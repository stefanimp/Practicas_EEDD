#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "VDinamico.h"
#include "ListaEnlaza.h"
#include "Ruta.h"
#include "VuelaFlight.h"

/**
 * @author  Stefan Giovanni Imperato Lozano sgil0001@red.ujaen.es
 * @author  Carlos Martinez Sanchez cms00065@red.ujaen.es
 * @warning Si al ejecutar el programa aparece un error de compilación, modificar el archivo CMAKE para que la versión sea la siguiente: set(CMAKE_CXX_STANDARD 17)
 * */
int main(int argc, const char * argv[]) {

    //Programa de prueba I: probar la lista enlazada con enteros
    ListaEnlazada<int> listaenteros;
    for (int i = 101; i <= 200; ++i) {
        listaenteros.insertarFinal(i);
    }
    std::cout<<"Insercion de 101 a 200" <<std::endl;

    ListaEnlazada<int>::Iterador iterador = listaenteros.iterador();

    for (int i = 98 ;i >= 1; --i) {
        listaenteros.insertarInicio(i);
    }
    std::cout<<"Insercion de 98 a 1" <<std::endl;

    ListaEnlazada<int>::Iterador iterador2 = listaenteros.iterador();

    int var = 100;

    listaenteros.insertar(iterador2,var);

    std::cout<<"Insercion del 100" <<std::endl;

    var =  99;
    listaenteros.insertar(iterador2,var);
    std::cout<<"Insercion del 99 al principio" <<std::endl;
    iterador = listaenteros.iterador();

    while (!iterador.fin()){
        std::cout<<iterador.dato() <<std::endl;
        iterador.siguiente();
    }
    std::cout<<"Se muestran datos del 99 a" <<std::endl;

    for (int i = 0; i < 10; ++i) {
        listaenteros.borrarIncicio();
        listaenteros.borrarFinal();
    }
    std::cout<<"Borrados los datos" <<std::endl;
    iterador = listaenteros.iterador();


    while (!iterador.fin()){
        if (((iterador.dato())%10) == 0 ){
            ListaEnlazada<int>::Iterador iteradorTemporal(iterador);
            iterador.siguiente();
            listaenteros.borrar(iteradorTemporal);
        }else{
            iterador.siguiente();
        }
    }
    std::cout<<"Borrados los datos multiplos de 10" <<std::endl;

    iterador = listaenteros.iterador();

    while (!iterador.fin()){
        std::cout<<iterador.dato() <<std::endl;
        iterador.siguiente();
    }

    std::cout<< "Fin del programa de prueba 1"<<std::endl;








    //Programa de prueba II: probar la funcionalidad de VuelaFlight

    //Para el fichero "aeropuertos.csv"
    VuelaFlight vuelaFlight;
    Aeropuerto aeropuerto;
    UTM utm;

    std::ifstream is;
    std::string fila;

    unsigned int id=0;
    std::string iata="";
    std::string tipo="";
    std::string nombre="";
    std::string latitud_str="";
    std::string longitud_str="";
    std::string continente="";
    std::string iso_pais="";
    float latitud, longitud;

    is.open("../aeropuertos_v2.csv"); //Archivo del que leeremos los aeropuertos
    if ( is.good() ) {

        clock_t t_ini = clock();
        //Descartamos la primera línea del documento csv, ya que no contiene ningún aeropuerto.
        std::string lineaBasura;
        std::getline(is,fila);

        while ( getline(is, fila ) ) {
            if (fila!="") {
                std::stringstream columnas(fila);

                columnas.str(fila);

                //formato de fila: id;iata;tipo;nombre;latitud;longitud;continente;iso_pais

                columnas>>id;
                columnas.ignore( ); //Hacemos esto para evitar la conversión de "id" a string
                getline(columnas,iata,';'); //Leemos caracteres hasta encontrar y omitir ';'
                getline(columnas,tipo,';');
                getline(columnas,nombre,';');
                columnas>>latitud;
                columnas.ignore( );
                columnas>>longitud;
                columnas.ignore( );
                getline(columnas,continente,';');
                getline(columnas,iso_pais,';');

                aeropuerto.setId(id);
                aeropuerto.setIata(iata);
                aeropuerto.setTipo(tipo);
                aeropuerto.setNombre(nombre);
                utm.setLatitud(latitud);
                utm.setLongitud(longitud);
                aeropuerto.setPosicion(utm);
                aeropuerto.setContinente(continente);
                aeropuerto.setIsoPais(iso_pais);

                // Inserto el aeropuerto en el contenedor
                try {
                    vuelaFlight.addAeropuerto(aeropuerto);
/*                    std::cout << " Aeropuerto: ( ID=" << id
                              << " iata=" << iata << " Tipo=" << tipo << " Nombre=" << nombre
                              << " Posicion=(" << latitud << ", " << longitud << ")"
                              << " Continente=" << continente << " Pais=" << iso_pais
                              << ")" << std::endl;*/
                }catch (std::out_of_range &e){
                    std::cout<<e.what() <<std::endl;
                }catch (std::invalid_argument &e){
                    std::cout<<e.what() <<std::endl;
                }

                fila="";
                columnas.clear();
            }

        }

        is.close();

        std::cout << "Tiempo lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    vuelaFlight.ordenarAirports();


    //Para el fichero "rutas.csv"
    ListaEnlazada<Ruta> routes;
    Ruta ruta;

    std::ifstream is2;
    std::string fila2;

    std::string aerolinea = "";
    std::string idOrigen;
    std::string idDestino;

    is2.open("../rutas_v1.csv"); //carpeta de proyecto
    if ( is2.good() ) {

        clock_t t_ini = clock();
        //Descartamos la primera línea del documento csv, ya que no contiene ningúna ruta.
        std::string lineaBasura;
        std::getline(is2,lineaBasura);

        while ( getline(is2, fila2 ) ) {
            if (fila2!="") {
                std::stringstream columnas2(fila2);

                columnas2.str(fila2);

                //formato de fila2: aerolinea, origin, destination

                getline(columnas2, aerolinea, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas2,idOrigen,';');
                getline(columnas2,idDestino,';');

                // Inserto la ruta en la lista enlazada
                vuelaFlight.addNewRute(idOrigen,idDestino,aerolinea);

                fila2="";
                columnas2.clear();
                /*
                std::cout << " Aerolinea: " << aerolinea
                          << " ID Origen: " <<idOrigen
                          << " Posicion: " <<idDestino
                          << std::endl;
                */
            }

        }

        is2.close();

        std::cout << "Tiempo lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }


    // Buscar si hay rutas entre el aeropuerto de Barcelona(BCN) con Estambul (IST)
    std::string idSt = "IST";
    std::string idBCN = "BCN";

    if(vuelaFlight.buscarRutasOriDes(idSt,idBCN)){
        std::cout<<"Hay ruta entre el aeropuerto de Barcelona (BCN) con el de Estambul (IST)" <<std::endl;
    }

    //Buscar también si hay ruta entre el aeropuerto de Granada-Jaén (GRX) con algún aeropuerto inglés (GB).
    std::string idGR = "GRX";
    std::string isoEng = "GB";

    VDinamico<Aeropuerto*> aeropuertosEng = vuelaFlight.buscarAeropuertoPais(isoEng);

    for (int i = 0; i < aeropuertosEng.tamLogigo(); ++i) {
        if((!vuelaFlight.buscarRutasOriDes(idGR, aeropuertosEng[i]->getIata()))){
            std::cout<<"Hay ruta entre el aeropuerto de Granada-Jaén (GRX) con algún aeropuerto inglés (GB)" <<std::endl;
            break;
        }
        if((!vuelaFlight.buscarRutasOriDes(aeropuertosEng[i]->getIata(), idGR))){
            std::cout<<"Hay ruta entre el aeropuerto de Granada-Jaén (GRX) con algún aeropuerto inglés (GB)" <<std::endl;
            break;
        }
    }



    //Añadir en O(1) una nueva ruta entre el aeropuerto de Granada-Jaén (GRX) con el de París Charles de Gaulle (CDG) de la compañía Iberia (IBE). Las rutas deben ir y volver entre ambos aeropuertos.
    std::string idCD = "CDG";
    std::string aerolinea2 = "IBE";

    vuelaFlight.addNewRute(idGR,idCD,aerolinea2);
    clock_t t_ini1 = clock();

    std::cout << "Tiempo lectura: " << ((clock() - t_ini1) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

    return 0;
}