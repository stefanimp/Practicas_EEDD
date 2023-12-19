//
// Created by stefan on 09/10/2023.
//

#ifndef PRACTICA_1B_AEROPUERTO_H
#define PRACTICA_1B_AEROPUERTO_H

#include <iostream>
#include "UTM.h"
#include <stdexcept>

class Aeropuerto{
private:
    //Atributos
    unsigned int id;
    std::string iata="";
    std::string tipo="";
    std::string nombre="";
    UTM posicion;
    std::string continente="";
    std::string isoPais="";
public:
    //Constructores y destructor
    Aeropuerto();
    Aeropuerto(unsigned int id, std::string iata, std::string tipo, std::string nombre, UTM posicion, std::string continente, std::string isoPais);
    Aeropuerto(const Aeropuerto& orig);
    virtual ~Aeropuerto();
    //Getters y Setters
    int getId() const;
    void setId(const unsigned int &id);
    const std::string &getIata() const;
    void setIata(const std::string &iata);
    const std::string &getTipo() const;
    void setTipo(const std::string &tipo);
    const std::string &getNombre() const;
    void setNombre(const std::string &nombre);
    UTM getPosicion() const;
    void setPosicion(const UTM &posicion);
    float getX() const;
    float getY() const;
    const std::string &getContinente() const;
    void setContinente(const std::string &continente);
    const std::string &getIsoPais() const;
    void setIsoPais(const std::string &isoPais);
    bool operator<(const Aeropuerto& orig);
    bool operator>(const Aeropuerto& orig);
    bool operator==(const Aeropuerto& orig);
};

#endif //PRACTICA_1B_AEROPUERTO_H