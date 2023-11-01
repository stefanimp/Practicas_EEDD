//
// Created by stefan on 23/10/2023.
//

// IMPORTANTE cuando en la práctica pide que se busque por id se refiere al iata

#include "VuelaFlight.h"

VuelaFlight::VuelaFlight() {

}

void VuelaFlight::ordenarAirports() {
    airports.ordenar();
}

//TODO como inserta lanza excepciones, donde debería poner el try y el catch para mostrar el mensaje de error Cuando este resuelta la duda apuntarlo en los apuintes de excepciones de obsifian
/**
 * @brief   Inserta un auropuerto nuevo en el vector dinámico de aeropuertos
 * @param[in]aeropuerto objeto aeropuerto que se quiere insertar
 * @post    Un nuevo aeropuerto es añadido
 * */
void VuelaFlight::addAeropuerto(const Aeropuerto &aeropuerto) {
    this->airports.insertar(aeropuerto);
}


/**
 * @brief   Busca una ruta que coincida con el id del aeropuerto de origen y de destino
 * @param[in]idAerOrig  iata de l aeropuerto de origen
 * @param[in]idAerDest  iata del aeropuerto de destino
 * @return  Devuelve, si se ha encontrado, la ruta con las características exigidas
 * @return  Devuelve, si no se ha encontrado la ruta especificada, un puetero a nulo
 * */
Ruta* VuelaFlight::buscarRutasOriDes(const std::string &idAerOrig, const std::string &idAerDest) {
    ListaEnlazada<Ruta>::Iterador iterador = routes.iterador();
    Ruta *ruta = nullptr;

    while (!iterador.fin()){
        if(iterador.dato().getOrigin().getIata() == idAerOrig && iterador.dato().getDestination().getIata() == idAerDest){
            return &(iterador.dato());
        }
        iterador.siguiente();
    }
    return ruta;
}

// Devuelvo una lista de punteros a rutas
ListaEnlazada<Ruta*> VuelaFlight::buscarRutasOrigen(const std::string &idAerOrig) {
    ListaEnlazada<Ruta*> listaNueva;
    ListaEnlazada<Ruta>::Iterador iterador = routes.iterador();

    //TODO ESTO ESTA BIEN?
    while (!iterador.fin()){
        if(iterador.dato().getOrigin().getIata() == idAerOrig){
            listaNueva.insertarFinal(&(iterador.dato()));
        }
        iterador.siguiente();
    }
    return listaNueva;
}

//TODO se puede hacer con busqueda binaria?
VDinamico<Aeropuerto*> VuelaFlight::buscarAeropuertoPais(const std::string &pais) {
    VDinamico<Aeropuerto*> nuevoVDim;

    for (int i = 0; i < airports.tamLogigo(); ++i) {
        if (airports[i].getIsoPais() == pais){
            nuevoVDim.insertar(&airports[i]);
        }
    }
    return nuevoVDim;

}
// TODO se puede hacer con busqueda binaria?
void VuelaFlight::addNewRute(const std::string &idAerOrig, const std::string &idAerDest, const std::string &aerolin) {
    Ruta rutanueva;
    rutanueva.setAerolinea(aerolin);

    for (int i = 0; i < airports.tamLogigo(); ++i) {
        if(airports[i].getIata() == idAerOrig){
            rutanueva.setOrigin(airports[i]);
        }
        if(airports[i].getIata() == idAerDest){
            rutanueva.setDestination(airports[i]);
        }
    }

    routes.insertarFinal(rutanueva);
}
