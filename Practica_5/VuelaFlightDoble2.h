//
// Created by stefan on 10/12/2023.
//

#ifndef PRACTICA_2_VUELAFLIGHTDOBLE2_H
#define PRACTICA_2_VUELAFLIGHTDOBLE2_H

#include "Ruta.h"
#include "THashAeropuerto.h"
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>


class VuelaFlightDoble2{
private:
    THashAeropuerto airports;
    std::multimap<std::string, Ruta> routesOrigin;  // La clave es el codigo IATA del aeropuerto origen
    std::multimap<std::string, Ruta*> routesDest;   // La clave es el codigo IATA del aeropuerto destino
    std::map<std::string, Aerolinea> aerolines; // La calve es el ICAO de la aerolinea

public:
    //Constructores y destructores
    VuelaFlightDoble2();
    VuelaFlightDoble2(std::ifstream &fichAirports, std::ifstream &fichAerolines, std::ifstream &fichRoutes, std::ifstream &fichFlights, unsigned long int maxAirpotsToInsert, float lambda = 0.7);
    ~VuelaFlightDoble2() = default;
    //Otros metodos
    void addAeropuerto(const Aeropuerto &aeropuerto);
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
    Aeropuerto* buscaAeropuertoIata(const std::string &iata);
    unsigned int getNumAeropuertos() const;
    std::list<Aeropuerto*> getAeropuertosList();
    std::vector<Aeropuerto*> getAeropuertosVector();
    void eliminarAirport(const std::string &iata);
    void eliminarAirportsInactivos();
    void mostrarEstadoTabla() const;
};

#endif //PRACTICA_2_VUELAFLIGHTDOBLE2_H
