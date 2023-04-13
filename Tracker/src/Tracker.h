#pragma once

#include <string>
#include <list>
#include <unordered_map>
#include "TrackerEvent.h"

class IPersistence;
class ISerializer;

class Tracker {

private:

    Tracker();
    ~Tracker();

    // Referencia estatica para el singleton
    static Tracker* instance_;

    // Sesion ID
    std::string id_;

    // Mascara para representar que eventos se van a trackear
    uint16_t eventsMaskBits_;

    // Genera la mascara de bits a partir de la lectura del JSON
    void ReadConfigurationFile();

    // Genera un id de sesion aplicando sha256 a una cadena sacada a partir del tiempo actual
    void generateSessionId();

    std::unordered_map<std::string, ISerializer*> serializers_;

    // Lista de objetos de persistencia (cada uno se encarga de un tipo de persistencia)
    std::list<IPersistence*> perstObjects_;

    std::list<RecurringEvent*> recurringEvents;


    std::string currentSerializer;
    int maxElementsInQueue;

    float dumpTimer;
    float dumpTime;

    float defaultRecurringInterval;
public:

    // Evitamos copiar objetos de la clase Tracker
    Tracker(Tracker& other) = delete;

    // Evitamos asignar objetos de la clase Tracker
    void operator=(const Tracker&) = delete;


    static ISerializer* GetSerializer();


    /// <summary>
    /// Este metodo deberia ser llamado en cada iteracion del bucle de juego. Se utiliza para actualizar los temporizadores
    /// </summary>
    static void Update(float dt);


    // Factoria de eventos
    static SessionStartEvent* createSessionStartEvent();
    static SessionEndEvent* createSessionEndEvent();
    static LeaveBaseEvent* createLeaveBaseEvent();
    static FoodItemCraftedEvent* createFoodItemCraftedEvent();
    static ShipItemCraftedEvent* createShipItemCraftedEvent();
    static ActionUsedEvent* createActionUsedEvent();
    static EnterRaidMenuEvent* createEnterRaidMenuEvent();
    static RaidSelectedEvent* createRaidSelectedEvent();
    static ItemConsumedEvent* createItemConsumedEvent();
    static PositionEvent* createPositionEvent();


    /// <summary>
    /// Libera los recursos del tracker, persistiendo antes todos los eventos de la cola
    /// </summary>
    static void End();

    /// <summary>
    /// Devuelve la instancia del singleton
    /// </summary>
    static Tracker* Instance();

    /// <summary>
    /// Si el eventos es trackeable, lo envia a los objetos de persistencia
    /// Después es eliminado ya que los objetos de persistencia lo clona
    /// </summary>
    void trackEvent(TrackerEvent* event);


    RecurringEvent* AddRecurringEvent(float interval, std::function<TrackerEvent* ()> funct);
    RecurringEvent* AddRecurringEvent(std::function<TrackerEvent*()> funct);
    bool RemoveRecurringEvent(RecurringEvent* event);

};

