//
// Created by stefan on 23/10/2023.
//

#ifndef PRACTICA_1B_VUELAFLIGHT_H
#define PRACTICA_1B_VUELAFLIGHT_H

#include "ListaEnlaza.h"
#include "VDinamico.h"
#include "Ruta.h"
#include "AVL.h"

class VuelaFlight{
private:
    VDinamico<Aeropuerto> airports;
    ListaEnlazada<Ruta> routes;
    AVL<Aerolinea> aerolines;

public:
    //Constructores y destructores
    VuelaFlight();
    VuelaFlight(std::ifstream &fichAirports, std::ifstream &fichRoutes, std::ifstream &fichAerolines);
    ~VuelaFlight() = default;
    //Otros metodos
    void addAeropuerto(const Aeropuerto &aeropuerto);
    void ordenarAirports();
    Ruta *buscarRutasOriDes(const std::string &idAerOrig, const std::string &idAerDest);
    ListaEnlazada<Ruta*> buscarRutasOrigen(const std::string &idAerOrig);
    ListaEnlazada<Aeropuerto*> buscarAeropuertoPais(const std::string &pais);
    Ruta* addNewRute(const std::string &idAerOrig, const std::string &idAerDest, const std::string &aerolin);
    Aerolinea& buscaAerolinea(const std::string &icaoAerolinea);
    ListaEnlazada<Aerolinea*> buscarAerolineasActivas();
    ListaEnlazada<Aerolinea*> getAerolineasPais(const std::string &idPais);
};

#endif //PRACTICA_1B_VUELAFLIGHT_H
