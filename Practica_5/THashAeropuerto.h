//
// Created by stefan on 29/11/2023.
//

#ifndef PRACTICA_2_THASHAEROPUERTO_H
#define PRACTICA_2_THASHAEROPUERTO_H

#include "Aeropuerto.h"
#include <vector>
#include <cmath>
#include <functional>


class THashAeropuerto{
private:
    class Celda{
    public:
        unsigned long clave;
        Aeropuerto aeropuerto;
        //int estado; // 0=LIBRE, 1=OCUPADO, 2=BORRADO
        enum {LIBRE,OCUPADO,BORRADO} estado = LIBRE;


        Celda():estado(LIBRE){

        }
        Celda(const Aeropuerto &aeropuerto):estado(OCUPADO), clave(funcionHashing(aeropuerto.getIata())),aeropuerto(aeropuerto){

        }

        Celda(const Celda &original):estado(original.estado), clave(original.clave), aeropuerto(original.aeropuerto){

        }

        ~Celda(){

        }

        Celda& operator=(const Celda &original){
            if(this != &original){
                clave = original.clave;
                aeropuerto = Aeropuerto(original.aeropuerto);
                estado = original.estado;
            }
            return *this;
        }

    };


    long int numElementos;
    long int tamReal; // Como el tamaño fisico de un vector dinamico
    long int primoPorDebajoTam; // El primer numero primo menor que el tamaño de la tabla
    std::vector<Celda> tabla;
    //TODO que tiene que devolver esto?
    // Esta sera de dispersion cuadratica
    unsigned long int funcionDispersionCuadratica(unsigned long clave, int intento);
    unsigned long int funcionDispersionDoble1(unsigned long clave, int intento);
    unsigned long int funcionDispersionDoble2(unsigned long clave, int intento);
    unsigned long int siguientePrimo(unsigned long int num);
    unsigned long int primoAnterior(unsigned long int num);
    unsigned int maxColisiones; // maximo de colisiones que se han producido de entre todas las operaciones de insercion
    unsigned int numMax10;      // numero de veces que se han superado las 10 colisiones al intentar hacer una insercion de entre todas las inserciones
    unsigned long int totalColisiones;
    unsigned int numRedipersiones;
public:

    static unsigned long funcionHashing(const std::string &clave);
    THashAeropuerto(long int maxElementos, float lambda = 0.7);
    THashAeropuerto(const THashAeropuerto &original);
    ~THashAeropuerto();
    // Hacemos los metodos inline para que no haya costo extra al hacer las llamdas a las otra funciones, si estuvieran declarados en el cpp seria mas costoso
    // Métodos para insertar
    bool insertarCuadratica(const std::string &iata, const Aeropuerto &aeropuerto){
        unsigned long clave = funcionHashing(iata);
        insertarCuadratica(clave,iata,aeropuerto);
    }
    bool insertarCuadratica(unsigned long clave, const std::string &iata, const Aeropuerto &aeropuerto);
    bool insertarDoble1(const std::string &iata, const Aeropuerto &aeropuerto){
        unsigned long clave = funcionHashing(iata);
        insertarDoble1(clave, iata, aeropuerto);
    }
    bool insertarDoble1(unsigned long clave, const std::string &iata, const Aeropuerto &aeropuerto);
    bool insertarDoble2(const std::string &iata, const Aeropuerto &aeropuerto){
        unsigned long clave = funcionHashing(iata);
        insertarDoble2(clave, iata, aeropuerto);

    }
    bool insertarDoble2(unsigned long clave, const std::string &iata, const Aeropuerto &aeropuerto);
    // Métodos para buscar
    Aeropuerto* buscarCuadratica(const std::string &iata){
        unsigned long clave = funcionHashing(iata);
        buscarCuadratica(clave,iata);
    }
    Aeropuerto* buscarCuadratica(unsigned long clave, const std::string &iata);
    Aeropuerto* buscarDoble1(const std::string &iata){
        unsigned long clave = funcionHashing(iata);
        buscarDoble1(clave,iata);
    }
    Aeropuerto* buscarDoble1(unsigned long clave, const std::string &iata);
    Aeropuerto* buscarDoble2(const std::string &iata){
        unsigned long clave = funcionHashing(iata);
        buscarDoble2(clave,iata);
    }
    Aeropuerto* buscarDoble2(unsigned long clave, const std::string &iara);
    // Métodos borrar
    bool borrarCuadratica(const std::string &iata){
        unsigned long clave = funcionHashing(iata);
        borrarCuadratica(clave,iata);
    }
    bool borrarCuadratica(unsigned long clave, const std::string &iata);
    bool borrarDoble1(const std::string &iata){
        unsigned long clave = funcionHashing(iata);
        borrarDoble1(clave,iata);
    }
    bool borrarDoble1(unsigned long clave, const std::string &iata);
    bool borrarDoble2(const std::string &iata){
        unsigned long clave = funcionHashing(iata);
        borrarDoble2(clave,iata);
    }
    bool borrarDoble2(unsigned long clave, const std::string &iata);
    // Getters y setters
    unsigned int getnumElementos() const;
    unsigned int getTamTabla() const;
    unsigned int getMaxColisiones() const;
    unsigned int getNumMax10() const;
    unsigned long int getPromedioColisiones() const;
    float getFactorCarga() const;
    int getNumRedispersiones() const;
    // Otros metodos
    void redispersarDoble2(unsigned tam);

    // Operadores
    THashAeropuerto& operator=(const THashAeropuerto &original);
    Aeropuerto& operator[] (long unsigned int posicion);
};

#endif //PRACTICA_2_THASHAEROPUERTO_H
