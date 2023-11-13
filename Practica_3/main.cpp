#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "VDinamico.h"
#include "ListaEnlaza.h"
#include "Ruta.h"
#include "VuelaFlight.h"
#include "AVL.h"

/**
 * @author  Stefan Giovanni Imperato Lozano sgil0001@red.ujaen.es
 * @author  Carlos Martinez Sanchez cms00065@red.ujaen.es
 * @warning Si al ejecutar el programa aparece un error de compilación, modificar el archivo CMAKE para que la versión sea la siguiente: set(CMAKE_CXX_STANDARD 17)
 * */
int main(int argc, const char * argv[]) {

    //Programa prueba práctica 3


    //Creamos los objetos ifstream donde estarán almacenados los csv de los aeropuertos, aerolíneas y rutas
    std::ifstream aeropuertos;
    std::ifstream aerolineas;
    std::ifstream rutas;
    //Abirmos los archivos csv y los guardamos en los objetos ifstream
    aeropuertos.open("../aeropuertos_v2.csv");
    aerolineas.open("../aerolineas_v1.csv");
    rutas.open("../rutas_v1.csv");
    //Lamamos al constructor de vuelaflight para que se cree a partir de los ficheros csv
    VuelaFlight vuelaflight = VuelaFlight(aeropuertos,aerolineas,rutas);


    //Vicualizamos toda la información de la aerolinea rayanair
    Aerolinea ryn = vuelaflight.buscaAerolinea("RYR");
    if(&ryn){
        std::cout<< "ID: " <<ryn.getId() <<std::endl;
        std::cout<<"ICAO: " <<ryn.getIcao() <<std::endl;
        std::cout<<"Nombre: " <<ryn.getNombre() <<std::endl;
        std::cout<<"Pais: " <<ryn.getPais() <<std::endl;
        if(ryn.getActivo()){
            std::cout<<"Activa" <<std::endl;
        }else{
            std::cout<<"No activa" <<std::endl;
        }
    }


    //Muestra todas las aerolineas activas
    ListaEnlazada<Aerolinea*> aerolineasactivas = vuelaflight.buscarAerolineasActivas();
    ListaEnlazada<Aerolinea*>::Iterador iterador = aerolineasactivas.iterador();
    std::cout<<"Aerolineas activas: " <<std::endl;
    while (!iterador.fin()){
        std::cout<<"Nombre: " <<iterador.dato()->getNombre() <<std::endl;
        iterador.siguiente();
    }

    //Busca todos los aeropuertos origen en los que opera Iberia Airlines, con icao IBE
    Aerolinea ibe = vuelaflight.buscaAerolinea("IBE");
    VDinamico<Aeropuerto*> ibeAeropuertos = ibe.getAeropuertosOrigin();
    std::cout<<"Cantidad de aeropuetos: " <<ibeAeropuertos.tamLogigo() <<std::endl;

    //Busca todas las rutas operadas por Iberia Arilines con origen en el aeropuerto de Málaga(AGP)
    VDinamico<Ruta*> ibeRutasAGP = ibe.getRutasAeropuerto("AGP");
    std::cout<<"Cantidad de rutas: " <<ibeRutasAGP.tamLogigo() <<std::endl;

    //Ejercicio extra parejas Implementar el método VuelaFlight::getAerolineasPais(String idPais): Aerolinea[] que muestra todas las aerolíneas de un país dado como parámetro (utilizar el recorrido inorden). Para probarlo, muestra por pantalla la información de las aerolíneas que operan en España.
    std::cout<<"Mosrtamos todas las aerolineas que operan en Españna" <<std::endl;
    ListaEnlazada<Aerolinea*> listAerolineasEspagna = vuelaflight.getAerolineasPais("Spain");
    ListaEnlazada<Aerolinea*>::Iterador iteradorEspagna = listAerolineasEspagna.iterador();
    while (!iteradorEspagna.fin()){
        std::cout<<"Nombre: " <<iteradorEspagna.dato()->getNombre() <<std::endl;
        iteradorEspagna.siguiente();
    }




}
