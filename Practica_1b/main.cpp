#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "VDinamico.h"
#include "Aeropuerto.h"

/**
 * @author  Stefan Giovanni Imperato Lozano sgil0001@red.ujaen.es
 * @author  Carlos Martinez Sanchez cms00065@red.ujaen.es
 * @warning Si al ejecutar el programa aparece un error de compilación, modificar el archivo CMAKE para que la versión sea la siguiente: set(CMAKE_CXX_STANDARD 17)
 * */
int main(int argc, const char * argv[]) {

    VDinamico<Aeropuerto> vec;
    Aeropuerto aeropuerto;
    UTM utm;

    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;
    int contador=0;

    std::string id = "";
    std::string ident="";
    std::string tipo="";
    std::string nombre="";
    std::string latitud_str="";
    std::string longitud_str="";
    std::string continente="";
    std::string iso_pais="";

    float latitud, longitud;

    is.open("../aeropuertos.csv"); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id;ident;tipo;nombre;latitud;longitud;continente;iso_pais

                getline(columnas, id, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas,ident,';');
                getline(columnas,tipo,';');
                getline(columnas,nombre,';');
                getline(columnas,latitud_str,';');
                getline(columnas,longitud_str,';');
                getline(columnas,continente,';');
                getline(columnas,iso_pais,';');

                //  Transformamos la latitud y longitud a float
                latitud=std::stof(latitud_str);
                longitud=std::stof(longitud_str);

                utm.setLatitud(latitud);
                utm.setLongitud(longitud);

                aeropuerto.setId(id);
                aeropuerto.setIdent(ident);
                aeropuerto.setTipo(tipo);
                aeropuerto.setNombre(nombre);
                aeropuerto.setPosicion(utm);
                aeropuerto.setContinente(continente);
                aeropuerto.setIsoPais(iso_pais);

                // Inserto el aeropuerto en el contenedor
                vec.insertar(aeropuerto);

                fila="";
                columnas.clear();
                ++contador;

                /*
                std::cout << ++contador
                          << " Aeropuerto: ( ID=" << id
                          << " ident=" << ident << " Tipo=" << tipo << " Nombre=" << nombre
                          << " Posicion=(" << latitud << ", " << longitud << ")"
                          << " Continente=" << continente << " Pais=" << iso_pais
                          << ")" << std::endl;

                */
            }

        }

        is.close();

        std::cout << "Tiempo lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }



    // Ordenación del vector de mayor a menor
    clock_t t_ini1 = clock();
    vec.ordenarRev();

    // Muestro el id de los primeros 30 aeropuertos ordenados de mayor a menor
    std::cout<<std::endl<<"ID de aeropuertos ordenado de MAYOR A MENOR: "<<std::endl;
    for(int i=0; i<30; i++){
        std::cout<<"Id del "<<i+1<<" aeropuerto: "<<vec[i].getId()<<std::endl;
    }
    std::cout << "Tiempo lectura: " << ((clock() - t_ini1) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

    // Ordenación del vector de menor a mayor
    clock_t t_ini2 = clock();
    vec.ordenar();

    //Muestro el id de los primeros 30 aeropuertos ordenados de menor a mayor
    std::cout<<std::endl<<"ID de aeropuertos ordenado de MENOR A MAYOR: "<<std::endl;
    for(int i=0; i<30; i++){
        std::cout<<"Id del "<<i+1<<" aeropuerto: "<<vec[i].getId()<<std::endl;
    }
    std::cout << "Tiempo lectura: " << ((clock() - t_ini2) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

    //Muestro la posicion de los aeropuertos con distintas id en el contenedor
    std::cout<<std::endl;
    clock_t t_ini3 = clock();
    for(int i=0; i<vec.tamLogigo(); i++){
        if(vec[i].getId()=="345166"){
            std::cout<<"El aeropuerto con id "<<vec[i].getId()<<" se encuentra en la posicion "<<i<<" del contenedor"<<std::endl;
        }

        if(vec[i].getId()=="6640"){
            std::cout<<"El aeropuerto con id "<<vec[i].getId()<<" se encuentra en la posicion "<<i<<" del contenedor"<<std::endl;
        }

        if(vec[i].getId()=="6676"){
            std::cout<<"El aeropuerto con id "<<vec[i].getId()<<" se encuentra en la posicion "<<i<<" del contenedor"<<std::endl;
        }

        if(vec[i].getId()=="345364"){
            std::cout<<"El aeropuerto con id "<<vec[i].getId()<<" se encuentra en la posicion "<<i<<" del contenedor"<<std::endl;
        }

        if(vec[i].getId()=="6778"){
            std::cout<<"El aeropuerto con id "<<vec[i].getId()<<" se encuentra en la posicion "<<i<<" del contenedor"<<std::endl;
        }
    }
    std::cout << "Tiempo lectura: " << ((clock() - t_ini3) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

    clock_t t_ini4 = clock();


    VDinamico<Aeropuerto> vAux;

    for (int i = 0; i < vec.tamLogigo(); ++i) {
        if(vec.getMem()[i].getContinente() == "NA"){
            vAux.insertar(vec[i], UINT_MAX);
            vec.borrar(i);
        }
    }
    std::cout << "Tiempo lectura: " << ((clock() - t_ini4) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;



    std::cout<<std::endl<<"Tamanio logico del vector auxiliar con todos los aeropuertos sin el continente NA: "<<vAux.tamLogigo()<<std::endl;
    std::cout<<"Tamanio logico del vector dinamico original con los aeropuertos eliminados: "<<vec.tamLogigo()<<std::endl;

    //Muestro la información de los primeros 20 aeropuertos del nuevo vector auxiliar, primero, los ordeno de menor a mayor
    vAux.ordenar();


    for(int i=0; i<20; i++){
        std::cout<<"Aeropuerto "<<i+1<<": "<<std::endl;
        std::cout<<"Id: "<<vAux.getMem()[i].getId()<<std::endl;
        std::cout<<"Identificador: "<<vAux.getMem()[i].getIdent()<<std::endl;
        std::cout<<"Tipo: "<<vAux.getMem()[i].getTipo()<<std::endl;
        std::cout<<"Nombre: "<<vAux.getMem()[i].getNombre()<<std::endl;
        std::cout<<"Latitud: "<<vAux.getMem()[i].getPosicion().getLatitud()<<std::endl;
        std::cout<<"Longitud: "<<vAux.getMem()[i].getPosicion().getLongitud()<<std::endl;
        std::cout<<"Continente: "<<vAux.getMem()[i].getContinente()<<std::endl;
        std::cout<<"Iso Pais: "<<vAux.getMem()[i].getIsoPais()<<std::endl;
        std::cout<<std::endl;
    }
    std::cout << "Tiempo lectura: " << ((clock() - t_ini4) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;





    return 0;
}

