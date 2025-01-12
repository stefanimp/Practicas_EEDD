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
        listaAeropuertos.push_back((aerorutes[i]->getOrigin()));
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

Vuelo *Aerolinea::addVuelo(Vuelo &vuelo) {
    // Comprobamos que el vuelo existe y que pertenece a esta areolinea
    if(&vuelo == nullptr || vuelo.getAerolinea() != this){
        return nullptr;
    }

    // Insertamos el vuelo en el multimap de vuelos de la aerolinea
    std::multimap<std::string, Vuelo>::iterator iteratorNewFlight = flights.insert(std::pair<std::string, Vuelo>(vuelo.getFlightNumb(), vuelo));

    //
    bool encontrado = false;
    std::deque<Ruta*>::iterator iteratorRoutes = aerorutes.begin();
    while (iteratorRoutes != aerorutes.end() && !encontrado){
        if ((*iteratorRoutes)->getOrigin() == vuelo.getAeropuertoOrigin() && (*iteratorRoutes)->getDestination() == vuelo.getAeropuertoDestino() && &(*iteratorRoutes)->getCompany() == vuelo.getAerolinea()){
            encontrado = true;
            (*iteratorRoutes)->addVuelo(iteratorNewFlight->second);
        }
        ++iteratorRoutes;
    }

    return &iteratorNewFlight->second;
}


std::list<Vuelo*> Aerolinea::getVuelos(const std::string &flightNum) {
    std::list<Vuelo*> listFlights;
    std::multimap<std::string, Vuelo>::iterator iteratorFlights = flights.find(flightNum);
    while (iteratorFlights != flights.end() && iteratorFlights->second.getFlightNumb() == flightNum){
        listFlights.push_back(&iteratorFlights->second);
        ++iteratorFlights;
    }
    return listFlights;
}


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

void Aerolinea::bajaAeropuerto(const std::string &iataAirport) {

    std::multimap<std::string, Vuelo>::iterator iteratorFlights = flights.begin();
    while(iteratorFlights != flights.end()){
        if(iteratorFlights->second.getAeropuertoDestino()->getIata() == iataAirport || iteratorFlights->second.getAeropuertoOrigin()->getIata() == iataAirport){
            iteratorFlights = flights.erase(iteratorFlights);
        }else {
            ++iteratorFlights;
        }
    }

    std::deque<Ruta *>::iterator iteratorRoutes = aerorutes.begin();
    while (iteratorRoutes != aerorutes.end()) {
        if ((*iteratorRoutes)->getOrigin()->getIata() == iataAirport || (*iteratorRoutes)->getDestination()->getIata() == iataAirport) {
            iteratorRoutes = aerorutes.erase(iteratorRoutes);
        }else{
            ++iteratorRoutes;
        }
    }

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