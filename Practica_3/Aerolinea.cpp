//
// Created by stefan on 06/11/2023.
//

#include "Aerolinea.h"
#include "Ruta.h"

Aerolinea::~Aerolinea() {

}

VDinamico<Aeropuerto*> Aerolinea::getAeropuertosOrigin() {
    VDinamico<Aeropuerto*> aeropuertosOrigen;
    for (int i = 0; i < aerorutes.tamLogigo(); ++i) {
        aeropuertosOrigen.insertar(&(aerorutes[i]->getOrigin()));
    }
    return aeropuertosOrigen;
}

VDinamico<Ruta *> Aerolinea::getRutasAeropuerto(const std::string &iataAeropuerto) {
    VDinamico<Ruta*> rutasIata;
    for (int i = 0; i < aerorutes.tamLogigo(); ++i) {
        if (aerorutes[i]->existeAeropuerto(iataAeropuerto)){
            rutasIata.insertar(aerorutes[i]);
        }
    }
    return rutasIata;
}

void Aerolinea::setId(const unsigned int id) {
    this->id = id;
}

unsigned int Aerolinea::getId() const {
    return id;
}

void Aerolinea::setIcao(const std::string &icao) {
    this->icao = icao;
}

std::string Aerolinea::getIcao() const {
    return icao;
}

void Aerolinea::setNombre(const std::string &nombre) {
    this->nombre = nombre;
}

std::string Aerolinea::getNombre() const {
    return nombre;
}

void Aerolinea::setPais(const std::string &pais) {
    this->pais = pais;
}

std::string Aerolinea::getPais() const {
    return pais;
}

void Aerolinea::setActivo(const bool activo) {
    this->activo = activo;
}

bool Aerolinea::getActivo() const {
    return activo;
}

void Aerolinea::linkAerolRuta(Ruta *ruta) {
    aerorutes.insertar(ruta);
}

bool Aerolinea::isAvtivo() const {
    return activo;
}

bool Aerolinea::operator<(const Aerolinea &orig) {
    return icao < orig.icao;
}

bool Aerolinea::operator>(const Aerolinea &orig) {
    return (icao > orig.icao);
}

bool Aerolinea::operator==(const Aerolinea &orig) {
    return (icao == orig.icao);
}