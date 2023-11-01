#include <iostream>
#include "VDinamico.h"
#include <random>

//TODO añadir la excepciones correspondientes
//Añadde numero enteros aleatorios comprobando que ninguno sea repetido
template<class T>
void generarNumerosAleatoriosUnicos(long int desde, long int hasta, VDinamico<T> &vec){
    //Esta es la semilla para generar nuemros aleatorios
    std::random_device rd;
    //Generador de numeros aleatorios
    std::mt19937 gen(rd());
    //Distribución uniforme en el rando "desde" y "hasta"
    std::uniform_int_distribution<int> distribution(desde, hasta);

    for (int i = 0; i < vec.getTam(); ++i) {
        bool existe = false;
        do{
            existe = false;
            int numAleatorio = distribution(gen);
            for (int j = 0; j < i; ++j) {
                if(numAleatorio == vec[j]){
                    existe = true;
                }
            }
            if(!existe){
                vec.cambiaElemnto(numAleatorio,i);
            }
        }while (existe);
    }
}

int main() {

    VDinamico vec_int = VDinamico<int>(10000);

    generarNumerosAleatoriosUnicos(0,10000,vec_int);

    std::cout<<"Prineras 20 posiciones del vector  aleatoriamente:" <<std::endl;
    for (int i = 0; i < 20; ++i) {
        std::cout<<vec_int[i] <<std::endl;
    }

    vec_int.ordenar();
    std::cout<<"Prineras 20 posiciones del vector ordenado de menor a mayor:" <<std::endl;
    for (int i = 0; i < 20; ++i) {
        std::cout<<vec_int[i] <<std::endl;
    }

    vec_int.ordenarREV();
    std::cout<<"Prineras 20 posiciones del vector ordenado de mayor a menor:" <<std::endl;
    for (int i = 0; i < 20; ++i) {
        std::cout<<vec_int[i] <<std::endl;
    }



    return 0;
}