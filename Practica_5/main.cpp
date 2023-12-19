#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>

#include "Ruta.h"
#include "VuelaFlight.h"
#include "VuelaFilghtDoble1.h"
#include "VuelaFlightDoble2.h"
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
/*
    std::cout<<"============================================================================================================" <<std::endl;
    std::cout<<"Segunda versión de VuelaFlight con dispersión cuadratica de la tabla Hash y lambda 0.65" <<std::endl;
    std::cout<<"============================================================================================================" <<std::endl;
    //Abirmos los archivos csv y los guardamos en los objetos ifstream
    aeropuertos.open("../aeropuertos_v3.csv");
    aerolineas.open("../aerolineas_v1.csv");
    rutas.open("../rutas_v1.csv");
    flights.open("../infovuelos_v1.csv");
    //Lamamos al constructor de vuelaflight para que se cree a partir de los ficheros csv
    VuelaFlight vuelaflight1 = VuelaFlight(aeropuertos,aerolineas,rutas,flights,76366,0.65);
    vuelaflight1.mostrarEstadoTabla();


    std::cout<<"============================================================================================================" <<std::endl;
    std::cout<<"Segunda versión de VuelaFlight con dispersión cuadratica de la tabla Hash y lambda 0.68" <<std::endl;
    std::cout<<"============================================================================================================" <<std::endl;
    //Abirmos los archivos csv y los guardamos en los objetos ifstream
    aeropuertos.open("../aeropuertos_v3.csv");
    aerolineas.open("../aerolineas_v1.csv");
    rutas.open("../rutas_v1.csv");
    flights.open("../infovuelos_v1.csv");
    //Lamamos al constructor de vuelaflight para que se cree a partir de los ficheros csv
    VuelaFlight vuelaflight1_2 = VuelaFlight(aeropuertos,aerolineas,rutas,flights,76366,0.68);
    vuelaflight1_2.mostrarEstadoTabla();



    // Ahora la segunda versión de VuelaFlight usando la dipsersion doble 1 de la tabla hash
    std::cout<<"============================================================================================================" <<std::endl;
    std::cout<<"Segunda versión de VuelaFlight con dispersión doble 1 de la tabla Hash y lambda 0.65" <<std::endl;
    std::cout<<"============================================================================================================" <<std::endl;
    //Abirmos los archivos csv y los guardamos en los objetos ifstream
    aeropuertos.open("../aeropuertos_v3.csv");
    aerolineas.open("../aerolineas_v1.csv");
    rutas.open("../rutas_v1.csv");
    flights.open("../infovuelos_v1.csv");
    //Lamamos al constructor de vuelaflight para que se cree a partir de los ficheros csv
    VuelaFlightDoble1 vuelaflight2_1 = VuelaFlightDoble1(aeropuertos,aerolineas,rutas,flights,76366,0.65);
    vuelaflight2_1.mostrarEstadoTabla();

    std::cout<<"============================================================================================================" <<std::endl;
    std::cout<<"Segunda versión de VuelaFlight con dispersión doble 1 de la tabla Hash y lambda 0.68" <<std::endl;
    std::cout<<"============================================================================================================" <<std::endl;
    //Abirmos los archivos csv y los guardamos en los objetos ifstream
    aeropuertos.open("../aeropuertos_v3.csv");
    aerolineas.open("../aerolineas_v1.csv");
    rutas.open("../rutas_v1.csv");
    flights.open("../infovuelos_v1.csv");
    //Lamamos al constructor de vuelaflight para que se cree a partir de los ficheros csv
    VuelaFlightDoble1 vuelaflight2_2 = VuelaFlightDoble1(aeropuertos,aerolineas,rutas,flights,76366,0.68);
    vuelaflight2_2.mostrarEstadoTabla();

*/

    // Ahora la segunda versión de VuelaFlight usando la dipsersion doble 2 de la tabla hash
    std::cout<<"============================================================================================================" <<std::endl;
    std::cout<<"Tercera versión de VuelaFlight con dispersión doble 2 de la tabla Hash y lambda 0.65" <<std::endl;
    std::cout<<"============================================================================================================" <<std::endl;
    //Abirmos los archivos csv y los guardamos en los objetos ifstream
    aeropuertos.open("../aeropuertos_v3.csv");
    aerolineas.open("../aerolineas_v1.csv");
    rutas.open("../rutas_v1.csv");
    flights.open("../infovuelos_v1.csv");
    //Lamamos al constructor de vuelaflight para que se cree a partir de los ficheros csv
    VuelaFlightDoble2 vuelaflight3_1 = VuelaFlightDoble2(aeropuertos,aerolineas,rutas,flights,76366,0.65);
    vuelaflight3_1.mostrarEstadoTabla();
/*
    std::cout<<"============================================================================================================" <<std::endl;
    std::cout<<"Tercera versión de VuelaFlight con dispersión doble 2 de la tabla Hash y lambda 0.68" <<std::endl;
    std::cout<<"============================================================================================================" <<std::endl;
    //Abirmos los archivos csv y los guardamos en los objetos ifstream
    aeropuertos.open("../aeropuertos_v3.csv");
    aerolineas.open("../aerolineas_v1.csv");
    rutas.open("../rutas_v1.csv");
    flights.open("../infovuelos_v1.csv");
    //Lamamos al constructor de vuelaflight para que se cree a partir de los ficheros csv
    VuelaFlightDoble2 vuelaflight3_2 = VuelaFlightDoble2(aeropuertos,aerolineas,rutas,flights,76366,0.68);
    vuelaflight3_2.mostrarEstadoTabla();
 */

    // Programa de prueba 1
    // Hemos elegido vuelaflight3_1 como la mejor opcion, seguiremos trabajando con este.
    std::vector<Aeropuerto*> vectorAeropuertos = vuelaflight3_1.getAeropuertosVector();
    const int RANGO_MIN = 0;
    const int RANGO_MAX = vectorAeropuertos.size();

    clock_t t_inicio = clock();
    for (int i = 0; i < 1000000; ++i) {
        vuelaflight3_1.buscaAeropuertoIata(vectorAeropuertos[(rand() % vectorAeropuertos.size())]->getIata());
    }
    std::cout <<std::endl <<"Tiempo empleado pata leer 1.000.000 (10^6) datos en la tabla hash con la configuracion seleccionada " <<((clock()-t_inicio)/(float) CLOCKS_PER_SEC) <<" segundos." <<std::endl;


    std::map<std::string, Aeropuerto> mapAirports;
    for (int i = 0; i < RANGO_MAX; ++i) {
        mapAirports.insert(std::pair<std::string, Aeropuerto>(vectorAeropuertos[i]->getIata(),*vectorAeropuertos[i]));
    }

    clock_t t_inicio2 = clock();
    for (int i = 0; i < 1000000; ++i) {
        mapAirports.find(vectorAeropuertos[(rand() % vectorAeropuertos.size())]->getIata());
    }
    std::cout <<std::endl <<"Tiempo empleado pata leer 1.000.000 (10^6) datos en un map de aeropuertos: " <<((clock()-t_inicio2)/(float) CLOCKS_PER_SEC) <<" segundos." <<std::endl;

    // 3. Buscar el aeropuerto con IATA "00AS" y mostrar sus datos. Tras esto, eliminar el aeropuerto con dicho codigo. Volver a buscar el aeropuerto borrado y, si no se encuentra, volver a insertarlo en el sistema. Mostrar el estado de la tabla para comprobar el n'umero de clisiones m'aximo que se han producido.
    Aeropuerto * airport00AS = vuelaflight3_1.buscaAeropuertoIata("00AS");
    if(airport00AS){
        std::cout<<"Datos del aeropuerto 00AS: " <<std::endl;
        std::cout<<"IATA: " <<airport00AS->getIata() <<std::endl;
        std::cout<<"Tipo: " <<airport00AS->getTipo() <<std::endl;
        std::cout<<"Pais: " <<airport00AS->getIsoPais() <<std::endl;
        std::cout<<"Nombre: " <<airport00AS->getNombre() <<std::endl;
        std::cout<<"ID: " <<airport00AS->getId() <<std::endl;
        std::cout<<"Continente: " <<airport00AS->getContinente() <<std::endl;
        vuelaflight3_1.eliminarAirport("00AS");
    }
    if(!vuelaflight3_1.buscaAeropuertoIata("00AS")){
        vuelaflight3_1.addAeropuerto(*airport00AS);
        vuelaflight3_1.mostrarEstadoTabla();
    }

    // 4. Eliminar todos los aeropuertos inactivos con el m'etodo implementado eliminarAeropuertoInactivo(). Comprobar el n'umero de aeropuertos registrados antes y despues de realizar esta operacion ademas del estado de la tabla.
    vuelaflight3_1.eliminarAirportsInactivos();
    vuelaflight3_1.mostrarEstadoTabla();

    // Redispersion de la tabla
    std::cout<<"============================================================================================================" <<std::endl;
    std::cout<<"Cuarta versión de VuelaFlight con dispersión doble 2 de la tabla Hash y lambda 0.5 para que se redispersione" <<std::endl;
    std::cout<<"============================================================================================================" <<std::endl;
    //Abirmos los archivos csv y los guardamos en los objetos ifstream
    aeropuertos.open("../aeropuertos_v3.csv");
    aerolineas.open("../aerolineas_v1.csv");
    rutas.open("../rutas_v1.csv");
    flights.open("../infovuelos_v1.csv");
    //Lamamos al constructor de vuelaflight para que se cree a partir de los ficheros csv
    VuelaFlightDoble2 vuelaflight4 = VuelaFlightDoble2(aeropuertos,aerolineas,rutas,flights,76366,0.8);
    vuelaflight4.mostrarEstadoTabla();


/*
    std::list<Vuelo*> listVuelos = vuelaflight.buscaVuelos("AEA5201");
    std::list<Vuelo*>::iterator iteratorVuelos = listVuelos.begin();
    std::cout<<"El aeropuerto origen del vuelo AEA5201 es: " <<(*iteratorVuelos)->getAeropuertoOrigin()->getIata() <<std::endl;
    Aerolinea *aerolineAEA = (*iteratorVuelos)->getAerolinea();
    aerolineAEA->bajaAeropuerto("AEA");
    listVuelos = vuelaflight.buscaVuelos("AEA5201");
    iteratorVuelos = listVuelos.begin();
    std::cout<<"El aeropuerto origen del vuelo AEA5201 es: " <<(*iteratorVuelos)->getAeropuertoOrigin()->getIata() <<std::endl;
*/








/*
    std::cout<<"============================================================================================================" <<std::endl;
    //Visualizamos toda la información de la aerolinea rayanair
    Aerolinea *ryn = vuelaflight.buscaAerolinea("RYR");
    std::cout<<std::endl <<"Datos Aerloliea Rayanair: " <<std::endl;
    if(&ryn){
        std::cout<< "ID: " <<ryn->getId() <<std::endl;
        std::cout<<"ICAO: " <<ryn->getIcao() <<std::endl;
        std::cout<<"Nombre: " <<ryn->getNombre() <<std::endl;
        std::cout<<"Pais: " <<ryn->getPais() <<std::endl;
        if(ryn->getActivo()){
            std::cout<<"Activa" <<std::endl;
        }else{
            std::cout<<"No activa" <<std::endl;
        }
    }
    std::cout<<"============================================================================================================" <<std::endl;


    //Muestra todas las aerolineas activas
    std::cout<<"============================================================================================================" <<std::endl;
    std::cout<<std::endl <<"Aeroineas activas: " <<std::endl;
    std::list<Aerolinea*> aerolineasactivas = vuelaflight.buscarAerolineasActivas();
    std::cout<<std::endl <<"Numero de aeroineas activas: " <<aerolineasactivas.size()<<std::endl;
    std::list<Aerolinea*>::iterator iterador = aerolineasactivas.begin();
    while (iterador != aerolineasactivas.end()){
        std::cout<<"Nombre: " <<(*iterador)->getNombre() <<std::endl;
        ++iterador;
    }
    std::cout<<"============================================================================================================" <<std::endl;

    //Busca todos los aeropuertos origen en los que opera Iberia Airlines, con icao IBE
    std::cout<<"============================================================================================================" <<std::endl;
    Aerolinea *ibe = vuelaflight.buscaAerolinea("IBE");
    std::list<Aeropuerto*> ibeAeropuertos = ibe->getAeropuertosOrigin();
    std::cout<<"Cantidad de aeropuetos con origen IBE operados por Iberia Airlines: " <<ibeAeropuertos.size() <<std::endl;
    std::cout<<"============================================================================================================" <<std::endl;

    //Busca todas las rutas operadas por Iberia Arilines con origen en el aeropuerto de Málaga(AGP)
    std::cout<<"============================================================================================================" <<std::endl;
    std::list<Ruta*> ibeRutasAGP = ibe->getRutasAeropuerto("AGP");
    std::cout<<"Cantidad de rutas operadas por Iberia Airlines en el aeropuerto de Málaga: " <<ibeRutasAGP.size() <<std::endl;
    std::cout<<"============================================================================================================" <<std::endl;

    //Ejercicio extra parejas Implementar el método VuelaFlight::getAerolineasPais(String idPais): Aerolinea[] que muestra todas las aerolíneas de un país dado como parámetro (utilizar el recorrido inorden). Para probarlo, muestra por pantalla la información de las aerolíneas que operan en España.
    std::cout<<"============================================================================================================" <<std::endl;
    std::list<Aerolinea*> listAerolineasEspagna = vuelaflight.getAerolineasPais("Spain");
    std::cout<<"Mosrtamos todas las aerolineas que operan en España, que son: "<<listAerolineasEspagna.size() <<std::endl;
    std::list<Aerolinea*>::iterator iteradorEspagna = listAerolineasEspagna.begin();
    while (iteradorEspagna != listAerolineasEspagna.end()){
        std::cout<<"Nombre: " <<(*iteradorEspagna)->getNombre() <<std::endl;
        ++iteradorEspagna;
    }
    std::cout<<"============================================================================================================" <<std::endl;


    // Segunda parte. Para los vuelos con identificador de vuelo AEA5201 y VLG2021, si existen, mostrar:
    //         - (2.1.) Datos de la AEROLINEA que los opera (nombre completo y país al que pertenece) y IATA de los AEROPUERTOS de origen y destino
    //         - (2.2.) Listado con todas las fechas y estado del tiempo en las que se ha efectuado en condiciones de lluvia o chubascos.

    std::cout<<"============================================================================================================" <<std::endl;
    std::cout<<"Segundo apartado"<<std::endl;

    std::cout<<std::endl <<std::endl <<"Datos del vuelo AEA5201" <<std::endl;
    std::list<Vuelo*> listAEA5201 = vuelaflight.buscaVuelos("AEA5201");
    std::list<Vuelo*>::iterator iteratorListAEA5201 = listAEA5201.begin();
    if(listAEA5201.empty()){
        std::cout<<"No se encontraron vuelos con el identificador AEA5201"<<std::endl;
    }else{
        std::cout<<"Datos de la aerolinea" <<std::endl;
        std::cout<<"Nombre: " <<(*iteratorListAEA5201)->getAerolinea()->getNombre() <<std::endl;
        std::cout<<"Pais: " <<(*iteratorListAEA5201)->getAerolinea()->getPais() <<std::endl;
        std::cout << "IATA aeropuerto origen: " << (*iteratorListAEA5201)->getAeropuertoOrigin()->getIata() << std::endl;
        std::cout << "IATA aeropuerto destino: " << (*iteratorListAEA5201)->getAeropuertoDestino()->getIata() << std::endl;
        while (iteratorListAEA5201 != listAEA5201.end()){
            if((*iteratorListAEA5201)->getDatMeteo() == "Lluvia" || (*iteratorListAEA5201)->getDatMeteo() == "Chubascos dispersos"){
                std::cout<<"Fecha del vuelo: " <<(*iteratorListAEA5201)->getFecha()->cadenaDia() <<std::endl;
                std::cout<<"Condiciones metereologicas: " <<(*iteratorListAEA5201)->getDatMeteo() <<std::endl;
            }
            ++iteratorListAEA5201;
        }

    }
    std::cout<<"============================================================================================================" <<std::endl;

    std::cout<<std::endl <<std::endl <<"Datos del vuelo VLG2021" <<std::endl;
    std::list<Vuelo*> listVLG2021 = vuelaflight.buscaVuelos("VLG2021");
    std::list<Vuelo*>::iterator iteratorListVLG2021 = listVLG2021.begin();
    if(listAEA5201.empty()){
        std::cout<<"No se encontraron vuelos con el identificador VLG2021"<<std::endl;
    }else{
        std::cout<<"Datos de la aerolinea" <<std::endl;
        std::cout<<"Nombre: " <<(*iteratorListVLG2021)->getAerolinea()->getNombre() <<std::endl;
        std::cout<<"Pais: " <<(*iteratorListVLG2021)->getAerolinea()->getPais() <<std::endl;
        std::cout << "IATA aeropuerto origen: " << (*iteratorListVLG2021)->getAeropuertoOrigin()->getIata() << std::endl;
        std::cout << "IATA aeropuerto destino: " << (*iteratorListVLG2021)->getAeropuertoDestino()->getIata() << std::endl;
        while (iteratorListVLG2021 != listVLG2021.end()){
            if((*iteratorListVLG2021)->getDatMeteo() == "Lluvia" || (*iteratorListVLG2021)->getDatMeteo() == "Chubascos dispersos"){
                std::cout<<"Fecha del vuelo: " <<(*iteratorListVLG2021)->getFecha()->cadenaDia() <<std::endl;
                std::cout<<"Condiciones metereologicas: " <<(*iteratorListVLG2021)->getDatMeteo() <<std::endl;
            }
            ++iteratorListVLG2021;
        }

    }
    std::cout<<"============================================================================================================" <<std::endl;

    // Tercer apartado. Mostrar todos los modelos de aviones(unicos) utilizados en vuelos operados por Vueling VLG, el 13/04/2018
    std::cout<<"============================================================================================================" <<std::endl;
    std::cout<<"Tercer apartado"<<std::endl;
    std::cout<<"Mostramos los aviones unicos utilizados en los vuelos operados por Vueling, VLG el 13/04/2018" <<std::endl;
    Fecha fecha1(13,4,18);
    std::list<Vuelo*> listVuelosVLGFecha1 = vuelaflight.vuelosOperadosPor("VLG", fecha1);
    std::list<Vuelo*>::iterator iteratorVuelosVLGFecha1 = listVuelosVLGFecha1.begin();
    std::set<std::string> setFlights;
    while (iteratorVuelosVLGFecha1 != listVuelosVLGFecha1.end()){
        setFlights.insert((*iteratorVuelosVLGFecha1)->getPlane());
        ++iteratorVuelosVLGFecha1;
    }
    std::set<std::string>::iterator iteratorSetFlights = setFlights.begin();
    while (iteratorSetFlights != setFlights.end()){
        std::cout<<"Avion: " <<*iteratorSetFlights <<std::endl;
        ++iteratorSetFlights;
    }
    std::cout<<"============================================================================================================" <<std::endl;

    //Cuarto apartado. Mostrar los identificadores de vuelo(unicos) con destino a Londres(LHR, STN, LTN, LGW) desde cualquier aeropuerto español
    std::cout<<"============================================================================================================" <<std::endl;
    std::cout<<"Cuarto apartado"<<std::endl;
    std::cout<<"Mostramos los identificadores de vuelo(unicos) con destino a Londres(LHR, STN, LTN, LGW) desde cualquier aeropuerto español" <<std::endl;
    std::set<std::string> setLHR = vuelaflight.buscaVuelosDestAerop("ES", "LHR");
    std::set<std::string> setSTN = vuelaflight.buscaVuelosDestAerop("ES", "STN");
    std::set<std::string> setLTN = vuelaflight.buscaVuelosDestAerop("ES", "LTN");
    std::set<std::string> setLGW = vuelaflight.buscaVuelosDestAerop("ES", "LGW");

    std::set<std::string>::iterator iteratorSetLHR = setLHR.begin();
    std::set<std::string>::iterator iteratorSetSTN = setSTN.begin();
    std::set<std::string>::iterator iteratorSetLTN = setLTN.begin();
    std::set<std::string>::iterator iteratorSetLGW = setLGW.begin();
    int numIdentFlight = 0;

    while (iteratorSetSTN != setSTN.end()){
        setLHR.insert(*iteratorSetSTN);
        ++iteratorSetSTN;
    }
    while (iteratorSetLTN != setLTN.end()){
        setLHR.insert(*iteratorSetLTN);
        ++iteratorSetLTN;
    }
    while (iteratorSetLGW != setLGW.end()){
        setLHR.insert(*iteratorSetLGW);
        ++iteratorSetLGW;
    }

    while (iteratorSetLHR != setLHR.end()){
        std::cout<<++numIdentFlight<<". Identificador vuelo: " <<*iteratorSetLHR <<std::endl;
        ++iteratorSetLHR;
    }
    std::cout<<"============================================================================================================" <<std::endl;
    //Quinto apartado. Mostrar las ciudades donde se operan vuelos de Iberojet, EVE
    std::cout<<"============================================================================================================" <<std::endl;
    std::cout<<"Quinto apartado"<<std::endl;
    std::cout<<"Mostramos llas ciudades donde se operan vuelos de Iberojet, EVE" <<std::endl;
    std::set<Aeropuerto*> setAirportsEVE = vuelaflight.buscaAeropuertosAerolinea("EVE");

    if (!setAirportsEVE.empty()){
        std::set<Aeropuerto*>::iterator iteratorSetAirportsEVE = setAirportsEVE.begin();
        while (iteratorSetAirportsEVE != setAirportsEVE.end()){
            std::cout<<"Ciudad: " <<(*iteratorSetAirportsEVE)->getNombre() <<std::endl;
            ++iteratorSetAirportsEVE;
        }
    }

*/

}
