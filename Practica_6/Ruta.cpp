//
// Created by stefan on 23/10/2023.
//

#include "Ruta.h"


//TODO quizas añadir  aqui una excepcion que si el origin o el destination estan vacios no se pude crear el objeto
/**
 * @brief   Constructor parametrizado de la clase Ruta
 * @details Da valores a los atributos aerolinea, origin y detination
 * @param[in]aerolinea  valor que tendra el atributo aerolinea
 * @param[in]origin aeropuerto de origen de la ruta
 * @param[in]destination    aeropuerto de destino que tendra la ruta
 * @post    El objeto es creado con los valores dados como parametros
 * */
Ruta::Ruta(Aerolinea &company, Aeropuerto &origin, Aeropuerto &destination):company(&company), origin(&origin), destination(&destination) {

}

/**
 * @brief   Destructor de la clase Ruta
 * @post    El objeto es destruido
 * */
Ruta::~Ruta() {

}

/**
 * @brief   Devuelve la direccion de memoria del atributo origin
 * @post    La direccion de memoria del atributo origin es devuelta
 * */
Aeropuerto *Ruta::getOrigin() const {
    return origin;
}

/**
 * @brief   Modifica la direccion de memoria del atributo origin
 * @param[in]origin   nueva deireccion de memoria que tendrá el atributo origin
 * @post    La direccion de memoria del atributo origin queda modificada
 * */
void Ruta::setOrigin(Aeropuerto &origin) {
    this->origin = &origin;
}

/**
 * @brief   Devuelve la direccion de memoria del atributo detination
 * @post    La direcion de memoria del atributo destination es devuelta
 * */
Aeropuerto *Ruta::getDestination() const {
    return destination;
}

/**
 * @brief   Modifica la direccion de memoria del atributo destination
 * @param[in]destination   nueva deireccion de memoria que tendrá el atributo destination
 * @post    La direccion de memoria del atributo destination queda modificada
 * */
void Ruta::setDestination(Aeropuerto &destination) {
    this->destination = &destination;
}

void Ruta::setCompany(Aerolinea &company) {
    this->company = &company;
}

Aerolinea &Ruta::getCompany() const {
    return *company;
}

bool Ruta::existeAeropuerto(const std::string &iata) {
    return ((origin->getIata() == iata) || (destination->getIata() == iata));
}

bool Ruta::addVuelo(Vuelo &vuelo) {
    if(vuelo.getAeropuertoOrigin() == origin && vuelo.getAeropuertoDestino() == destination && vuelo.getAerolinea() == company){
        flightRoute.push_back(&(vuelo));
        return true;
    }
    return false;
}

long Ruta::getNumFlights() const {
    return flightRoute.size();
}

//TODO así está bien?
std::list<Vuelo *> Ruta::getFlights() {
    return flightRoute;

}