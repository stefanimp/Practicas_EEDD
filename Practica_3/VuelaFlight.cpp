//
// Created by stefan on 23/10/2023.
//

// IMPORTANTE cuando en la práctica pide que se busque por id se refiere al iata

#include "VuelaFlight.h"
#include <iostream>
#include <fstream>
#include <string>

VuelaFlight::VuelaFlight() {

}

/**
 * @brief   Constructor parametrizado de la clase VuelaFlight
 * @details REcibe como parámetros tres ifstrem que son el contenido de del fichero csv del que queremos leer los datos de vuelaflight. Esta función asigna a todas las rutas su compañia, aeropuerto de origen y destino correspondientes. También asigna a todas las Aerolineas todas las rutas que realizan.
 * @param[in]fichAirports   Contenido del fichero de aeropuertos en formato csv:  id;iata;tipo;nombre;latitud;longitud;continente;iso_pais
 * @param[in]fichAerolines  Contenido del fichero de aerolineas en formato csv:   id,icao, nombre, pais, activo
 * @param[in]fichRoutes     Contenido del fichero de rutas en formato csv:        aerolinea, origin, destination
 * @post    El objeto es creado con todos los datos leídos del fichero correspondiente
 * */
VuelaFlight::VuelaFlight(std::ifstream &fichAirports, std::ifstream &fichAerolines, std::ifstream &fichRoutes) {
    std::string fila;
    if(fichAirports.good()){
        Aeropuerto aeropuerto;
        UTM  utm;

        unsigned int id=0;
        std::string iata="";
        std::string tipo="";
        std::string nombre="";
        std::string continente="";
        std::string iso_pais="";
        float latitud, longitud;

        //Descartamos la primera línea del documento csv, ya que no contiene ningún aeropuerto.
        std::string lineaBasura;
        std::getline(fichAirports,lineaBasura);

        while (std::getline(fichAirports,fila)){
            if(fila != ""){
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
                try {
                    this->addAeropuerto(aeropuerto);
                }catch (std::out_of_range &e){
                    std::cout<<e.what() <<std::endl;
                }catch (std::invalid_argument &e){
                    std::cout<<e.what() <<std::endl;
                }
                fila = "";
                columnas.clear();
            }
        }
        this->ordenarAirports();
        fichAirports.close();
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    if(fichAerolines.good()){
        Aerolinea aerolinea;
        unsigned int id = 0;
        std::string icao = "";
        std::string nombre = "";
        std::string pais = "";
        std::string activo = "";
        //Descartamos la primera línea del documento csv, ya que no contiene ninguna aerolinea
        std::string lineaBasura;
        std::getline(fichAerolines,lineaBasura);

        while(std::getline(fichAerolines,fila)){
            if(fila != ""){
                std::stringstream columnas(fila);
                columnas.str(fila);
                //formato de aerolineas: id,icao, nombre, pais, activo
                columnas>>id;
                columnas.ignore( );
                std::getline(columnas,icao,';');
                std::getline(columnas,nombre,';');
                std::getline(columnas,pais,';');
                std::getline(columnas,activo,';');

                aerolinea.setId(id);
                aerolinea.setIcao(icao);
                aerolinea.setNombre(nombre);
                aerolinea.setPais(pais);
                if(activo == "Y"){
                    aerolinea.setActivo(true);
                }else{
                    aerolinea.setActivo(false);
                }
                aerolines.inserta(aerolinea);

                fila = "";
                columnas.clear();
            }
        }
        fichAerolines.close();
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    if(fichRoutes.good()){
        Ruta ruta;
        std::string aerolinea = "";
        std::string idOrigen;
        std::string idDestino;
        //Descartamos la primera línea del documento csv, ya que no contiene ningúna ruta.
        std::string lineaBasura;
        std::getline(fichRoutes,lineaBasura);

        while (std::getline(fichRoutes,fila)){
            if(fila != ""){
                std::stringstream columnas(fila);
                columnas.str(fila);
                //formato de fila2: aerolinea, origin, destination
                getline(columnas, aerolinea, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas,idOrigen,';');
                getline(columnas,idDestino,';');
                // Se inserta la ruta en la lista enlazada
                Ruta *rutaAgnadida = this->addNewRute(idOrigen,idDestino,aerolinea);
                if (rutaAgnadida){
                    Aerolinea *aerolineaRuta = &rutaAgnadida->getCompany();
                    aerolineaRuta->linkAerolRuta(rutaAgnadida);
                }
                fila = "";
                columnas.clear();
            }
        }
        fichRoutes.close();
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }
}


void VuelaFlight::ordenarAirports() {
    airports.ordenar();
}

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
/**
 * @brief   Devuelve una lista enlaza de punteros a las rutas que tengan el aeropuerto origen pasado como parámetro
 * @param[in]idAerOrig  id(iata) del aeropuerto origen que se quiere busca de entre todas las rutas
 * @post    Un lista enlazada de punteros a rutas con todas las rutas qu tengan como aeropuerto de origen el pasado como parámetro es devuelta
 * */
ListaEnlazada<Ruta*> VuelaFlight::buscarRutasOrigen(const std::string &idAerOrig) {
    ListaEnlazada<Ruta*> listaNueva;
    ListaEnlazada<Ruta>::Iterador iterador = routes.iterador();

    while (!iterador.fin()){
        if(iterador.dato().getOrigin().getIata() == idAerOrig){
            listaNueva.insertarFinal(&(iterador.dato()));
        }
        iterador.siguiente();
    }
    return listaNueva;
}

/**
 * @brief   Busca todos los aeropuertos de l pais indicado.
 * @details Se utiliza una lista enlaza ya que tiene una inserción poco costosa.
 * @param[in]pais   Pais del que se quieren buscar los aeropuertos.
 * @post    Devuelve una lista enlazada con todos los aeropuertos del pais pasado como parámetro.
 * */
ListaEnlazada<Aeropuerto*> VuelaFlight::buscarAeropuertoPais(const std::string &pais) {
    ListaEnlazada<Aeropuerto*> nuevoVDim;

    for (int i = 0; i < airports.tamLogigo(); ++i) {
        if (airports[i].getIsoPais() == pais){
            nuevoVDim.insertarFinal(&airports[i]);
        }
    }
    return nuevoVDim;
}


/**
 * @brief   Añade una nueva ruta a la lista enlazada de rutas
 * @details Añade la nueva ruta a la lista enlazada. Busca entre el AVL de aerolineas para enlazar la correspondiente y en el vector dinamico de aeropuertos para enlazar el aeropuerto de origen y de destino.
 * @param[in]idAerOrig  Iata del aeropuerto origen de la ruta. Nos servir'a para buscarlo entre el vector din'amico con una busqueda binaria.
 * @param[in]idAerDest  Iata del aeropuerto destino de la ruta. Nos serria para buscarlo entre el vector dinamico con una busqueda binaria.
 * @param[in]aerolin    Id de la aerolinea. Nos servira para buscar la aerolinea en el AVL y asignarla a la ruta.
 * @post    Si todos los campos han sido encontrados se añade la nueva ruta.
 * @return  De vuelve la direccion de memoria de la ruta añadida
 * */
Ruta* VuelaFlight::addNewRute(const std::string &idAerOrig, const std::string &idAerDest, const std::string &aerolin) {
    Ruta rutanueva;
    Aerolinea aeroComprobacion;
    Aeropuerto aeropComprobacion;
    aeroComprobacion.setIcao(aerolin);

    rutanueva.setCompany(*(aerolines.buscaRec(aeroComprobacion)));

    aeropComprobacion.setIata(idAerOrig);
    int resultado = airports.busquedaBin(aeropComprobacion);
    if(resultado != -1){
        rutanueva.setOrigin(airports[resultado]);
    }

    aeropComprobacion.setIata(idAerDest);
    resultado = airports.busquedaBin(aeropComprobacion);
    if(resultado != -1){
        rutanueva.setDestination(airports[resultado]);
    }

    if (&rutanueva.getOrigin() && &rutanueva.getDestination() && &rutanueva.getCompany()){
        routes.insertarFinal(rutanueva);
        return &routes.fin();
    }

    return nullptr;

}

Aerolinea &VuelaFlight::buscaAerolinea(const std::string &icaoAerolinea) {
    Aerolinea aerolineaAux;
    aerolineaAux.setIcao(icaoAerolinea);
    return *aerolines.buscaRec(aerolineaAux);
}

ListaEnlazada<Aerolinea *> VuelaFlight::buscarAerolineasActivas() {
    VDinamico<Aerolinea*> vecAerolines = aerolines.recorreInOrden();
    ListaEnlazada<Aerolinea*> listAerolines;
    for (int i = 0; i < vecAerolines.tamLogigo(); ++i) {
        if (vecAerolines[i]->isAvtivo()){
            listAerolines.insertarFinal(vecAerolines[i]);
        }
    }
    return listAerolines;
}

ListaEnlazada<Aerolinea *> VuelaFlight::getAerolineasPais(const std::string &idPais) {
    VDinamico<Aerolinea*> vecAerolines = aerolines.recorreInOrden();
    ListaEnlazada<Aerolinea*> listAerolines;
    for (int i = 0; i < vecAerolines.tamLogigo(); ++i) {
        if (vecAerolines[i]->getPais() == idPais){
            listAerolines.insertarFinal(vecAerolines[i]);
        }
    }
    return listAerolines;
}
