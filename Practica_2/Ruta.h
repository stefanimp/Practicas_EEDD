//
// Created by stefan on 23/10/2023.
//

#ifndef PRACTICA_1B_RUTA_H
#define PRACTICA_1B_RUTA_H

#include "Aeropuerto.h"

class Ruta{
private:
    std::string aerolinea = "";
    //Esto con punteros o sin punteros?
    Aeropuerto *origin = nullptr;
    Aeropuerto *destination = nullptr;
public:
    //Constructores y destructor
    Ruta();
    Ruta(std::string aerolinea, Aeropuerto &origin, Aeropuerto &destination);
    ~Ruta();
    //Getters y setters
    const std::string getAerolinea() const;
    void setAerolinea(const std::string &aerolinea);
    Aeropuerto& getOrigin() const;
    void setOrigin(Aeropuerto &origin);
    Aeropuerto& getDestination() const;
    void setDestination(Aeropuerto &destination);

};

#endif //PRACTICA_1B_RUTA_H
