#pragma once

#include <string>
#include <list>

class ITrackerAsset;
class IPersistence;
class TrackerEvent;

class Tracker {

private:
    Tracker();
    ~Tracker();

    // Referencia estatica para el singleton
    static Tracker* instance_;

    std::string id_;

    uint16_t eventsMaskBits_;

    // Genera la mascara de bits a partir de la lectura del JSON
    void createMaskBits();

    // Genera un id de sesion aplicando sha256 a una cadena sacada a partir del tiempo actual
    void generateSessionId();

    // Lista de trackers activos
    std::list<ITrackerAsset*> trackers_;

    // Lista de objetos de persistencia (cada uno se encarga de un tipo de persistencia)
    std::list<IPersistence*> perstObjects_;


public:

    // Evitamos copiar objetos de la clase Tracker
    Tracker(Tracker& other) = delete;

    // Evitamos asignar objetos de la clase Tracker
    void operator=(const Tracker&) = delete;

    /// <summary>
    /// Libera los recursos del tracker, persistiendo antes todos los eventos de la cola
    /// </summary>
    static void End();

    /// <summary>
    /// Devuelve la instancia del singleton
    /// </summary>
    static Tracker* Instance();

    /// <summary>
    /// Envía el evento a los trackers que lo acepten
    /// </summary>
    void trackEvent(TrackerEvent* event);

};

