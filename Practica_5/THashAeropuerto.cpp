//
// Created by stefan on 02/12/2023.
//

#include "THashAeropuerto.h"

unsigned long THashAeropuerto::siguientePrimo(unsigned long num) {
    if(num%2 == 0){
        ++num;
    }
    bool esPrimo = true;
    do{
        esPrimo = true;
        for (int i = 3; i < sqrt(num); ++i) {
            if(num%i == 0){
                esPrimo = false;
            }
        }
        if(!esPrimo){
            num += 2;
        }
    } while (!esPrimo);

    return num;
}

unsigned long THashAeropuerto::primoAnterior(unsigned long num) {
    if(num%2 == 0){
        ++num;
    }
    bool esPrimo = true;
    do {
        esPrimo = true;
        for (int i = 3; i < sqrt(num) ; ++i) {
            if(num%i == 0){
                esPrimo = false;
            }
        }
        if(!esPrimo){
            num -= 2;
        }
    } while (!esPrimo);

    return num;
}

THashAeropuerto::THashAeropuerto(long int maxElementos, float lambda):numElementos(0),maxColisiones(0), numMax10(0), totalColisiones(0),numRedipersiones(0) {
    tamReal = maxElementos/lambda;
    tamReal = siguientePrimo(tamReal);

    primoPorDebajoTam = tamReal - 2;
    primoPorDebajoTam = primoAnterior(primoPorDebajoTam);

    tabla = std::vector<Celda>(tamReal);
}


THashAeropuerto::THashAeropuerto(const THashAeropuerto &original):maxColisiones(original.maxColisiones),numMax10(original.numMax10),totalColisiones(original.totalColisiones),numRedipersiones(original.numRedipersiones) {
    if (&original == nullptr){
        throw std::invalid_argument("THashAeropuerto::THashAeropuerto(const THashAeropuerto &original, se estan copiando valores de un objeto que no existe");
    }
    numElementos = original.numElementos;
    tamReal = original.tamReal;
    tabla = std::vector<Celda>(tamReal);
    for (int i = 0; i < tamReal; ++i) {
        tabla[i] = original.tabla[i];
    }
}


THashAeropuerto::~THashAeropuerto() {

}


unsigned int THashAeropuerto::getnumElementos() const {
    return numElementos;
}


unsigned int THashAeropuerto::getTamTabla() const {
    return tamReal;
}


unsigned long THashAeropuerto::funcionHashing(const std::string &clave) {
    std::hash<std::string> hasher;
    size_t hasSize_T = hasher(clave);
    unsigned long claveDef = static_cast<unsigned long>(hasSize_T);
    return claveDef;
}


unsigned long THashAeropuerto::funcionDispersionCuadratica(unsigned long clave, int intento) {
    return ((clave + (intento*intento))%tamReal);
}

unsigned long THashAeropuerto::funcionDispersionDoble1(unsigned long clave, int intento) {
    return (((clave%tamReal) + intento*(primoPorDebajoTam - (clave%primoPorDebajoTam)))%tamReal);
}

unsigned long THashAeropuerto::funcionDispersionDoble2(unsigned long clave, int intento) {
    return (((clave%tamReal) + intento*(11 + (clave%primoPorDebajoTam)))%tamReal);
}



bool THashAeropuerto::insertarCuadratica(unsigned long clave, const std::string &iata, const Aeropuerto &aeropuerto) {
    int intento = 0;
    bool insertado = false;
    do{
        unsigned long posicion = funcionDispersionCuadratica(clave, intento);
        if(tabla[posicion].estado == Celda::OCUPADO && tabla[posicion].clave == clave && tabla[posicion].aeropuerto.getIata() == iata){
            return false;
        } else if(tabla[posicion].estado != Celda::OCUPADO ){
            tabla[posicion].aeropuerto = aeropuerto;
            tabla[posicion].estado = Celda::OCUPADO;
            tabla[posicion].clave = clave;
            ++numElementos;
            return true;
        }
        ++intento;
        if(intento > maxColisiones){
            maxColisiones = intento;
        }
        if(intento == 10){
            ++numMax10;
        }
        ++totalColisiones;
    } while (!insertado);
}


bool THashAeropuerto::insertarDoble1(unsigned long clave, const std::string &iata, const Aeropuerto &aeropuerto) {
    int intento = 0;
    bool insertado = false;
    do{
        unsigned long posicion = funcionDispersionDoble1(clave, intento);
        if(tabla[posicion].estado == Celda::OCUPADO && tabla[posicion].clave == clave && tabla[posicion].aeropuerto.getIata() == iata){
            return false;
        } else if(tabla[posicion].estado != Celda::OCUPADO ){
            tabla[posicion].aeropuerto = aeropuerto;
            tabla[posicion].estado = Celda::OCUPADO;
            tabla[posicion].clave = clave;
            ++numElementos;
            return true;
        }
        ++intento;
        if(intento > maxColisiones){
            maxColisiones = intento;
        }
        if(intento == 10){
            ++numMax10;
        }
        ++totalColisiones;
    } while (!insertado);
}

bool THashAeropuerto::insertarDoble2(unsigned long clave, const std::string &iata, const Aeropuerto &aeropuerto) {
    int intento = 0;
    bool insertado = false;
    do{
        unsigned long posicion = funcionDispersionDoble2(clave, intento);
        if(tabla[posicion].estado == Celda::OCUPADO && tabla[posicion].clave == clave && tabla[posicion].aeropuerto.getIata() == iata){
            return false;
        } else if(tabla[posicion].estado != Celda::OCUPADO ){
            tabla[posicion].aeropuerto = aeropuerto;
            tabla[posicion].estado = Celda::OCUPADO;
            tabla[posicion].clave = clave;
            ++numElementos;
            if(getFactorCarga() > 0.7){
                redispersarDoble2((tamReal + (tamReal*0.3)));
            }
            return true;
        }
        ++intento;
        if(intento > maxColisiones){
            maxColisiones = intento;
        }
        if(intento == 10){
            ++numMax10;
        }
        ++totalColisiones;
    } while (!insertado);
}


Aeropuerto *THashAeropuerto::buscarCuadratica(unsigned long clave, const std::string &iata) {
    int intento = 0;
    bool encontrado = false;
    do {
        unsigned long posicion = funcionDispersionCuadratica(clave,intento);
        if (tabla[posicion].estado == Celda::LIBRE){   // Si es 0 la celda esta libre y por tanto no existe el objeto buscado
            return nullptr;
        }else if(tabla[posicion].estado == Celda::OCUPADO && tabla[posicion].clave == clave && tabla[posicion].aeropuerto.getIata() == iata){
            return &tabla[posicion].aeropuerto;
        }else{  // si aqui antes habia un objeto deberemos segur buscando
            ++intento;
        }
    }while (!encontrado);
}

Aeropuerto *THashAeropuerto::buscarDoble1(unsigned long clave, const std::string &iata) {
    int intento = 0;
    bool encontrado = false;
    do {
        unsigned long posicion = funcionDispersionDoble1(clave,intento);
        if (tabla[posicion].estado == Celda::LIBRE){   // Si es 0 la celda esta libre y por tanto no existe el objeto buscado
            return nullptr;
        }else if(tabla[posicion].estado == Celda::OCUPADO && tabla[posicion].clave == clave && tabla[posicion].aeropuerto.getIata() == iata){
            return &tabla[posicion].aeropuerto;
        }else{  // si aqui antes habia un objeto deberemos segur buscando
            ++intento;
        }
    }while (!encontrado);
}

Aeropuerto *THashAeropuerto::buscarDoble2(unsigned long clave, const std::string &iata) {
    int intento = 0;
    bool encontrado = false;
    do {
        unsigned long posicion = funcionDispersionDoble2(clave,intento);
        if (tabla[posicion].estado == Celda::LIBRE){   // Si es 0 la celda esta libre y por tanto no existe el objeto buscado
            return nullptr;
        }else if(tabla[posicion].estado == Celda::OCUPADO && tabla[posicion].clave == clave && tabla[posicion].aeropuerto.getIata() == iata){
            return &tabla[posicion].aeropuerto;
        }else{  // si aqui antes habia un objeto deberemos segur buscando
            ++intento;
        }
    }while (!encontrado);
}


bool THashAeropuerto::borrarCuadratica(unsigned long clave, const std::string &iata) {
    int intento = 0;
    bool encontrado = false;
    do {
        unsigned long posicion = funcionDispersionCuadratica(clave,intento);
        if (tabla[posicion].estado == Celda::LIBRE){   // Si es 0 la celda esta libre y por tanto no existe el objeto buscado
            return false;
        }else if(tabla[posicion].estado == 1 && tabla[posicion].clave == clave && tabla[posicion].aeropuerto.getIata() == iata){
            tabla[posicion].estado = Celda::BORRADO;
            --numElementos;
            return true;
        }else{  // si aqui antes habia un objeto deberemos segur buscando
            ++intento;
        }
    }while (!encontrado);
}

bool THashAeropuerto::borrarDoble1(unsigned long clave, const std::string &iata) {
    int intento = 0;
    bool encontrado = false;
    do {
        unsigned long posicion = funcionDispersionDoble1(clave,intento);
        if (tabla[posicion].estado == Celda::LIBRE){   // Si es 0 la celda esta libre y por tanto no existe el objeto buscado
            return false;
        }else if(tabla[posicion].estado == 1 && tabla[posicion].clave == clave && tabla[posicion].aeropuerto.getIata() == iata){
            tabla[posicion].estado = Celda::BORRADO;
            --numElementos;
            return true;
        }else{  // si aqui antes habia un objeto deberemos segur buscando
            ++intento;
        }
    }while (!encontrado);
}

bool THashAeropuerto::borrarDoble2(unsigned long clave, const std::string &iata) {
    int intento = 0;
    bool encontrado = false;
    do {
        unsigned long posicion = funcionDispersionDoble2(clave,intento);
        if (tabla[posicion].estado == Celda::LIBRE){   // Si es 0 la celda esta libre y por tanto no existe el objeto buscado
            return false;
        }else if(tabla[posicion].estado == 1 && tabla[posicion].clave == clave && tabla[posicion].aeropuerto.getIata() == iata){
            tabla[posicion].estado = Celda::BORRADO;
            --numElementos;
            return true;
        }else{  // si aqui antes habia un objeto deberemos segur buscando
            ++intento;
        }
    }while (!encontrado);
}


unsigned int THashAeropuerto::getMaxColisiones() const {
    return maxColisiones;
}

unsigned int THashAeropuerto::getNumMax10() const {
    return numMax10;
}

unsigned long int THashAeropuerto::getPromedioColisiones() const {
    return totalColisiones/numElementos;
}

float THashAeropuerto::getFactorCarga() const {
    float numEle = numElementos;
    float tamR = tamReal;
    return numEle/tamR;
}

int THashAeropuerto::getNumRedispersiones() const {
    return numRedipersiones;
}

//TODO hacer esta funcion
THashAeropuerto &THashAeropuerto::operator=(const THashAeropuerto &original) {

}



Aeropuerto& THashAeropuerto::operator[](long unsigned int posicion) {
    Aeropuerto *airpot = nullptr;
    if(tabla[posicion].estado == Celda::OCUPADO){
        return tabla[posicion].aeropuerto;
    }
    return *airpot;
}

void THashAeropuerto::redispersarDoble2(unsigned int tam) {
    ++numRedipersiones;
    tamReal = siguientePrimo(tam);
    primoPorDebajoTam = primoAnterior(tamReal-2);
    std::vector<Celda> newVec = std::vector<Celda>(tamReal);
    numElementos = 0;
    maxColisiones = 0;
    numMax10 = 0;
    totalColisiones = 0;

    for (int i = 0; i < tabla.size(); ++i) {
        if (tabla[i].estado == Celda::OCUPADO){
            int intento = 0;
            bool insertado = false;
            do{
                unsigned long position = funcionDispersionDoble2(tabla[i].clave,intento);
                if(newVec[position].estado != Celda::OCUPADO) {
                    newVec[position].estado = Celda::OCUPADO;
                    newVec[position].aeropuerto = tabla[i].aeropuerto;
                    newVec[position].clave = tabla[i].clave;
                    ++numElementos;
                    insertado = true;
                }
                if(intento > maxColisiones){
                    maxColisiones = intento;
                }
                if(intento == 10){
                    ++numMax10;
                }
                if(!insertado){
                    ++totalColisiones;
                    ++intento;
                }

            } while (!insertado);
        }
    }

    tabla = newVec;

}









