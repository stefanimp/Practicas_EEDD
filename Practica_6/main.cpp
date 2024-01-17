#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>

#include "Ruta.h"
#include "VuelaFlight.h"
#include "fecha.h"

float distanciaPtsHaversine(float lat1, float long1, float lat2, float long2){
    constexpr float R = 6371.0; // Radio de la Tierra en kilómetros

    // Convertir grados a radianes
    float lat1Rad = lat1 * (M_PI / 180.0);
    float long1Rad = long1 * (M_PI / 180.0);
    float lat2Rad = lat2 * (M_PI / 180.0);
    float long2Rad = long2 * (M_PI / 180.0);

    // Calcular diferencias en latitud y longitud
    float deltaLat = lat2Rad - lat1Rad;
    float deltaLong = long2Rad - long1Rad;

    // Fórmula de Haversine
    float a = std::sin(deltaLat / 2) * std::sin(deltaLat / 2) +
              std::cos(lat1Rad) * std::cos(lat2Rad) *
              std::sin(deltaLong / 2) * std::sin(deltaLong / 2);
    float c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    float distancia = R * c;

    return distancia;
}

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
    vuelaflight.mostrarEstadoMalla();




    UTM coordenadasJaen = UTM(37.7692200, -3.7902800);
    std::vector<Aeropuerto*> vectAirports = vuelaflight.buscarAriportsRadio(coordenadasJaen,300);
    std::cout<<"====================================================" <<std::endl;
    std::cout<<"Aeropuertos en un radio de 300km a Jaen capital: " <<std::endl;
    for (int i = 0; i < vectAirports.size(); ++i) {
        std::cout<<vectAirports[i]->getIata() <<std::endl;
    }
    std::cout<<"====================================================" <<std::endl;
    std::cout<<"Aeropuerto mas cercano a Jaen capital: " <<std::endl;
    float distanciaMenor = distanciaPtsHaversine(coordenadasJaen.getLatitud(), coordenadasJaen.getLongitud(), vectAirports[0]->getY(), vectAirports[0]->getX());
    Aeropuerto *airportMasCercanoJaen = vectAirports[0];
    for (int i = 0; i < vectAirports.size(); ++i) {
        if(distanciaPtsHaversine(coordenadasJaen.getLatitud(), coordenadasJaen.getLongitud(), vectAirports[i]->getY(), vectAirports[i]->getX()) < distanciaMenor){
            distanciaMenor = distanciaPtsHaversine(coordenadasJaen.getLatitud(), coordenadasJaen.getLongitud(), vectAirports[i]->getY(), vectAirports[i]->getX());
            airportMasCercanoJaen = vectAirports[i];
        }
    }
    std::cout<<airportMasCercanoJaen->getIata() <<std::endl;


    std::cout<<"====================================================" <<std::endl;
    std::cout<<"Nombres de los 5 aeropuertos con mas vuelos de en un radio de 800km desde la capital de madrid:  " <<std::endl;
    UTM coordenadasMadird(40.4165,-3.70256);
    std::list<Aeropuerto*> listAirports = vuelaflight.airportsMasSalidas(coordenadasMadird, 800);
    std::list<Aeropuerto*>::iterator itListAirportsMasFlightsMdz = listAirports.begin();
    while (itListAirportsMasFlightsMdz != listAirports.end()){
        std::cout<<(*itListAirportsMasFlightsMdz)->getIata() <<std::endl;
        ++itListAirportsMasFlightsMdz;
    }


    std::cout<<"====================================================" <<std::endl;
    std::cout<<"La ciudad europea, Londres o Venecia, concentra más aeropuertos en un radio de 400Km es: " <<std::endl;
    UTM coordenadasLondon = UTM(51.499854, -0.281591);
    std::vector<Aeropuerto*> vectAirportsLondon = vuelaflight.buscarAriportsRadio(coordenadasLondon,400);
    UTM coordenadasVenezia = UTM(45.497652, 12.216734);
    std::vector<Aeropuerto*> vectAirportsVenezia = vuelaflight.buscarAriportsRadio(coordenadasVenezia,400);
    if(vectAirportsLondon.size() > vectAirportsVenezia.size()){
        std::cout<<"Es London" <<std::endl;
    }else if(vectAirportsLondon.size() < vectAirportsVenezia.size()){
        std::cout<<"Es Venezia" <<std::endl;
    }else{
        std::cout<<"Tiene los mismos" <<std::endl;
    }



    std::cout<<"====================================================" <<std::endl;
    std::cout<<"Ejercicio por parejas. Aganadir unn nuevo aeropuerto a vuelaflight en el que solo opera la aerolinea IBERIA. " <<std::endl
    <<"Este hara las rutas Jaen-Madrid, Jaen-Barcelona y sus respectivas vueltas. Y agnadir a la aerolinea las nuevas rutas." <<std::endl
    <<"Obtener todos los aeropuertos en un radio de 300km de Antequera (37.0193800, -4.5612300) y  visualizar sus datos para comprobar que aparece el nuevo aeropuerto creado." <<std::endl;
    Aeropuerto airportJaen(65538,"JEN","medium_airport","Aeropuerto de Jaen",coordenadasJaen,"EU","ES");
    vuelaflight.addAirportPostConst(airportJaen);
    Aerolinea *iberia = vuelaflight.buscaAerolinea("IBE");
    Aeropuerto *airportMad = vuelaflight.buscaAeropuertoIata("MAD");
    Aeropuerto *airportBcn = vuelaflight.buscaAeropuertoIata("BCN");
    iberia->linkAerolRuta(vuelaflight.addNewRute(airportJaen.getIata(), airportMad->getIata(), iberia->getNombre()));
    iberia->linkAerolRuta(vuelaflight.addNewRute(airportJaen.getIata(), airportBcn->getIata(), iberia->getNombre()));
    UTM coordenadasAntequera = UTM(37.0193800, -4.5612300);
    std::vector<Aeropuerto*> vectAirportsAntequera = vuelaflight.buscarAriportsRadio(coordenadasAntequera,300);
    for (int i = 0; i < vectAirportsAntequera.size(); ++i) {
        std::cout<<vectAirportsAntequera[i]->getIata() <<std::endl;
    }
    
}
