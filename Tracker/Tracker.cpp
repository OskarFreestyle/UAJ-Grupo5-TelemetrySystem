#include "Tracker.h"
#include <iostream>

// Variable estatica para el singleton
Tracker* Tracker::_instance = nullptr;

Tracker::Tracker()
{
    std::cout << "Tracker construido con exito" << std::endl;
}

Tracker::~Tracker()
{
    std::cout << "Tracker destruido con exito" << std::endl;
}

void Tracker::Init()
{
    std::cout << "Tracker Init" << std::endl;
}

void Tracker::End()
{
    // Comprueba que el tracker no ha sido borrado antes y lo borra
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

Tracker& Tracker::GetInstance()
{
    // Crea uno si es el primero
    if (_instance == nullptr) {
        _instance = new Tracker();
        std::cout << "Tracker creado con exito" << std::endl;
    }

    std::cout << "Tracker ya existente" << std::endl;

    return *_instance;
}

void Tracker::trackEvent()
{
}
