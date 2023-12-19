//
// Created by stefan on 09/10/2023.
//
#include "UTM.h"

/**
 * @brief   Constructor parametrizado de la clase UTM
 * @param[in]latitud    valor que tendrá el atributo latitud
 * @param[in]longitud   Valor que tendrá el atributo longitud
 * @post    El onjeto es creado con los valores que se han pasado como parámetro
 * */
UTM::UTM(float latitud, float longitud) : latitud(latitud), longitud(longitud) {

}

/**
 * @brief   Destructor de la clase UTM
 * */
UTM::~UTM() {

}

/**
 * @brief   Devuelve el valor del atributo latitud
 * @return  El valor del atributo latitud
 * */
float UTM::getLatitud() const {
    return latitud;
}

/**
 * @brief   Modifica el valor del atributo latitud
 * @param[in]latitud    Nuevo valor que tendrá el atributo latitud
 * @post    El atributo latitud queda modificado
 * */
void UTM::setLatitud(float latitud) {
    this->latitud = latitud;
}

/**
 * @brief   Devuelve el valor del atributo longitud
 * @return  El valor del atributo longitud
 * */
float UTM::getLongitud() const {
    return longitud;
}

/**
 * @brief   Modifica el valor del atributo longitud
 * @param[in]longitud   Nuevo valor que tendrá el atributo longitud
 * @post    El atributo longitud queda modificado
 * */
void UTM::setLongitud(float longitud) {
    this->longitud = longitud;
}
