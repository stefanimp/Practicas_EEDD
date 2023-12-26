//
// Created by stefan on 23/10/2023.
//

#ifndef PRACTICA_1B_VUELAFLIGHT_H
#define PRACTICA_1B_VUELAFLIGHT_H


#include "Ruta.h"
#include "MallaRegular.h"

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <sstream>

class VuelaFlight{
private:

    class AirportsFlights{
    public:
        Aeropuerto *airport = nullptr;
        int numFlights = 0;

        AirportsFlights(Aeropuerto &airport, const int numFlights):airport(&airport), numFlights(numFlights){
        }

        ~AirportsFlights(){
            airport = nullptr;
        };
        bool operator>(const AirportsFlights &orig) const{
            return (this->numFlights > orig.numFlights);
        }
        bool operator<(const AirportsFlights &orig) const{
            return (this->numFlights < orig.numFlights);
        }

    };

    std::unordered_map<std::string, Aeropuerto> airports;
    MallaRegular<Aeropuerto*> airportsUTM;
    std::multimap<std::string, Ruta> routesOrigin;  // La clave es el codigo IATA del aeropuerto origen
    std::multimap<std::string, Ruta*> routesDest;   // La clave es el codigo IATA del aeropuerto destinos
    std::map<std::string, Aerolinea> aerolines; // La calve es el ICAO de la aerolinea
    void rellenaMalla(float xMin, float xMax, float yMin, float yMax){
        airportsUTM = MallaRegular<Aeropuerto*>(xMin, yMin, xMax, yMax, 80);
        for (std::unordered_map<std::string, Aeropuerto>::iterator iteratorAirports = airports.begin(); iteratorAirports != airports.end() ; ++iteratorAirports) {
            airportsUTM.insertar(iteratorAirports->second.getX(),iteratorAirports->second.getY(),&iteratorAirports->second);
        }
    }
public:
    //Constructores y destructores
    VuelaFlight() = default;
    VuelaFlight(std::ifstream &fichAirports, std::ifstream &fichAerolines, std::ifstream &fichRoutes, std::ifstream &fichFlights);
    ~VuelaFlight() = default;
    //Otros metodos
    unsigned long funcionHash(const std::string &iata);
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
    std::list<Vuelo*> vuelosOperadosPor(const std::string &icaoAerolinea, const Fecha &fecha);
    std::set<std::string> buscaVuelosDestAerop(const std::string &paisOrig, const std::string &iataAeropDest);
    std::set<Aeropuerto*> buscaAeropuertosAerolinea(const std::string &icaoAerolinea);
    Aeropuerto* buscaAeropuertoIata(const std::string &iata);
    unsigned int getNumAeropuertos() const;
    std::list<Aeropuerto*> getAeropuertos();
    void eliminarAirport(const std::string &iata);
    void eliminarAirportsInactivos();
    std::vector<Aeropuerto*> buscarAriportsRadio(const UTM &pos, float radioKm);
    std::list<Aeropuerto*> airportsMasSalidas(const UTM &pos, float radioKm);
    void addAirportPostConst(const Aeropuerto &airport);
    void mostrarEstadoTabla() const;
    void mostrarEstadoMalla() const;

};

#endif //PRACTICA_1B_VUELAFLIGHT_H
