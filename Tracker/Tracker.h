#pragma once

class Tracker {

private:
    Tracker();
    ~Tracker();

    // Referencia estatica para el singleton
    static Tracker* instance_;

    // TODO add persistenceObjects IPersistence
    // TODO add activeTrackers List<ITrackerAsset>

public:

    /// <summary>
    /// Libera los recursos del tracker, persistiendo antes todos los eventos de la cola
    /// </summary>
    void End();

    /// <summary>
    /// Devuelve la instancia del singleton
    /// </summary>
    static Tracker* Instance();

    /// <summary>
    /// TODO
    /// </summary>
    void trackEvent();

    // Eliminado el operador de clon
    Tracker(Tracker& other) = delete;
    // Eliminado el operador de asignacion
    void operator=(const Tracker&) = delete;
};

