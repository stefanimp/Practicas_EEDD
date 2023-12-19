//
// Created by stefan on 22/11/2023.
//

#ifndef PRACTICA_2_VUELO_H
#define PRACTICA_2_VUELO_H

#endif //PRACTICA_2_VUELO_H

#include "string"
#include "fecha.h"
#include "Aerolinea.h"
#include "Aeropuerto.h"

class Vuelo{
private:
    std::string flihghtNumb;
    std::string plane;
    std::string datMeteo;
    Fecha fecha;
    Aerolinea *linkaero = nullptr;
    Aeropuerto *airpOrigin = nullptr;
    Aeropuerto *airpDestin = nullptr;
public:
    Vuelo() = default;
    ~Vuelo();
    Aerolinea *getAerolinea() const;
    void setAerolinea(Aerolinea &aerolinea);
    Aeropuerto *getAeropuertoOrigin() const;
    void setAirportOrig(Aeropuerto &airportOrig);
    Aeropuerto *getAeropuertoDestino() const;
    void setAirportDest(Aeropuerto &airportDest);
    std::string getFlightNumb() const;
    void setFlightNumb(const std::string &flightNumb);
    Fecha* getFecha();
    void setFecha(const Fecha &fecha);
    void setPlane(const std::string &plane);
    std::string getPlane() const;
    void setDatMeteo(std::string datMeteo);
    std::string getDatMeteo() const;
};