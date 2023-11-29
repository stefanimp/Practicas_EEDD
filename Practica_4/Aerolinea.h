//
// Created by stefan on 06/11/2023.
//

#ifndef PRACTICA_2_AEROLINEA_H
#define PRACTICA_2_AEROLINEA_H

#include "string"
#include "Aeropuerto.h"
#include "fecha.h"
#include <deque>
#include <map>
#include <list>

class Ruta;
class Vuelo;

class Aerolinea{
private:
    unsigned int id = 0;
    std::string icao = "";
    std::string  nombre = "";
    std::string pais = "";
    bool activo;
    std::deque<Ruta*> aerorutes;
    std::multimap<std::string, Vuelo> flights; //con clave identificador de vuelo
public:
    Aerolinea() = default;
    ~Aerolinea();
    std::list<Aeropuerto*> getAeropuertosOrigin();
    std::list<Ruta*> getRutasAeropuerto(const std::string &iataAeropuerto);
    void setId(const unsigned int id);
    unsigned int getId() const;
    void setIcao(const std::string &icao);
    std::string getIcao() const;
    void setNombre(const std::string &nombre);
    std::string getNombre() const;
    void setPais(const std::string &pais);
    std::string getPais() const;
    void setActivo(const bool activo);
    bool getActivo() const;
    void linkAerolRuta(Ruta *ruta);
    bool isAvtivo() const;
    Vuelo* addVuelo(Vuelo &vuelo);
    std::list<Vuelo*> getVuelos(const std::string &flightNum);
    std::list<Vuelo*> getVuelos(const Fecha &fechIni, const Fecha &fechFin);
    std::multimap<std::string, Vuelo> getVuelos() const;
    bool operator<(const Aerolinea &orig);
    bool operator>(const Aerolinea &orig);
    bool operator==(const Aerolinea &orig);

};


#endif //PRACTICA_2_AEROLINEA_H
