//
// Created by stefan on 06/11/2023.
//

#ifndef PRACTICA_2_AEROLINEA_H
#define PRACTICA_2_AEROLINEA_H

#include "string"
#include "VDinamico.h"
#include "Aeropuerto.h"
class Ruta;

class Aerolinea{
private:
    unsigned int id = 0;
    std::string icao = "";
    std::string  nombre = "";
    std::string pais = "";
    bool activo;
    VDinamico<Ruta*> aerorutes;
public:
    Aerolinea() = default;
    ~Aerolinea();
    VDinamico<Aeropuerto*> getAeropuertosOrigin();
    VDinamico<Ruta*> getRutasAeropuerto(const std::string &iataAeropuerto);
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
    bool operator<(const Aerolinea &orig);
    bool operator>(const Aerolinea &orig);
    bool operator==(const Aerolinea &orig);

};

#endif //PRACTICA_2_AEROLINEA_H
