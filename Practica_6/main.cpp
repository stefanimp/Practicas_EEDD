#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>

#include "Ruta.h"
#include "VuelaFlight.h"
#include "fecha.h"


/**
 * @author  Stefan Giovanni Imperato Lozano sgil0001@red.ujaen.es
 * @author  Carlos Martinez Sanchez cms00065@red.ujaen.es
 * @warning Si al ejecutar el programa aparece un error de compilación, modificar el archivo CMAKE para que la versión sea la siguiente: set(CMAKE_CXX_STANDARD 17)
 * */
int main(int argc, const char * argv[]) {


    //Primera parte. Programa prueba práctica 3.

    //Creamos los objetos ifstream donde estarán almacenados los csv de los aeropuertos, aerolíneas y rutas
    std::ifstream aeropuertos;
    std::ifstream aerolineas;
    std::ifstream rutas;
    std::ifstream flights;
    //Abirmos los archivos csv y los guardamos en los objetos ifstream
    aeropuertos.open("../aeropuertos_v3.csv");
    aerolineas.open("../aerolineas_v1.csv");
    rutas.open("../rutas_v1.csv");
    flights.open("../infovuelos_v1.csv");
    //Lamamos al constructor de vuelaflight para que se cree a partir de los ficheros csv
    VuelaFlight vuelaflight (aeropuertos,aerolineas,rutas,flights);
    vuelaflight.mostrarEstadoTabla();



    // 3. Buscar el aeropuerto con IATA "00AS" y mostrar sus datos. Tras esto, eliminar el aeropuerto con dicho codigo. Volver a buscar el aeropuerto borrado y, si no se encuentra, volver a insertarlo en el sistema. Mostrar el estado de la tabla para comprobar el n'umero de clisiones m'aximo que se han producido.
    Aeropuerto  airport00AS = *vuelaflight.buscaAeropuertoIata("00AS");
    if(&airport00AS){
        std::cout<<"Datos del aeropuerto 00AS: " <<std::endl;
        std::cout<<"IATA: " <<airport00AS.getIata() <<std::endl;
        std::cout<<"Tipo: " <<airport00AS.getTipo() <<std::endl;
        std::cout<<"Pais: " <<airport00AS.getIsoPais() <<std::endl;
        std::cout<<"Nombre: " <<airport00AS.getNombre() <<std::endl;
        std::cout<<"ID: " <<airport00AS.getId() <<std::endl;
        std::cout<<"Continente: " <<airport00AS.getContinente() <<std::endl;
        vuelaflight.eliminarAirport("00AS");
    }
    if(!vuelaflight.buscaAeropuertoIata("00AS")){
        vuelaflight.addAeropuerto(airport00AS);
        vuelaflight.mostrarEstadoTabla();
    }


    // 4. Eliminar todos los aeropuertos inactivos con el m'etodo implementado eliminarAeropuertoInactivo(). Comprobar el n'umero de aeropuertos registrados antes y despues de realizar esta operacion ademas del estado de la tabla.
    vuelaflight.eliminarAirportsInactivos();
    vuelaflight.mostrarEstadoTabla();

}
