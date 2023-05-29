#include "Tracker.h"
#include "Timer.h"
#include "sha256.h"
#include "nlohmann/json.hpp"
#include "checkML.h"
#include "FilePersistence.h"
#include "JsonSerializer.h"
#include "CSVSerializer.h"

#include <iostream>
#include <fstream>

using json = nlohmann::json;

// Referencia estatica para el singleton
Tracker* Tracker::instance_ = nullptr;

Tracker* Tracker::Instance() {
    // Si el singleton no existe lo crea
    if (instance_ == nullptr)
        instance_ = new Tracker();

    return instance_;
}

void Tracker::End() {
    // Se destruye el timer
    Timer::End();

    // Se acaban de persistir los objetos que queden
    for (auto& pers : instance_->perstObjects_) {
        pers->Flush(true);
    }

    // Se borra la instancia del singleton
    if (instance_ != nullptr) {
        delete instance_;
        instance_ = nullptr;
    }
}

Tracker::Tracker() {
    std::cout << "Tracker construido con exito!" << std::endl;

    generateSessionId();

    readConfigurationFile();

    // Se crean los serializadores y los objetos de persistencia
    serializers_["json"] = new JsonSerializer();
    serializers_["csv"] = new CSVSerializer();

    perstObjects_.push_back(new FilePersistence(maxElementsInQueue, id_));
}

Tracker::~Tracker() {

    // Se eliminan los eventos periodicos
    for (auto rec : recurringEvents)
        delete rec;

    recurringEvents.clear();

    // Se eliminan los objetos de persistencia
    for (auto it = perstObjects_.begin(); it != perstObjects_.end(); ++it)
        delete (*it);

    perstObjects_.clear();
       
            // Se eliminan los serializadores
            for (auto& ser : serializers_)
                delete ser.second;

            serializers_.clear();

    std::cout << "Tracker destruido con exito!" << std::endl;
}

void Tracker::readConfigurationFile() {

    // Lectura de JSON y creacion de mascara de bits
    std::ifstream file("configure.json");
    json j;
    file >> j;

    eventsBitMask_ = 0x0000;

    for (const auto& item : j.at("data")) {
        bool active = item.at("active");
        int index = item.at("index");

        // Si el evento esta marcado como trackeable se añade a la mascara
        if (active)
            eventsBitMask_ += std::pow(2, index);
    }

    defaultRecurringInterval = j.contains("defaultRecurringInterval") ? j["defaultRecurringInterval"].get<float>() : 10;
    maxElementsInQueue = j.contains("maxElementsInQueue") ? j["maxElementsInQueue"].get<int>() : 10;
    currentSerializer = j.contains("serializer") ? j["serializer"].get<std::string>() : "json";
}

void Tracker::generateSessionId() {
    // Se inicia el timer
    time_t now = Timer::Instance()->getTimeNow();

    // El numero en bytes que necesita el buffer para que la función ctime_s funcione correctamente son 26
    const std::size_t buffer_size = 26;

    char dt[buffer_size]; 
    ctime_s(dt, buffer_size, &now);

    id_ = sha256(dt);

    std::cout << "Identificador de la sesion: " << id_ << " generado con SHA-256 a partir de la fecha actual: " << dt << std::endl;
}


void Tracker::trackEvent(TrackerEvent* event) {

    // Si el evento no es trackeable se descarta
    if (!event->isTrackable(eventsBitMask_))
    {
        TrackerEvent::DestroyEvent(event);
        return;
    }

    // Envia a todos los objetos de persistencia
    for (auto p : perstObjects_)
        p->sendEvent(event);

    // Destruye el evento ya que los objetos de persistencia lo clonan
    TrackerEvent::DestroyEvent(event);
}

ISerializer* Tracker::GetSerializer() {
    std::string current = instance_->currentSerializer;
    std::unordered_map<std::string, ISerializer*>& serializer = instance_->serializers_;

    if (serializer.contains(current)) {
        return serializer[current];
    }

    return serializer["json"];
}


void Tracker::Update(float dt) {
    for (auto& recEv : instance_->recurringEvents) 
        recEv->Update(dt);
}


RecurringEventsManager* Tracker::AddRecurringEvent(std::function<TrackerEvent* ()> funct, float interval) {

    // Si no se especifica intervalo entre eventos, se establece el intervalo por defecto
    if (interval == -1) interval = defaultRecurringInterval;

    RecurringEventsManager* ev = new RecurringEventsManager(funct, interval);
    recurringEvents.push_back(ev);
    return ev;
}

bool Tracker::RemoveRecurringEvent(RecurringEventsManager* ev) {

    int size = recurringEvents.size();
    recurringEvents.remove(ev);

    delete ev;

    return recurringEvents.size() != size;
}


// ------------------ Factoria de eventos ---------------------

SessionStartEvent* Tracker::createSessionStartEvent() {
    return new SessionStartEvent(Timer::Instance()->getTimeNow(), instance_->id_);
}

SessionEndEvent* Tracker::createSessionEndEvent() {
    return new SessionEndEvent(Timer::Instance()->getTimeNow(), instance_->id_);
}

LeaveBaseEvent* Tracker::createLeaveBaseEvent() {
    return new LeaveBaseEvent(Timer::Instance()->getTimeNow(), instance_->id_);
}

FoodItemCraftedEvent* Tracker::createFoodItemCraftedEvent() {
    return new FoodItemCraftedEvent(Timer::Instance()->getTimeNow(), instance_->id_);
}

ShipItemCraftedEvent* Tracker::createShipItemCraftedEvent() {
    return new ShipItemCraftedEvent(Timer::Instance()->getTimeNow(), instance_->id_);
}

ActionUsedEvent* Tracker::createActionUsedEvent() {
    return new ActionUsedEvent(Timer::Instance()->getTimeNow(), instance_->id_);
}

EnterRaidMenuEvent* Tracker::createEnterRaidMenuEvent() {
    return new EnterRaidMenuEvent(Timer::Instance()->getTimeNow(), instance_->id_);
}

RaidSelectedEvent* Tracker::createRaidSelectedEvent() {
    return new RaidSelectedEvent(Timer::Instance()->getTimeNow(), instance_->id_);
}

ItemConsumedEvent* Tracker::createItemConsumedEvent() {
    return new ItemConsumedEvent(Timer::Instance()->getTimeNow(), instance_->id_);
}

PositionEvent* Tracker::createPositionEvent() {
    return new PositionEvent(Timer::Instance()->getTimeNow(), instance_->id_);
}
