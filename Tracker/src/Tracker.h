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
    uint16_t eventsBitMask_;

    // Numero maximo de eventos en la cola al mismo tiempo
    int maxElementsInQueue;

    // Lista de objetos de persistencia (cada uno se encarga de un tipo de persistencia)
    std::list<IPersistence*> perstObjects_;


    std::list<RecurringEventsManager*> recurringEvents;

    std::list<std::string> serializersToUse;

    float defaultRecurringInterval;


    // Genera la mascara de bits a partir de la lectura del JSON e inicializa el resto de informacion
    void readConfigurationFile();

    // Genera un id de sesion aplicando sha256 a una cadena obtenida a partir del tiempo actual
    void generateSessionId();

public:
    /// <summary>
    /// Devuelve la instancia del singleton
    /// </summary>
    static Tracker* Instance();

    /// <summary>
    /// Libera los recursos del tracker, persistiendo antes todos los eventos de la cola
    /// </summary>
    static void End();

    // Evitamos copiar objetos de la clase Tracker
    Tracker(Tracker& other) = delete;

    // Evitamos asignar objetos de la clase Tracker
    void operator=(const Tracker&) = delete;
    
    static ISerializer* GetSerializer();

    /// <summary>
    /// Este metodo deberia ser llamado en cada iteracion del bucle de juego. Se utiliza para actualizar los temporizadores
    /// </summary>
    static void Update(float dt);


    /// <summary>
    /// Si el eventos es trackeable, lo envia a los objetos de persistencia
    /// Despu�s es eliminado ya que los objetos de persistencia lo clona
    /// </summary>
    void trackEvent(TrackerEvent* event);


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

    // Tracking de eventos periodicos
    RecurringEventsManager* AddRecurringEvent(std::function<TrackerEvent* ()> funct, float interval = -1);
    bool RemoveRecurringEvent(RecurringEventsManager* event);
};

