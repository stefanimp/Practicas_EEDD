//
// Created by stefan on 25/09/2023.
//

#ifndef PRACTICA_1_VDINAMICO_H
#define PRACTICA_1_VDINAMICO_H

#include <stdexcept>
#include <algorithm>

template<class T>
class VDinamico{
private:
    T *mem;
    long int tam;
public:
    //TODO documentar el codigo


    /**
     * @brief   Constructor parametrizado de la clase VDinamico.
     * @param[in]n  tamaño que tendra el vector.
     * @post    El objeto es creado con un vector de tamaño n.
     * */
    VDinamico(long int n);

    /**
     * @brief   Constructor parametrizado de la clase VDinamico.
     * @details El nuevo objeto creado copia los atributos del objeto original, pero son atributos independientes a pesar de ser iguales. Es decir, no apuntan a la misma dirección de memoria. Modificar los atributos de uno de los objetos no implica que se modifiquen los atributos del obro objeto.
     * @param[in]original   Objeto del que queremos copiar los atributos.
     * @post    El objeto es creado con atributos iguales que el objeto original.
     * @warning Debemos asegurarnos de que le operador asignación del los objetos que queramos copiar está bien implementado y que ninguna parte del nuevo objeto apunte a la misma parte que le objeto original a copiar.
     * */
    VDinamico(const VDinamico &original);

    /**
     * @brief   Constructor parametrizado de la clase VDinamico.
     * @details Copia cierto numero de elementos desde la posición indicada. El usuario conoce que la posición inicial del vector es 0.
     * @param[in]original   Objeto del que queremos copiar los atributos.
     * @param[in]numelementos   Numero de objetos a copiar del VDinamico original.
     * @param[in]posicionInicial    Posición desde la que se empezarán a copiar los objetos.
     * @throws std::out_of_range    si la posición desde la que queremos copiar los objetos es mayor que el tamaño del vector
     * @throws std::out_of_range    si se quieren copiar más elementos de los que existen.
     * */
    VDinamico(const VDinamico &original, unsigned int posicionInicial, unsigned int numelementos);

    /**
     * @brief   Destructor de la clase VDinamico.
     * */
    ~VDinamico();

    /**
     * @brief   Devuelve el objeto almacenado en la posición que recibe como parámetro el operador.
     * @param[in]pos    Posición del objeto que queremos que nos sea devuelto.
     * @post    El objeto de la posición indicada es devuelto.
     * @throws  std::out_of_range si la posición a la que se quiere acceder es mayor que las posiciones existentes.
     * */
    T &operator[] (unsigned int pos);

    /**
     * @brief   Operador de asignación
     * @details Copia todos los atributos de un objeto a otro. Aunque copie los atributos, estos no deben apuntar a las mismas direcciones de memoria, por ello, en el caso de que haya punteros u objetos en memoria dinámica, el operador asignación debe estar correctamente implementado para que los dos objetos que son diferentes, no tengan atributos que apunten a la misma dirección de memoria.
     * @post    Asigna los atributos de un objeto VDinamico a otro Objeto de tipo VDinamico
     * */
    VDinamico &operator=(VDinamico &arr);

    void ordenar();

    void ordenarREV();

    long int getTam();

    void cambiaElemnto(T elemento, int posicion);

    const int POS_MIN = 0;

};

template<class T>
VDinamico<T>::VDinamico(long int n){
    mem = new T[tam = n];
}

template<class T>
VDinamico<T>::VDinamico(const VDinamico<T> &original):tam(original.tam) {

    //Al ser un vector de un solo puntero y hacer el new ya se crean objetos del tipo T por defecto, a diferencia del vector de doble puntero, que no se crearían los objetos, si no punteros a objetos.
    mem = new T[tam];

    for (int i = 0; i < tam; ++i) {
        //Como los n = tam objetos ya han sido creados anteriormente, ahora solo aplicamos el operador asignación
        mem[i] = original.mem[i];
    }
}

//La posicionInicial es iga al posicon?  Es decir si queremos que empiece desde el primer elemetno posicionInicial seria 1 o 0?????
template<class T>
VDinamico<T>::VDinamico(const VDinamico<T> &original, unsigned int posicionInicial, unsigned int numelementos) {
    if (posicionInicial > original.tam){
        throw std::out_of_range("VDinamico::VDinamico(const VDinamico &original, unsigned int posicionInicial, unsigned int numelementos), Error, la posicion inical no puede ser mayor que le tamaño del vector.");
    }
    if((posicionInicial + numelementos) > original.tam){
        throw std::out_of_range ("\"VDinamico::VDinamico(const VDinamico &original, unsigned int posicionInicial, unsigned int numelementos), Error, el numero de elementos a copiar no puede ser mayor que el numero de elementos disponibles");
    }
    tam = numelementos;
    mem = new T[tam];
    for (int i = posicionInicial, j = 0; i < posicionInicial+numelementos; ++i, ++j) {
        mem[j] = original.mem[i];
    }
}

template<class T>
VDinamico<T>::~VDinamico() {
    delete[] mem;
}

template<class T>
T &VDinamico<T>::operator[](unsigned int pos) {
    if(pos > tam){
        throw std::out_of_range("VDinamico::&operator[], Error, la posicion a la que se pretende acceder no existe");
    }
    return mem[pos];
}

template<class T>
VDinamico<T> &VDinamico<T>::operator=(VDinamico<T> &arr){
    for (int i = 0; i < this->tam = arr.tam; ++i) {
        mem[i] = arr.mem[i];
    }
}

template<class T>
void VDinamico<T>::ordenar() {
    //El primer parametro es el iterador de acceso que dirige a la posicion del primer elemento del intervalo que se va a ordenar
    //El segundo parametro es el iterador de acceso aleatorio que dirige a la posicion situada en posicion despues del ultimo elemento del intervalo que se va a ordenar. Es por esto que ponemos mem + tam y no mem + tam-1

    std::sort(mem, mem + tam);
}

template<class T>
void VDinamico<T>::ordenarREV() {
    //greater: objeto de funcion de predicado definido por el usuario que define el criterio de comparacion que deben cumplir los elementos sucesivos de la ordenacion.
    //COn esto conseguimos que se ordene de meyor a menor
    std::sort(mem, mem + tam, std::greater<T>() );
}

template<class T>
long VDinamico<T>::getTam() {
    return tam;
}

template<class T>
void VDinamico<T>::cambiaElemnto(T elemento, int posicion) {
    if (posicion < POS_MIN){
        throw std::out_of_range("\"VDinamico::cambiaElemento(T elemento, int posicion), Error, la posicion a la que se pretende acceder no existe\"");
    }
    mem[posicion] = elemento;
}


#endif //PRACTICA_1_VDINAMICO_H
