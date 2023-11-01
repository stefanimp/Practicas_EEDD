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
 * @param[in]ident  valor que tendrá el atributo ident
 * @param[in]isoPais valor que tendrá el atributo isoPais
 * @post    El objeto es creado y sus atributos toman los valores especificados en los parámetros del constructor
 * */
Aeropuerto::Aeropuerto(std::string id, std::string ident, std::string tipo,std::string nombre, UTM posicion, std::string continente,std::string isoPais):
        id(id), ident(ident), tipo(tipo), nombre(nombre), posicion(posicion), continente(continente), isoPais(isoPais){

}

/**
 * @brief   Constructor de copia de la clase Aeropuerto
 * @details Los atributos tienen los mismos valores, pero en caso de tener algún puntero, estos no apuntarán a la misma dirección de memoria.
 * @param[in]orig   objeto del que se copiarán todos los parámetros
 * @post    El objeto queda creado con los mismo parámetros que el original
 * @warning . El operado asignación de todos los objetos que se vayan a copiar debe estar bien implementado.
 * */
Aeropuerto::Aeropuerto(const Aeropuerto &orig): id(orig.id), ident(orig.ident), tipo(orig.tipo), nombre(orig.nombre), continente(orig.continente), isoPais(orig.isoPais) {

}

/**
 * @brief   Destructor de la clase Aeropuerto
 * @post    El objeto queda destruido
 * */
Aeropuerto::~Aeropuerto() {

}

const std::string &Aeropuerto::getId() const {
    return id;
}

void Aeropuerto::setId(const std::string &id) {
    this->id = id;
}

const std::string &Aeropuerto::getIdent() const {
    return ident;
}

void Aeropuerto::setIdent(const std::string &ident) {
    this->ident = ident;
}

const std::string &Aeropuerto::getTipo() const {
    return tipo;
}

void Aeropuerto::setTipo(const std::string &tipo) {
    this->tipo = tipo;
}

const std::string &Aeropuerto::getNombre() const {
    return nombre;
}

void Aeropuerto::setNombre(const std::string &nombre) {
    this->nombre = nombre;
}

const std::string &Aeropuerto::getContinente() const {
    return continente;
}

void Aeropuerto::setContinente(const std::string &continente) {
    this->continente = continente;
}

const std::string &Aeropuerto::getIsoPais() const {
    return isoPais;
}

void Aeropuerto::setIsoPais(const std::string &isoPais) {
    this->isoPais = isoPais;
}

UTM Aeropuerto::getPosicion() const{
    return posicion;
}

void Aeropuerto::setPosicion(const UTM& posicion) {
    this->posicion = posicion;
}

bool Aeropuerto::operator<(const Aeropuerto &orig) {
    return (stoi(this->id) < stoi(orig.id));
}

bool Aeropuerto::operator>(const Aeropuerto &orig) {
    return (stoi(this->id) > stoi(orig.id));
}