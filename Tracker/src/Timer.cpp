#include "Timer.h"
#include <ctime>
#include <sstream>

Timer* Timer::instance = nullptr;

Timer* Timer::Instance() {

	if (instance == nullptr)
		instance = new Timer();

	return instance;
}

void Timer::End() {

	if (instance != nullptr) {
		delete instance; 
		instance = nullptr;
	}
}

time_t Timer::getTimeNow() {
    return std::time(nullptr);
}

std::string Timer::getTimeNowStringFormat() {

    // Obtenemos el tiempo actual en segundos desde el 1 de enero de 1970
    std::time_t tiempoActual = std::time(nullptr);
    std::time(&tiempoActual);

    std::tm tiempoLocal;

    // Convertimos el tiempo en una estructura tm para obtener la información
    localtime_s(&tiempoLocal, &tiempoActual);

    // Creamos un objeto std::stringstream para construir el string
    std::stringstream ss;

    // Formateamos los componentes de fecha y hora en el string
    ss << tiempoLocal.tm_year + 1900 << "-" << tiempoLocal.tm_mon + 1 << "-" << tiempoLocal.tm_mday << " ";
    ss << tiempoLocal.tm_hour << ":" << tiempoLocal.tm_min << ":" << tiempoLocal.tm_sec;

    // Obtenemos el string resultante
    std::string timeNowStringFormat = ss.str();

    return timeNowStringFormat;
}
