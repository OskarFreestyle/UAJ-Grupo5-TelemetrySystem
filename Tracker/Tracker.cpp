#include "Tracker.h"
#include <iostream>

// Referencia estatica para el singleton
Tracker* Tracker::instance_ = nullptr;

Tracker::Tracker() {
    std::cout << "Tracker construido con exito" << std::endl;
}

Tracker::~Tracker() {
    std::cout << "Tracker destruido con exito" << std::endl;
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

void Tracker::trackEvent() {

}
