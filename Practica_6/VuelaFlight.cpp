//
// Created by stefan on 23/10/2023.
//

// IMPORTANTE cuando en la práctica pide que se busque por id se refiere al iata

#include "VuelaFlight.h"
#include <iostream>
#include <fstream>
#include <string>


/**
 * @brief   Constructor parametrizado de la clase VuelaFlight
 * @details REcibe como parámetros tres ifstrem que son el contenido de del fichero csv del que queremos leer los datos de vuelaflight. Esta función asigna a todas las rutas su compañia, aeropuerto de origen y destino correspondientes. También asigna a todas las Aerolineas todas las rutas que realizan.
 * @param[in]fichAirports   Contenido del fichero de aeropuertos en formato csv:  id;iata;tipo;nombre;latitud;longitud;continente;iso_pais
 * @param[in]fichAerolines  Contenido del fichero de aerolineas en formato csv:   id,icao, nombre, pais, activo
 * @param[in]fichRoutes     Contenido del fichero de rutas en formato csv:        aerolinea, origin, destination
 * @param[in]fichFlights    Contenido del fichero de vuelos en formato csv:       flightNumber;dep_airport_code;arr_airport_code;plane;dep_weather_desc;dep_date
 * @post    El objeto es creado con todos los datos leídos del fichero correspondiente
 * */
VuelaFlight::VuelaFlight(std::ifstream &fichAirports, std::ifstream &fichAerolines, std::ifstream &fichRoutes, std::ifstream &fichFlights) {
    std::string fila;
    float xMin;
    float xMax;
    float yMin;
    float yMax;
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
        int num = 0;
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
                if(num == 0){
                    xMin = aeropuerto.getX();
                    xMax = aeropuerto.getX();
                    yMin = aeropuerto.getY();
                    yMax = aeropuerto.getY();
                    ++num;
                }
                this->addAeropuerto(aeropuerto);
                if (aeropuerto.getX() < xMin){
                    xMin = aeropuerto.getX();
                }else if(aeropuerto.getX() > xMax){
                    xMax = aeropuerto.getX();
                }
                if(aeropuerto.getY() < yMin){
                    yMin = aeropuerto.getY();
                }else if(aeropuerto.getY() > yMax){
                    yMax = aeropuerto.getY();
                }

                fila = "";
                columnas.clear();
            }
        }
        fichAirports.close();

    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

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
    rellenaMalla(xMin, xMax, yMin, yMax);

    std::cout<<"Cantidad de aeropuertos cargados: " <<airports.size() <<std::endl;
    std::cout<<"Cantidad de aerolineas cargadas: " <<aerolines.size() <<std::endl;
    std::cout<<"Cantidad de rutas cargadas: " <<routesOrigin.size() <<std::endl;
}

/**
 * @brief   Función de hashing utilizada para crear las claves de búsqueda de la tablas hash(unordered_map) a través del IATA del aeropuerto
 * @details Utiliza la función hash de la biblioteca std para generar las claves
 * @return  Devuelve la clave que es de tipo unsigned long
 * */
unsigned long VuelaFlight::funcionHash(const std::string &iata) {
    std::hash<std::string> hasher;
    size_t hasSize_T = hasher(iata);
    unsigned long claveDef = static_cast<unsigned long>(hasSize_T);
    return claveDef;
}


/**
 * @brief   Inserta un auropuerto nuevo en el unordered_map
 * @param[in]aeropuerto objeto aeropuerto que se quiere insertar
 * @post    Un nuevo aeropuerto es añadido
 * */
void VuelaFlight::addAeropuerto(const Aeropuerto &aeropuerto) {
     airports.insert(std::make_pair(aeropuerto.getIata(),aeropuerto));
}


/**
 * @brief   Busca una ruta que coincida con el id del aeropuerto de origen y de destino
 * @param[in]idAerOrig  iata de l aeropuerto de origen
 * @param[in]idAerDest  iata del aeropuerto de destino
 * @return  Devuelve, si se ha encontrado, la ruta con las características exigidas
 * @return  Devuelve, si no se ha encontrado la ruta especificada, un puetero a nulo
 * */
Ruta* VuelaFlight::buscarRutasOriDes(const std::string &idAerOrig, const std::string &idAerDest) {
    std::multimap<std::string, Ruta>::iterator iteratorRuteOrig = routesOrigin.find(idAerOrig);
    std::multimap<std::string, Ruta*>::iterator iteratorRuteDest = routesDest.find(idAerDest);
    if (&iteratorRuteOrig->second == iteratorRuteDest->second){
        return iteratorRuteDest->second;
    }

    return nullptr;
}


/**
 * @brief   Devuelve una std::list de punteros a las rutas que tengan el aeropuerto origen pasado como parámetro
 * @param[in]idAerOrig  id(iata) del aeropuerto origen que se quiere busca de entre todas las rutas
 * @post    Una std::list de punteros a rutas con todas las rutas que tengan como aeropuerto de origen el pasado como parámetro es devuelta
 * @return  Una std::list de punteros a rutas con todas las rutas que tengan como aeropuerto de origen
 * */
std::list<Ruta*> VuelaFlight::buscarRutasOrigen(const std::string &idAerOrig) {
    std::list<Ruta*> listaNueva;
    std::multimap<std::string, Ruta>::iterator iteratorRoutesOrig = routesOrigin.find(idAerOrig);

    if(iteratorRoutesOrig != routesOrigin.end()){
        while (iteratorRoutesOrig->first == idAerOrig){
            listaNueva.push_back(&iteratorRoutesOrig->second);
            ++iteratorRoutesOrig;
        }
    }
    return listaNueva;
}

/**
 * @brief   Busca todos los aeropuertos del pais indicado.
 * @details Se utiliza una lista enlazada de std::list ya que tiene una inserción poco costosa.
 * @param[in]pais   Pais del que se quieren buscar los aeropuertos.
 * @post    Devuelve una lista enlazada con todos los aeropuertos del pais pasado como parámetro.
 * @return  Una lista enlazada con todos los aeropuertos del pais pasado como parámetro.
 * */
std::list<Aeropuerto*> VuelaFlight::buscarAeropuertoPais(const std::string &pais) {
    std::list<Aeropuerto*> listaNueva;

    for (std::unordered_map<std::string, Aeropuerto>::iterator iteratorAirports = airports.begin(); iteratorAirports != airports.end(); ++iteratorAirports) {
        if(iteratorAirports->second.getIsoPais() == pais){
            listaNueva.push_back(&iteratorAirports->second);
        }
    }
    return listaNueva;
}


/**
 * @brief   Añade una nueva ruta a ambos multimaps de rutas
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

    //Recordamos que en los maps se busca por el first
    std::map<std::string, Aerolinea>::iterator iterator = aerolines.find(aerolin);
    if (iterator == aerolines.end()){ //Comprobamos que se ha encontrado el elemento. .end() devuelve la siguiente posicion al ultimo elemento almacenado en map(aerlines)
        return nullptr;
    }
    rutanueva.setCompany((iterator)->second);

    // Buscamos el aeropuerto origen
    std::unordered_map<std::string, Aeropuerto>::iterator iteratorAirportOrig = airports.find(idAerOrig);
    if(iteratorAirportOrig == airports.end()){
        return nullptr;
    }
    rutanueva.setOrigin(iteratorAirportOrig->second);

    // Buscamos el aeropuerto destino
    std::unordered_map<std::string, Aeropuerto>::iterator iteratorAirportDest = airports.find(idAerDest);
    if(iteratorAirportDest == airports.end()){
        return nullptr;
    }

    std::multimap<std::string, Ruta*>::iterator iteratorRoutesDest = routesDest.begin();
    Ruta *rutaP = iteratorRoutesDest->second;
    rutanueva.setDestination(iteratorAirportDest->second);

    std::multimap<std::string, Ruta>::iterator iteratorRoutesOrigin = routesOrigin.insert(std::pair<std::string, Ruta>(rutanueva.getOrigin()->getIata(),rutanueva));
    routesDest.insert(std::pair<std::string, Ruta*>(iteratorRoutesOrigin->first,&(iteratorRoutesOrigin->second)));
    return &iteratorRoutesOrigin->second;
}


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
    std::unordered_map<std::string, Aeropuerto>::iterator iteradorAirportOrig = airports.find(iataAeroOrig);
    if(iteradorAirportOrig == airports.end()){
        return false;
    }

    std::unordered_map<std::string, Aeropuerto>::iterator iteradorAirportDest = airports.find(iataAeroDest);
    if(iteradorAirportDest == airports.end()){
        return false;
    }

    //Creamos el vuelo y cargamos todos los datos
    Vuelo newFlight;
    newFlight.setAerolinea(iteratorAerolines->second);
    newFlight.setAirportOrig(iteradorAirportOrig->second);
    newFlight.setAirportDest(iteradorAirportDest->second);
    newFlight.setFlightNumb(flightNum);
    newFlight.setPlane(plane);
    newFlight.setFecha(fecha);
    newFlight.setDatMeteo(datosMeteo);

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
    std::multimap<std::string, Ruta*>::iterator iteratorRoutes = routesDest.find(iataAeropDest);

    if(iteratorRoutes != routesDest.end()){
        while (iteratorRoutes->first == iataAeropDest){
            if(iteratorRoutes->second->getOrigin()->getIsoPais() == paisOrig){
                std::list<Vuelo*> listFlights = iteratorRoutes->second->getFlights();
                std::list<Vuelo*>::iterator iteratorListFlights = listFlights.begin();
                while (iteratorListFlights != listFlights.end()){
                    if((*iteratorListFlights)->getAeropuertoOrigin()->getIsoPais() == paisOrig){
                        setFlightDestFromCountry.insert((*iteratorListFlights)->getFlightNumb());
                    }
                    ++iteratorListFlights;
                }
                ++iteratorRoutes;
            }
        }
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

Aeropuerto *VuelaFlight::buscaAeropuertoIata(const std::string &iata) {
    std::unordered_map<std::string, Aeropuerto>::iterator iterator = airports.find(iata);
    if(iterator != airports.end()) {
        return &iterator->second;
    }
    return nullptr;
}

unsigned int VuelaFlight::getNumAeropuertos() const {
    return airports.size();
}

std::list<Aeropuerto *> VuelaFlight::getAeropuertos() {
    std::list<Aeropuerto*> listAirports;
    for (std::unordered_map<std::string, Aeropuerto>::iterator iterator = airports.begin(); iterator != airports.end(); ++iterator) {
        listAirports.push_back(&iterator->second);
    }
    return listAirports;
}


void VuelaFlight::eliminarAirport(const std::string &iata) {
    std::multimap<std::string, Ruta>::iterator iteratorRoutesOrigin = routesOrigin.find(iata);
    std::multimap<std::string, Ruta*>::iterator iteratorRoutesDest = routesDest.find(iata);
    if(iteratorRoutesOrigin != routesOrigin.end()){
        // Hacemos esto porque en los multimap los objetos con igual identificador se almacenan en posiciones contiguas de memoria
        while (iteratorRoutesOrigin->first == iata){
            iteratorRoutesOrigin->second.getCompany().bajaAeropuerto(iata);
            iteratorRoutesOrigin = routesOrigin.erase(iteratorRoutesOrigin);
            iteratorRoutesDest = routesDest.erase(iteratorRoutesDest);
        }

    }
    std::unordered_map<std::string, Aeropuerto>::iterator aeropuerto = airports.find(iata);
    airportsUTM.borrar(aeropuerto->second.getX(), aeropuerto->second.getY(),&aeropuerto->second);
    airports.erase(iata);
}


void VuelaFlight::eliminarAirportsInactivos() {
    std::unordered_map<std::string, Aeropuerto>::iterator iteratorAirports = airports.begin();
    while (iteratorAirports != airports.end()){
        if (iteratorAirports->second.getTipo() == "closed"){
            std::unordered_map<std::string, Aeropuerto>::iterator iteratorAirports2 = iteratorAirports;
            ++iteratorAirports;
            eliminarAirport(iteratorAirports2->second.getIata());
        }else{
            ++iteratorAirports;
        }
    }
}

std::vector<Aeropuerto*> VuelaFlight::buscarAriportsRadio(const UTM &pos, float radioKm) {
    std::vector<Aeropuerto*> vectorAirports = airportsUTM.buscarRadio(pos.getLongitud(), pos.getLatitud(), radioKm);

        return vectorAirports;
}

std::list<Aeropuerto *> VuelaFlight::airportsMasSalidas(const UTM &pos, float radioKm) {
    std::vector<Aeropuerto*> vectorAirports = airportsUTM.buscarRadio(pos.getLongitud(), pos.getLatitud(), radioKm);
    std::priority_queue<VuelaFlight::AirportsFlights, std::vector<VuelaFlight::AirportsFlights>, std::less<VuelaFlight::AirportsFlights>> airportQueue;
    std::list<Aeropuerto*> listAirportsDef;

    for (int i = 0; i < vectorAirports.size(); ++i) {
        int numFlights = 0;
        std::list<Ruta*> listRuotes = buscarRutasOrigen(vectorAirports[i]->getIata());
        std::list<Ruta*>::iterator iteratorListRoutes = listRuotes.begin();
        while (iteratorListRoutes != listRuotes.end()){
            numFlights += (*iteratorListRoutes)->getNumFlights();
            ++ iteratorListRoutes;
        }
        AirportsFlights airpflgt(*vectorAirports[i], numFlights);
        airportQueue.push(airpflgt);
    }
    for (int i = 0; i < 5 && i <= airportQueue.size(); ++i) {
        listAirportsDef.push_back(airportQueue.top().airport);
        airportQueue.pop();
    }
    return listAirportsDef;

}

void VuelaFlight::addAirportPostConst(const Aeropuerto &airport) {
    airports.insert(std::make_pair(airport.getIata(),airport));
    airportsUTM.insertar(airport.getX(), airport.getY(), this->buscaAeropuertoIata(airport.getIata()));
}



void VuelaFlight::mostrarEstadoTabla() const {
    std::cout<<"====================================================" <<std::endl;
    std::cout<<"Estado de la tabla hash que almacena los aeropuertos" <<std::endl;
    std::cout<<"====================================================" <<std::endl;
    std::cout<<"Numero de elementos         " <<" | " <<airports.size() <<std::endl;
    std::cout<<"====================================================" <<std::endl;
    std::cout<<"Tamaño de la tabla          " <<" | " <<airports.max_size() <<std::endl;
    std::cout<<"====================================================" <<std::endl;
    std::cout<<"Numero maximo de colisiones " <<" | " <<airports.max_load_factor() <<std::endl;
    std::cout<<"====================================================" <<std::endl;
    std::cout<<"Factor de carga             " <<" | " <<airports.load_factor() <<std::endl;
    std::cout<<"====================================================" <<std::endl;
}

void VuelaFlight::mostrarEstadoMalla() const {
    std::cout<<"====================================================" <<std::endl;
    std::cout<<"Estado de la malla que almacena los aeropuertos" <<std::endl;
    std::cout<<"====================================================" <<std::endl;
    std::cout<<"Numero de elementos:          " <<" | " <<airportsUTM.getnumElementos() <<std::endl;
    std::cout<<"====================================================" <<std::endl;
    std::cout<<"Media de elementos por celda: " <<" | " <<airportsUTM.promedioElementosPorCelda() <<std::endl;
    std::cout<<"====================================================" <<std::endl;
    std::cout<<"Max. elementos por celda:     " <<" | " <<airportsUTM.maxElementosPorCelda() <<std::endl;
    std::cout<<"====================================================" <<std::endl;
}
