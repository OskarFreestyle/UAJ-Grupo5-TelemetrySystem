#include "Tracker.h"
#include "Timer.h"
#include "sha256.h"
#include "nlohmann/json.hpp"
#include "checkML.h"
#include "FilePersistence.h"
#include "JsonSerializer.h"

#include <iostream>
#include <fstream>

using json = nlohmann::json;

// Referencia estatica para el singleton
Tracker* Tracker::instance_ = nullptr;

Tracker::Tracker() {

    std::cout << "Tracker construido con exito!" << std::endl;

    generateSessionId();

    createMaskBits();

    serializers_.push_back(new JsonSerializer());
    perstObjects_.push_back(new FilePersistence(serializers_, id_));
}

Tracker::~Tracker() {

    Timer::End();

    for (auto it = perstObjects_.begin(); it != perstObjects_.end(); ++it)
        delete (*it);

    perstObjects_.clear();

    for (auto it = serializers_.begin(); it != serializers_.end(); ++it)
        delete (*it);

    serializers_.clear();

    std::cout << "Tracker destruido con exito!" << std::endl;
}

void Tracker::createMaskBits() {

    // Lectura de JSON y creacion de mascara de bits
    std::ifstream file("events.json");
    json j;
    file >> j;

    eventsMaskBits_ = 0x0000;

    for (const auto& item : j.at("data")) {
        bool active = item.at("active");
        int index = item.at("index");

        if (active)
            eventsMaskBits_ += std::pow(2, index);
    }

}

void Tracker::generateSessionId() {
    time_t now = Timer::Instance()->getTimeNow();

    // El numero en bytes que necesita el buffer para que la función ctime_s funcione correctamente son 26
    const std::size_t buffer_size = 26;

    char dt[buffer_size]; 
    ctime_s(dt, buffer_size, &now);

    id_ = sha256(dt);

    std::cout << "Identificador de la sesion: " << id_ << " generado con SHA-256 a partir de la fecha actual: " << dt << std::endl;
}

SessionStartEvent* Tracker::createSessionStartEvent() {

    SessionStartEvent* e = new SessionStartEvent(Timer::Instance()->getTimeSinceStart(), id_);
    return e;
}

void Tracker::End() {

    if (instance_ != nullptr) {
        delete instance_;
        instance_ = nullptr;
    }
}

Tracker* Tracker::Instance() {

    if (instance_ == nullptr)
        instance_ = new Tracker();

    return instance_;

}


void Tracker::trackEvent(TrackerEvent* event) {

    if (!event->isTrackable(eventsMaskBits_)) return;

    for (std::list<IPersistence*>::iterator ite = perstObjects_.begin(); ite != perstObjects_.end(); ++ite) {
        (*ite)->sendEvent(event);
    }

    TrackerEvent::DestroyEvent(event);

}

std::string Tracker::getSessionId() {
    return id_;
}
