//
// Created by stefan on 23/10/2023.
//

#ifndef PRACTICA_1B_VUELAFLIGHT_H
#define PRACTICA_1B_VUELAFLIGHT_H

#include "ListaEnlaza.h"
#include "VDinamico.h"
#include "Ruta.h"

class VuelaFlight{
private:
    VDinamico<Aeropuerto> airports;
    ListaEnlazada<Ruta> routes;
public:
    //TODO eliminar el constructor por  defecto y parametrizado y agragar un construtor cuyos parñametros sean los archivos que va a cargar
    //Constructores y destructores
    VuelaFlight();
    ~VuelaFlight() = default;
    //Otros metodos
    void addAeropuerto(const Aeropuerto &aeropuerto);
    void ordenarAirports();
    Ruta *buscarRutasOriDes(const std::string &idAerOrig, const std::string &idAerDest);
    ListaEnlazada<Ruta*> buscarRutasOrigen(const std::string &idAerOrig);
    VDinamico<Aeropuerto*> buscarAeropuertoPais(const std::string &pais);
    void addNewRute(const std::string &idAerOrig, const std::string &idAerDest, const std::string &aerolin);

};

#endif //PRACTICA_1B_VUELAFLIGHT_H
