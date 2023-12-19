//
// Created by stefan on 22/11/2023.
//

#include "Vuelo.h"

Vuelo::~Vuelo() {

}

Aerolinea *Vuelo::getAerolinea() const {
    return linkaero;
}

void Vuelo::setAerolinea(Aerolinea &aerolinea) {
    this->linkaero = &aerolinea;
}

Aeropuerto *Vuelo::getAeropuertoOrigin() const {
    return airpOrigin;
}

void Vuelo::setAirportOrig(Aeropuerto &airportOrig) {
    this->airpOrigin = &airportOrig;
}

Aeropuerto *Vuelo::getAeropuertoDestino() const {
    return airpDestin;
}

void Vuelo::setAirportDest(Aeropuerto &airportDest) {
    this->airpDestin = &airportDest;
}

std::string Vuelo::getFlightNumb() const {
    return flihghtNumb;
}

void Vuelo::setFlightNumb(const std::string &flightNumb) {
    this->flihghtNumb = flightNumb;
}

Fecha *Vuelo::getFecha() {
    return &fecha;
}

void Vuelo::setFecha(const Fecha &fecha) {
    this->fecha = fecha;
}

void Vuelo::setPlane(const std::string &plane) {
    this->plane = plane;
}

std::string Vuelo::getPlane() const {
    return plane;
}

void Vuelo::setDatMeteo(std::string datMeteo) {
    this->datMeteo = datMeteo;
}

std::string Vuelo::getDatMeteo() const {
    return datMeteo;
}