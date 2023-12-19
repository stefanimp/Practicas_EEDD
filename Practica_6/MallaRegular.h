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

    class Casilla{
        std::list<T> puntos;
    public:
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

    MallaRegular() = default;
    MallaRegular(float XMin, float YMin, float XMax, float YMax, int nDiv);
    void insertar(float x, float y, const T &dato);
    T *buscar(float x, float y, const T &dato);
    bool borrar(float x, float y, const T &dato);
    // Metodos explicitamente pedidos por la practica
    std::vector<T> buscarRadio(float xcentro, float ycentro, float radio);
    unsigned maxElementosPorCelda();
    float promedioElementosPorCelda();
    float distanciaPtsHaversine(float lat1, float long1, float lat2, float long2){
        float radioTierra = 6378;
        float incremntLat = (lat2 - lat1)*(M_PI/180);
        float incrementLong = (long2 - long1)*(M_PI/180);
        float a = pow(sin(incremntLat/2),2) + cos(lat1*(M_PI/180)) * cos(lat2*(M_PI/180)) * pow(sin(incrementLong/2),2);
        float c = 2 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));
        float distancia = radioTierra*c;
        return distancia;
    }

private:
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
    std::vector<Casilla*> obtenerCasillasCercanas(float xCentro, float yCentro, float radio);

};

template<typename T>
MallaRegular<T>::MallaRegular(float XMin, float YMin, float XMax, float YMax, int nDiv):xMin(XMin), xMax(XMax+0.0001), yMin(YMin), yMax(YMax+0.0001) {
    tamCasillaX = (this->xMax - xMin) / nDiv;
    tamCasilllaY = (this->yMax - yMin) / nDiv;
    mallaRegular.insert(mallaRegular.begin(), nDiv, std::vector<Casilla>(nDiv));
}

template<typename T>
typename MallaRegular<T>::Casilla *MallaRegular<T>::obtenerCasilla(float x, float y) {
    int i = (x - xMin) / tamCasillaX;
    int j = (y - yMin) / tamCasilllaY;
    Casilla *result = nullptr;
    try {
        result = &mallaRegular.at(i).at(j);
    }catch(std::exception &e) {
        std::cout<<e.what() <<std::endl;
    }
    return result;
}

//TODO comprobar que esto funcione
template<typename T>
std::vector<typename MallaRegular<T>::Casilla*> MallaRegular<T>::obtenerCasillasCercanas(float xCentro, float yCentro, float radio) {
    std::vector<Casilla*> vectorCasillas;
    radio = radio/111.1;
    int iInicio = std::max(0, static_cast<int>((xCentro - xMin - radio) / tamCasillaX));
    int iFin = std::min(static_cast<int>(mallaRegular.size()) - 1, static_cast<int>((xCentro - xMin + radio) / tamCasillaX));
    int jInicio = std::max(0, static_cast<int>((yCentro - yMin - radio) / tamCasilllaY));
    int jFin = std::min(static_cast<int>(mallaRegular[0].size()) - 1, static_cast<int>((yCentro - yMin + radio) / tamCasilllaY));

    for (int i = iInicio; i <= iFin; ++i) {
        for (int j = jInicio; j <= jFin; ++j) {
            Casilla*c = nullptr;
            try {
                c = &mallaRegular.at(i).at(j);
                vectorCasillas.push_back(c);
            }catch (std::exception &e){
                std::cout<<e.what() <<std::endl;
            }

        }
    }

    return vectorCasillas;
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
    std::vector<T> vectorCercanos;
    std::vector<Casilla*> vectorCasillas = obtenerCasillasCercanas(xcentro,ycentro,radio);

    for (int i = 0; i < vectorCasillas.size(); ++i) {
        typename std::list<T>::iterator iteratorList = vectorCasillas[i]->puntosl;
        while (iteratorList != vectorCasillas[i]->puntos.end()){
            if(distanciaPtsHaversine(xcentro,ycentro,iteratorList.getX(),iteratorList.getY()) <= radio){
                vectorCercanos.push_back(*iteratorList);
            }
            ++iteratorList;
        }
    }
    return vectorCercanos;
}

template<typename T>
unsigned int MallaRegular<T>::maxElementosPorCelda() {
    return maxElementosCelda;
}

template<typename T>
float MallaRegular<T>::promedioElementosPorCelda() {
    int celdasHorizont = (xMax - xMin)/tamCasillaX;
    int celdasVert = (yMax - yMin)/tamCasilllaY;
    int numCeldas = celdasHorizont*celdasVert;
    return numElementos/numCeldas;
}





#endif //PRACTICA_2_MALLAREGULAR_H