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
VuelaFlight::VuelaFlight(std::ifstream &fichAirports, std::ifstream &fichAerolines, std::ifstream &fichRoutes, std::ifstream &fichFlights) {
    std::string fila;
    if(fichAirports.good()){
        Aeropuerto aeropuerto;
        UTM  utm;

        unsigned int id;
        std::string iata;
        std::string tipo;
        std::string nombre;
        std::string continente;
        std::string iso_pais;
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
                this->addAeropuerto(aeropuerto);

                fila = "";
                columnas.clear();
            }
        }
        fichAirports.close();
        // Ordenamos el vector para facilitar y asegurar las búsquedas dentro de este en O(logn)
        this->ordenarAirports();

    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    int numAirpots = airports.size();

    if(fichAerolines.good()){
        Aerolinea aerolinea;
        unsigned int id;
        std::string icao;
        std::string nombre;
        std::string pais;
        std::string activo;
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
                aerolines.insert(std::pair<std::string, Aerolinea>(aerolinea.getIcao(), aerolinea));

                fila = "";
                columnas.clear();
            }
        }
        fichAerolines.close();
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    int numAerolines = aerolines.size();

    if(fichRoutes.good()){
        Ruta ruta;
        std::string aerolinea;
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


    if(fichFlights.good()){

        Vuelo flight;
        std::string flightnum;
        std::string iataDep;
        std::string iataArr;
        std::string plane;
        std::string datmeteo;
        std::string datDate;
        int dia;
        int mes;
        int agno;
        //Descartamos la primera línea del documento csv, ya que no contiene ningún vuelo.
        std::string lineaBasura;
        std::getline(fichFlights, lineaBasura);

        while (std::getline(fichFlights, fila)){
            if(fila != ""){
                std::stringstream columnas(fila);
                columnas.str(fila);
                //formato de infovuelos_v11.csv: flightNumber;dep_airport_code;arr_airport_code;plane;dep_weather_desc;dep_date
                std::getline(columnas,flightnum,';');
                std::getline(columnas,iataDep,';');
                std::getline(columnas,iataArr,';');
                std::getline(columnas,plane,';');
                std::getline(columnas,datmeteo,';');
                std::getline(columnas,datDate,';');
                std::istringstream date(datDate);
                char delimiter;
                date >>dia >>delimiter >>mes >>delimiter >>agno;
                Fecha fecha(dia, mes, agno);
                registrarVuelo(flightnum, iataDep, iataArr, plane, datmeteo, fecha);
            }
        }
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    std::cout<<"Cantidad de aeropuertos cargados: " <<airports.size() <<std::endl;
    std::cout<<"Cantidad de aerolineas cargadas: " <<aerolines.size() <<std::endl;
    std::cout<<"Cantidad de rutas cargadas: " <<routes.size() <<std::endl;
}


/**
 * @brief   Ordena de menor a mayor el vector dinámico de aeropuertos
 * @details Ordena de menor a mayor el vector usando la función sort de la biblioteca algorithm
 * @post    El vector queda ordenado de menor a mayor
 * */
void VuelaFlight::ordenarAirports() {
    std::sort(airports.begin(), airports.end());
}

/**
 * @brief   Inserta un auropuerto nuevo en el vector dinámico de aeropuertos
 * @param[in]aeropuerto objeto aeropuerto que se quiere insertar
 * @post    Un nuevo aeropuerto es añadido
 * */
void VuelaFlight::addAeropuerto(const Aeropuerto &aeropuerto) {
    this->airports.push_back(aeropuerto);
}


/**
 * @brief   Busca una ruta que coincida con el id del aeropuerto de origen y de destino
 * @param[in]idAerOrig  iata de l aeropuerto de origen
 * @param[in]idAerDest  iata del aeropuerto de destino
 * @return  Devuelve, si se ha encontrado, la ruta con las características exigidas
 * @return  Devuelve, si no se ha encontrado la ruta especificada, un puetero a nulo
 * */
Ruta* VuelaFlight::buscarRutasOriDes(const std::string &idAerOrig, const std::string &idAerDest) {
    std::list<Ruta>::iterator iteratorRute = routes.begin();

    while (iteratorRute != routes.end()){
        if (iteratorRute->getOrigin().getIata() == idAerOrig && iteratorRute->getDestination().getIata() == idAerDest){
            return &(*iteratorRute);
        }
        ++iteratorRute;
    }

    return nullptr;
}


/**
 * @brief   Devuelve una std::list de punteros a las rutas que tengan el aeropuerto origen pasado como parámetro
 * @param[in]idAerOrig  id(iata) del aeropuerto origen que se quiere busca de entre todas las rutas
 * @post    Una std::list de punteros a rutas con todas las rutas que tengan como aeropuerto de origen el pasado como parámetro es devuelta
 * */
std::list<Ruta*> VuelaFlight::buscarRutasOrigen(const std::string &idAerOrig) {
    std::list<Ruta*> listaNueva;
    std::list<Ruta>::iterator iteratorRute = routes.begin();

    while (iteratorRute != routes.end()){
        if(iteratorRute->getOrigin().getIata() == idAerOrig){
            listaNueva.push_back(&(*iteratorRute));
        }
        ++iteratorRute;
    }
    return listaNueva;
}

/**
 * @brief   Busca todos los aeropuertos del pais indicado.
 * @details Se utiliza una lista enlazada de std::list ya que tiene una inserción poco costosa.
 * @param[in]pais   Pais del que se quieren buscar los aeropuertos.
 * @post    Devuelve una lista enlazada con todos los aeropuertos del pais pasado como parámetro.
 * */
std::list<Aeropuerto*> VuelaFlight::buscarAeropuertoPais(const std::string &pais) {
    std::list<Aeropuerto*> listaNueva;

    for (int i = 0; i < airports.size(); ++i) {
        if (airports[i].getIsoPais() == pais){
            listaNueva.push_back(&airports[i]);
        }
    }
    return listaNueva;
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
    // Creo la ruta que será añadida
    Ruta rutanueva;
    // Creo los objetos necesarios para realizar las comparaciones
    Aeropuerto aeropComprobacion;

    //Recordamos que en los maps se busca por el first
    //TODO cmproabr que funciona pasando el srting y si no un aeropuerto con ese string
    //TODO hay hay un iterator
    std::map<std::string, Aerolinea>::iterator iterator = aerolines.find(aerolin);
    if (iterator != aerolines.end()){ //Comprobamos que se ha encontrado el elemento. .end() devuelve la siguiente posicion al ultimo elemento almacenado en map(aerlines)
        rutanueva.setCompany((iterator)->second);
    }

    aeropComprobacion.setIata(idAerOrig);
    //TODO hay hay un iterator
    std::vector<Aeropuerto>::iterator iteratorAerop = std::lower_bound(airports.begin(), airports.end(), aeropComprobacion);
    if(iteratorAerop != airports.end()){
        //TODO comprobar que se inserta correctamente el aeropuerto y no un objeto copia
        rutanueva.setOrigin(*iteratorAerop);
    }

    aeropComprobacion.setIata(idAerDest);
    iteratorAerop = std::lower_bound(airports.begin(), airports.end(), aeropComprobacion);
    if(iteratorAerop != airports.end()){
        //TODO comprobar que se inserta correctamente el aeropuerto y no un objeto copia
        rutanueva.setDestination(*iteratorAerop);
    }

    if (&rutanueva.getOrigin() && &rutanueva.getDestination() && &rutanueva.getCompany()){
        routes.push_back(rutanueva);
        return &(routes.back());
    }

    return nullptr;
}

//TODO comprobar que este método funciona y revisar pregunta a balsas.
Aerolinea *VuelaFlight::buscaAerolinea(const std::string &icaoAerolinea) {
    Aerolinea *aerolinea;
    std::map<std::string, Aerolinea>::iterator iteratorAerolines = aerolines.find(icaoAerolinea);
    if(iteratorAerolines != aerolines.end()){
        aerolinea = &iteratorAerolines->second;
        return aerolinea;
    }
    return nullptr;
}

std::list<Aerolinea *> VuelaFlight::buscarAerolineasActivas() {
    std::list<Aerolinea*> listAerolines;
    for (std::map<std::string, Aerolinea>::iterator iteradorAerlines = aerolines.begin(); iteradorAerlines != aerolines.end() ; ++iteradorAerlines) {
        if(iteradorAerlines->second.getActivo()){
            listAerolines.push_back(&(iteradorAerlines->second));
        }
    }
    return listAerolines;
}

std::list<Aerolinea *> VuelaFlight::getAerolineasPais(const std::string &idPais) {
    std::list<Aerolinea*> listAerolines;
    for (std::map<std::string, Aerolinea>::iterator iteradorAerlines = aerolines.begin(); iteradorAerlines != aerolines.end() ; ++iteradorAerlines) {
        if(iteradorAerlines->second.getPais() == idPais){
            listAerolines.push_back(&(iteradorAerlines->second));
        }
    }
    return listAerolines;
}

bool VuelaFlight::registrarVuelo(const std::string flightNum, const std::string iataAeroOrig, const std::string iataAeroDest,
                            const std::string plane, const std::string datosMeteo, const Fecha &fecha) {
    // Primero comprobamos que existe la Aerolinea que queremos enlazar
    std::multimap<std::string , Aerolinea>::iterator iteratorAerolines = aerolines.find(flightNum.substr(0,3));
    if(iteratorAerolines == aerolines.end()){
        return false;
    }

    // Comprobamos que existen los aeropuertos que queremos enlazar
    Aeropuerto aeroComprobacion;
    aeroComprobacion.setIata(iataAeroOrig);
    std::vector<Aeropuerto>::iterator iteratorAriports1 = std::lower_bound(airports.begin(), airports.end(),aeroComprobacion);
    if (iteratorAriports1 == airports.end()){
        return false;
    }
    aeroComprobacion.setIata(iataAeroDest);
    std::vector<Aeropuerto>::iterator iteratorAirports2 = std::lower_bound(airports.begin(), airports.end(),aeroComprobacion);
    if(iteratorAirports2 == airports.end()){
        return false;
    }

    //Creamos el vuelo y cargamos todos los datos
    Vuelo newFlight;
    newFlight.setAerolinea(iteratorAerolines->second);
    newFlight.setAirportOrig(*iteratorAriports1);
    newFlight.setAirportDest(*iteratorAirports2);
    newFlight.setFlightNumb(flightNum);
    newFlight.setPlane(plane);
    newFlight.setFecha(fecha);
    newFlight.setDatMeteo(datosMeteo);

    //TODO comprobar si este paso es necesario o no. Lo que hace es buscar de entre las rutas si existe un ruta que coincida con el vuelo a insertar, si no existe, se crea. Tener en cuando que definir este método o no supone un cambio en el programa, en concreto en el apartado 4(que yo haya notado)
/*    std::list<Ruta*> listRoutes = (iteratorAerolines->second.getRutasAeropuerto(newFlight.getAeropuertoOrigin()->getIata()));
    std::list<Ruta*>::iterator iteratorListRoutes = listRoutes.begin();
    bool encontrado = false;
    while (iteratorListRoutes != listRoutes.end() && !encontrado){
        if((*iteratorListRoutes)->getOrigin() == *newFlight.getAeropuertoOrigin() && (*iteratorListRoutes)->getDestination() == *newFlight.getAeropuertoDestino()){
            encontrado = true;
        }
        ++iteratorListRoutes;
    }
    if(!encontrado){
        Ruta ruta = Ruta(*newFlight.getAerolinea(), *newFlight.getAeropuertoOrigin(), *newFlight.getAeropuertoDestino());
        routes.push_back(ruta);
        //Pasamos el routes.back y no el vuelo porque vuelo solo existe mientras exista esta función, aerolinea almacena un deque de punteros a rutas, es decir que apuntaría nulo si le pasamos newFlight
        iteratorAerolines->second.linkAerolRuta(&routes.back());
    }*/

    iteratorAerolines->second.addVuelo(newFlight);
    return true;
}

std::list<Vuelo *> VuelaFlight::buscaVuelos(const std::string &fNumber) {
    std::map<std::string , Aerolinea>::iterator iteratorAeroline = aerolines.find(fNumber.substr(0,3));
    std::list<Vuelo*> listFlights;
    if(iteratorAeroline != aerolines.end()){
        listFlights = iteratorAeroline->second.getVuelos(fNumber);
    }
    return listFlights;
}

std::list<Vuelo*> VuelaFlight::vuelosOperadosPor(const std::string &icaoAerolinea, const Fecha &fecha) {
    Aerolinea *aeroline = buscaAerolinea(icaoAerolinea);
    if (aeroline){
        return aeroline->getVuelos(fecha,fecha);
    }
    std::list<Vuelo*> listFlights;
    return listFlights;
}

std::set<std::string> VuelaFlight::buscaVuelosDestAerop(const std::string &paisOrig, const std::string &iataAeropDest) {
    std::set<std::string> setFlightDestFromCountry;
    std::list<Ruta>::iterator iteratorRoutes = routes.begin();

    while (iteratorRoutes != routes.end()){
        if(iteratorRoutes->getDestination().getIata() == iataAeropDest && iteratorRoutes->getOrigin().getIsoPais() == paisOrig){
            std::list<Vuelo*> listVuelos =iteratorRoutes->getFlights();
            std::list<Vuelo*>::iterator iteratorFlights = listVuelos.begin();
            while (iteratorFlights != listVuelos.end()){
                setFlightDestFromCountry.insert((*iteratorFlights)->getFlightNumb());
                ++iteratorFlights;
            }
        }
        ++iteratorRoutes;
    }

    return setFlightDestFromCountry;
}

std::set<Aeropuerto *> VuelaFlight::buscaAeropuertosAerolinea(const std::string &icaoAerolinea) {
    Aerolinea *aerolinea;
    std::set<Aeropuerto*> setAeropuertos;
    std::map<std::string, Aerolinea>::iterator iteratorAerolines = aerolines.find(icaoAerolinea);
    if(iteratorAerolines != aerolines.end()){
        aerolinea = &iteratorAerolines->second;
        std::multimap<std::string, Vuelo> multMapFlights = aerolinea->getVuelos();
        std::multimap<std::string, Vuelo>::iterator iteratorMultMpFlights = multMapFlights.begin();
        while (iteratorMultMpFlights != multMapFlights.end()){
            setAeropuertos.insert(iteratorMultMpFlights->second.getAeropuertoOrigin());
            setAeropuertos.insert(iteratorMultMpFlights->second.getAeropuertoDestino());
            ++iteratorMultMpFlights;
        }

    }
    return setAeropuertos;
}
