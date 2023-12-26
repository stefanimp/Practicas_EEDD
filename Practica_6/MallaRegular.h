//
// Created by stefan on 17/12/2023.
//

#ifndef PRACTICA_2_MALLAREGULAR_H
#define PRACTICA_2_MALLAREGULAR_H

#include <iostream>
#include <vector>
#include <list>
#include <cmath>

template<typename T>
class MallaRegular{
public:
    MallaRegular() = default;
    MallaRegular(float XMin, float YMin, float XMax, float YMax, int nDiv);
    void insertar(float x, float y, const T &dato);
    T *buscar(float x, float y, const T &dato);
    bool borrar(float x, float y, const T &dato);
    // Metodos explicitamente pedidos por la practica
    std::vector<T> buscarRadio(float xcentro, float ycentro, float radio);
    unsigned maxElementosPorCelda() const;
    float promedioElementosPorCelda() const;
    int getnumElementos() const;
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

private:

    class Casilla{
    public:
        std::list<T> puntos;
        Casilla():puntos(){}
        void insertar(const T &dato){
            puntos.push_back(dato);
        }
        T *buscar(const T &dato){
            typename std::list<T>::iterator iteratorList;
            iteratorList = puntos.begin();
            for (; iteratorList != puntos.end() ; ++iteratorList) {
                if(*iteratorList == dato){
                    return &(*iteratorList);
                }
            }
        }
        bool borrar(const T &dato){
            typename std::list<T>::iterator iteratorList;
            iteratorList = puntos.begin();
            for (; iteratorList != puntos.end() ; ++iteratorList) {
                if(*iteratorList == dato){
                    puntos.erase(iteratorList);
                    return true;
                }
            }
            return false;
        }

        int numElementos() const{
            return puntos.size();
        }
    };

    //Tamaño real global
    float xMin = 0;
    float xMax = 0;
    float yMin = 0;
    float yMax = 0;
    //Tamaño real de cada sacilla
    float tamCasillaX = 0;
    float tamCasilllaY = 0;
    // Otros atributos
    int maxElementosCelda = 0;
    int numElementos = 0;
    std::vector<std::vector<Casilla>> mallaRegular;
    Casilla *obtenerCasilla(float x, float y);
    std::vector<T> obtenerElementosRectangulo(float xCentro, float yCentro, float radio);

};

template<typename T>
MallaRegular<T>::MallaRegular(float XMin, float YMin, float XMax, float YMax, int nDiv):xMin(XMin), xMax(XMax+0.0001), yMin(YMin), yMax(YMax+0.0001) {
    tamCasillaX = (this->xMax - xMin) / nDiv;
    tamCasilllaY = (this->yMax - yMin) / nDiv;
    mallaRegular.insert(mallaRegular.begin(), nDiv, std::vector<Casilla>(nDiv));
}

template<typename T>
typename MallaRegular<T>::Casilla *MallaRegular<T>::obtenerCasilla(float x, float y) {
    int j = (x - xMin) / tamCasillaX;
    int i = (y - yMin) / tamCasilllaY;
    Casilla *result = nullptr;
    try {
        result = &mallaRegular.at(i).at(j);
    }catch(std::exception &e) {
        std::cout<<e.what() <<std::endl;
    }
    return result;
}

template<typename T>
T *MallaRegular<T>::buscar(float x, float y, const T &dato) {
    Casilla *casilla = obtenerCasilla(x,y);
    typename std::list<T>::iterator iteratorPts = casilla->puntos.begin();
    while (iteratorPts != casilla->puntos.end()){
        if (iteratorPts == dato){
            T *dato = iteratorPts;
            casilla->puntos.erase(iteratorPts);
            return dato;
        }
        ++iteratorPts;
    }
}


template<typename T>
std::vector<T > MallaRegular<T>::obtenerElementosRectangulo(float xCentro, float yCentro, float radio) {
    std::vector<T> vectorElementos;
    radio /= 111.1;

    int iInicio = (xCentro - xMin - radio) / tamCasillaX;
    int iFin = (xCentro - xMin + radio) / tamCasillaX;
    int jInicio = (yCentro - yMin - radio) / tamCasilllaY;
    int jFin = (yCentro - yMin + radio) / tamCasilllaY;

    //Comprobamos que los puntos calculados estén dentro de los límites de la malla
    if(iInicio < xMin){
        iInicio = xMin;
    }
    if(iFin > xMax){
        iFin = xMax;
    }
    if(jInicio < yMin){
        jInicio = yMin;
    }
    if(jFin > yMax){
        jFin = yMax;
    }

    for (int i = iInicio; i <= iFin; ++i) {
        for (int j = jInicio; j <= jFin; ++j) {
            Casilla*c = nullptr;
            try {
                //TODO cambiar los at por [] cuando compruebe que funciona
                c = &mallaRegular.at(j).at(i);
                typename std::list<T>::iterator iteratorCasilla = c->puntos.begin();
                while (iteratorCasilla != c->puntos.end()){
                    vectorElementos.push_back((*iteratorCasilla));
                    ++iteratorCasilla;
                }
            }catch (std::exception &e){
                std::cout<<e.what() <<std::endl;
            }

        }
    }

    return vectorElementos;
}



template<typename T>
void MallaRegular<T>::insertar(float x, float y, const T &dato) {
    Casilla *casilla = obtenerCasilla(x,y);
    casilla->insertar(dato);
    if (casilla->numElementos() > maxElementosCelda){
        maxElementosCelda = casilla->numElementos();
    }
    ++numElementos;
}

template<typename T>
bool MallaRegular<T>::borrar(float x, float y, const T &dato) {
    Casilla *casilla = obtenerCasilla(x,y);
    return casilla->borrar(dato);
}

template<typename T>
std::vector<T> MallaRegular<T>::buscarRadio(float xcentro, float ycentro, float radio) {
    std::vector<T> vectorElementos = obtenerElementosRectangulo(xcentro,ycentro,radio);
    std::vector<T> vectorCercanos;

    for (int i = 0; i < vectorElementos.size(); ++i) {
        if(distanciaPtsHaversine(xcentro,ycentro,vectorElementos.at(i)->getX(),vectorElementos.at(i)->getY()) <= radio){

            vectorCercanos.push_back(vectorElementos[i]);
        }
    }

    return vectorCercanos;
}


template<typename T>
unsigned int MallaRegular<T>::maxElementosPorCelda() const{
    return maxElementosCelda;
}

template<typename T>
float MallaRegular<T>::promedioElementosPorCelda() const{
    int celdasHorizont = (xMax - xMin)/tamCasillaX;
    int celdasVert = (yMax - yMin)/tamCasilllaY;
    int numCeldas = celdasHorizont*celdasVert;
    return numElementos/numCeldas;
}

template<typename T>
int MallaRegular<T>::getnumElementos() const {
    return numElementos;
}




#endif //PRACTICA_2_MALLAREGULAR_H