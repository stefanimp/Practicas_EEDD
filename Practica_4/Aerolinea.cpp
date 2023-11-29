//
// Created by stefan on 06/11/2023.
//

#include "Aerolinea.h"
#include "Ruta.h"

Aerolinea::~Aerolinea() {

}

std::list<Aeropuerto *> Aerolinea::getAeropuertosOrigin() {
    std::list<Aeropuerto*> listaAeropuertos;
    for (int i = 0; i < aerorutes.size(); ++i) {
        listaAeropuertos.push_back(&(aerorutes[i]->getOrigin()));
    }
    return listaAeropuertos;
}


std::list<Ruta *> Aerolinea::getRutasAeropuerto(const std::string &iataAeropuerto) {
    std::list<Ruta*> listaRutas;
    for (int i = 0; i < aerorutes.size(); ++i) {
        if(aerorutes[i]->existeAeropuerto(iataAeropuerto)){
            listaRutas.push_back(aerorutes[i]);
        }
    }
    return listaRutas;
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
    aerorutes.push_back(ruta);
}

bool Aerolinea::isAvtivo() const {
    return activo;
}

//TODO  comprobar si falta asñgo de este método y asegurarse de que se usa bien vuelaflight
//TODO ver si se pude optimizar este método y el leer de vuela flight
Vuelo *Aerolinea::addVuelo(Vuelo &vuelo) {
    if(&vuelo == nullptr || vuelo.getAerolinea() != this){
        return nullptr;
    }

    std::multimap<std::string, Vuelo>::iterator iteratorNewFlight = flights.insert(std::pair<std::string, Vuelo>(vuelo.getFlightNumb(), vuelo));

    bool encontrado = false;
    std::deque<Ruta*>::iterator iteratorRoutes = aerorutes.begin();
    while (iteratorRoutes != aerorutes.end() && !encontrado){
        if (&(*iteratorRoutes)->getOrigin() == vuelo.getAeropuertoOrigin() && &(*iteratorRoutes)->getDestination() == vuelo.getAeropuertoDestino() && &(*iteratorRoutes)->getCompany() == vuelo.getAerolinea()){
            encontrado = true;
            //TODO si no va probar con vuelo en vez del oiterador al añadir a la ruta
            (*iteratorRoutes)->addVuelo(iteratorNewFlight->second);
        }
        ++iteratorRoutes;
    }

    return &iteratorNewFlight->second;
}

//TODO comprobar que este método funcione. Es buena solución devolver una lista de punteros a Vuelos?
std::list<Vuelo*> Aerolinea::getVuelos(const std::string &flightNum) {
    std::list<Vuelo*> listFlights;
    std::multimap<std::string, Vuelo>::iterator iteratorFlights = flights.find(flightNum);
    while (iteratorFlights != flights.end() && iteratorFlights->second.getFlightNumb() == flightNum){
        listFlights.push_back(&iteratorFlights->second);
        ++iteratorFlights;
    }
    return listFlights;
}

//TODO está bien? Es una buena solución devolver una lista de punteros a vuelos?
std::list<Vuelo*> Aerolinea::getVuelos(const Fecha &fechIni, const Fecha &fechFin) {
    std::list<Vuelo*> listFlights;
    std::multimap<std::string, Vuelo>::iterator iteratorFlights = flights.begin();
    Fecha fechIn = fechIni;
    Fecha fechFn = fechFin;
    while (iteratorFlights != flights.end()){
        Fecha fechaTemp = *(iteratorFlights->second.getFecha());
        if(fechaTemp >= fechIn && fechaTemp <= fechFn){
            listFlights.push_back(&iteratorFlights->second);
        }
        ++iteratorFlights;
    }
    return listFlights;
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

std::multimap<std::string, Vuelo> Aerolinea::getVuelos() const {
    return flights;
}