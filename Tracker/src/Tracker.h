#pragma once

#include <string>
#include <list>
#include <unordered_map>

// Events
#include "Events/TrackerEvent.h"
#include "Events/ActionUsedEvent.h"
#include "Events/EnterRaidMenuEvent.h"
#include "Events/FoodItemCraftedEvent.h"
#include "Events/ItemConsumedEvent.h"
#include "Events/LeaveBaseEvent.h"
#include "Events/PositionEvent.h"
#include "Events/RaidSelectedEvent.h"
#include "Events/RaidVisualizedEvent.h"
#include "Events/RecurringEvent.h"
#include "Events/SessionEndEvent.h"
#include "Events/SessionStartEvent.h"
#include "Events/ShipItemCraftedEvent.h"

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

    // Tiempo entre flushes
    float timeBetweenFlushes;

    // Timer para la logica de flush de la cola
    float timer;

    // Lista de objetos de persistencia (cada uno se encarga de un tipo de persistencia)
    std::list<IPersistence*> perstObjects_;

    // Atriutos para eventos periodicos
    std::list<RecurringEvent*> recurringEvents;
    float defaultRecurringInterval;

    // Genera la mascara de bits a partir de la lectura del JSON e inicializa el resto de informacion
    void readConfigurationFile(std::list<std::string>& serializersToUse);

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
    static RaidVisualizedEvent* createRaidVisualizedEvent();
    static ItemConsumedEvent* createItemConsumedEvent();
    static PositionEvent* createPositionEvent();

    // Tracking de eventos periodicos
    RecurringEvent* AddRecurringEvent(std::function<TrackerEvent* ()> funct, float interval = -1);
    bool RemoveRecurringEvent(RecurringEvent* event);
};

