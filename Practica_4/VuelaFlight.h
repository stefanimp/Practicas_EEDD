//
// Created by stefan on 23/10/2023.
//

#ifndef PRACTICA_1B_VUELAFLIGHT_H
#define PRACTICA_1B_VUELAFLIGHT_H


#include "Ruta.h"
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>


class VuelaFlight{
private:
    std::vector<Aeropuerto> airports;
    std::list<Ruta> routes;
    std::map<std::string, Aerolinea> aerolines; // La calve es el ICAO de la aerolinea

public:
    //Constructores y destructores
    VuelaFlight();
    VuelaFlight(std::ifstream &fichAirports, std::ifstream &fichRoutes, std::ifstream &fichAerolines, std::ifstream &fichFlights);
    ~VuelaFlight() = default;
    //Otros metodos
    void addAeropuerto(const Aeropuerto &aeropuerto);
    void ordenarAirports();
    Ruta *buscarRutasOriDes(const std::string &idAerOrig, const std::string &idAerDest);
    std::list<Ruta*> buscarRutasOrigen(const std::string &idAerOrig);
    std::list<Aeropuerto*> buscarAeropuertoPais(const std::string &pais);
    Ruta* addNewRute(const std::string &idAerOrig, const std::string &idAerDest, const std::string &aerolin);
    Aerolinea *buscaAerolinea(const std::string &icaoAerolinea);
    std::list<Aerolinea*> buscarAerolineasActivas();
    std::list<Aerolinea*> getAerolineasPais(const std::string &idPais);
    bool registrarVuelo(const std::string flightNum, const std::string iataAeroOrig, const std::string iataAeroDest, const std::string plane, const std::string datosMeteo, const Fecha &fecha);
    std::list<Vuelo*> buscaVuelos(const std::string &fNumber);
    //TODO hacer este método
    std::list<Vuelo*> vuelosOperadosPor(const std::string &icaoAerolinea, const Fecha &fecha);
    std::set<std::string> buscaVuelosDestAerop(const std::string &paisOrig, const std::string &iataAeropDest);
    std::set<Aeropuerto*> buscaAeropuertosAerolinea(const std::string &icaoAerolinea);
};

#endif //PRACTICA_1B_VUELAFLIGHT_H
