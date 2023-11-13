//
// Created by stefan on 09/10/2023.
//

#include "Aeropuerto.h"

/**
 * @brief   Constructor por defecto de la clase Aeropuerto
 * @details El parámetro posicion también queda inicializado por defecto
 * @post El objeto queda creado con los valores dados por defecto en los atributos
 * */
Aeropuerto::Aeropuerto(): posicion(UTM()) {

}

/**
 * @brief   Constructor parametrizado de la clase Aeropuerto
 * @param[in]posicion   valor que tendrá el atributo posicion
 * @param[in]tipo   valor que tendrá el atributo tipo
 * @param[in]nombre valor que tendrá el atributo nombre
 * @param[in]continente valor que tendrá el atributo continente
 * @param[in]id valor que tendrá el atributo id
 * @param[in]iata  valor que tendrá el atributo iata
 * @param[in]isoPais valor que tendrá el atributo isoPais
 * @post    El objeto es creado y sus atributos toman los valores especificados en los parámetros del constructor
 * */
Aeropuerto::Aeropuerto(unsigned int id, std::string iata, std::string tipo,std::string nombre, UTM posicion, std::string continente,std::string isoPais):
        id(id), iata(iata), tipo(tipo), nombre(nombre), posicion(posicion), continente(continente), isoPais(isoPais){

}

/**
 * @brief   Constructor de copia de la clase Aeropuerto
 * @details Los atributos tienen los mismos valores, pero en caso de tener algún puntero, estos no apuntarán a la misma dirección de memoria.
 * @param[in]orig   objeto del que se copiarán todos los parámetros
 * @post    El objeto queda creado con los mismo parámetros que el original
 * @warning . El operado asignación de todos los objetos que se vayan a copiar debe estar bien implementado.
 * */
Aeropuerto::Aeropuerto(const Aeropuerto &orig): id(orig.id), iata(orig.iata), tipo(orig.tipo), nombre(orig.nombre), continente(orig.continente), isoPais(orig.isoPais) {

}

/**
 * @brief   Destructor de la clase Aeropuerto
 * @post    El objeto queda destruido
 * */
Aeropuerto::~Aeropuerto() {

}

/**
 * @brief   Devuelve el valor del atributo id
 * @post    El valor del atributo id es devuelto
 * */
int Aeropuerto::getId() const {
    return id;
}

/**
 * @brief   Modifica el valor del atributo id
 * @param[in]id   nuevo valor que tendrá el atributo id
 * @post    El atributo id queda modificado
 * */
void Aeropuerto::setId(const unsigned int &id) {
    this->id = id;
}

/**
 * @brief   Devuelve el valor del atributo iata
 * @post    El valor del atributo iata es devuelto
 * */
const std::string &Aeropuerto::getIata() const {
    return iata;
}

/**
 * @brief   Modifica el valor del atributo iata
 * @param[in]iata   nuevo valor que tendrá el atributo aita
 * @post    El atributo iata queda modificado
 * */
void Aeropuerto::setIata(const std::string &iata) {
    this->iata = iata;
}

/**
 * @brief   Devuelve el valor del atributo tipo
 * @post    El valor del atributo tipo es devuelto
 * */
const std::string &Aeropuerto::getTipo() const {
    return tipo;
}


/**
 * @brief   Modifica el valor del atributo tipo
 * @param[in]tipo   nuevo valor que tendrá el atributo tipo
 * @post    El atributo tipo queda modificado
 * */
void Aeropuerto::setTipo(const std::string &tipo) {
    this->tipo = tipo;
}

/**
 * @brief   Devuelve el valor del atributo nombre
 * @post    El valor del atributo nombre es devuelto
 * */
const std::string &Aeropuerto::getNombre() const {
    return nombre;
}

/**
 * @brief   Modifica el valor del atributo nombre
 * @param[in]nombre   nuevo valor que tendrá el atributo nombre
 * @post    El atributo nombre queda modificado
 * */
void Aeropuerto::setNombre(const std::string &nombre) {
    this->nombre = nombre;
}

/**
 * @brief   Devuelve el valor del atributo continente
 * @post    El valor del atributo continente es devuelto
 * */
const std::string &Aeropuerto::getContinente() const {
    return continente;
}

/**
 * @brief   Modifica el valor del atributo continente
 * @param[in]continente   nuevo valor que tendrá el atributo continente
 * @post    El atributo continente queda modificado
 * */
void Aeropuerto::setContinente(const std::string &continente) {
    this->continente = continente;
}

/**
 * @brief   Devuelve el valor del atributo isoPais
 * @post    El valor del atributo isoPais es devuelto
 * */
const std::string &Aeropuerto::getIsoPais() const {
    return isoPais;
}

/**
 * @brief   Modifica el valor del atributo isoPais
 * @param[in]isoPais   nuevo valor que tendrá el atributo isoPais
 * @post    El atributo isoPais queda modificado
 * */
void Aeropuerto::setIsoPais(const std::string &isoPais) {
    this->isoPais = isoPais;
}

/**
 * @brief   Devuelve el valor del atributo posicion
 * @post    El valor del atributo posicion es devuelto
 * */
UTM Aeropuerto::getPosicion() const{
    return posicion;
}

/**
 * @brief   Modifica el valor del atributo posicion
 * @param[in]posicion   nuevo valor que tendrá el atributo posicion
 * @post    El atributo posicion queda modificado
 * */
void Aeropuerto::setPosicion(const UTM& posicion) {
    this->posicion = posicion;
}

/**
 * @brief   Operador <(menor que) de la clase Aerorpuerto
 * @details Compara si un aeropuerto es menor que otro basandose en su iata
 * @return  True si this es menor que origianl y false si this no es menor que origianl
 * */
bool Aeropuerto::operator<(const Aeropuerto &orig) {
    return (this->iata < orig.iata);
}

/**
 * @brief   Operador >(mayor que) de la clase Aerorpuerto
 * @details Compara si un aeropuerto es mayor que otro basandose en su iata
 * @return  True si this es mayor que origianl y false si this no es mayor que origianl
 * */
bool Aeropuerto::operator>(const Aeropuerto &orig) {
    return (this->iata > orig.iata);
}

/**
 * @brief   Operador ==(igualdad) de la clase Aeropuerto
 * @details Compara si dos aeropuertos son iguales basandose en su iata
 * @return  Devuelve true si los aeropuertos tienen el mismo iata y falso si es distinto
 * */
bool Aeropuerto::operator==(const Aeropuerto &orig) {
    return (this->iata == orig.iata);
}