//
// Created by stefan on 07/10/2023.
//

#ifndef PRACTICA_1B_VDINAMICO_H
#define PRACTICA_1B_VDINAMICO_H

#include <math.h>
#include <algorithm>
#include "climits"

template<class T>
class VDinamico{
private:
    T *mem;
    /**
     * @brief   Tamaño físico del vector dinámico
     * @details Por defecto se inicializa a 1.
     * */
    long int tamFis = 1;        // Tamaño físico del vector mem
    /**
     * @brief   Tamaño lógico del vector dinámico
     * @details Por defecto se inicializa a 0
     * @warning Nunca puede superar al tamaño físico
     * */
    long int tamLog = 0;        // Tamaño lógico del vector mem

    /**
     * @brief   Crea un nuevo vector del tamaño dado a partir del vector del propio objeto copiando desde una posición hasta otra, ambas indicadas como parámetros, y  elimina el vector original.
     * @param[in]desde  posición desde la que se quieren empezar a tomar los datos
     * @param[in]hasta  posición hasta la que se quieren tomar los datos
     * @param[in]tamFisico  tamaño que tendrá el nuevo vector
     * */
    T& crearCopiaAuxiliar(unsigned long desde, unsigned long hasta, unsigned long tamFisico);

    /**
     * @brief   Posición que ocupa el primer elemento de un vector
     * */
    const int PRIMERA_POS = 0;

public:

    /**
     * @brief   Constructor por defecto de la clase VDinamico
     * @details El tamaño lógico queda inicializado a 0 y el tamaño físico a 1
     * @post    El objeto queda creado
     * */
    VDinamico();

    /**
     * @brief   Constructor parametrizado de la clase VDinamico.
     * @details El tamaño físico es potencia de 2 inmediatamente superior al tamaño lógico(tamLog).
     * @param[in]tamLog Tamaño lógico que tendrá en vector de VDinamico.
     * @post    El objeto es creado con el tamaño lógico indicado y en un tamaño físico que es potencia de 2 inmediatamente superior al tamaño lógico.
     * */
    VDinamico(unsigned int tamLog);

    /**
     * @brief   Constructor por copia de la clase VDinamico
     * @details El nuevo objeto creado copia los atributos del objeto original, pero son atributos independientes a pesar de ser iguales. Es decir, no apuntan a la misma dirección de memoria. Modificar los atributos de uno de los objetos no implica que se modifiquen los atributos del obro objeto.
     * @param[in]original   Objeto del que vamos a copiar los atributos
     * @post    EL objeto es creado con atributos iguales que el objeto original.
     * @throw   std::invalid_argument Si la dirección de memoria del objeto del que se van a copiar los atributos está vacía.
     * */
    VDinamico(const VDinamico &original);

    /**
     * @brief   Constructor por copia parcial de la clase VDinamico
     * @details El nuevo objeto creado copia los atributos y cierto numero de elementos(numElementos) desde la posición indicada(posicionIncial) del objeto original. El usuario conoce que la primera posición del vector es 0 y que la ultima es tamLog -1.
     * @param[in]original   Objeto del que queremos copiar los atributos
     * @param[in]numElementos   Número de elementos del vector del objeto que se quieren copiar
     * @param[in]posicionInicial    Posición inicial desde la que se copiaran los elementos del vector del objeto original
     * @throws std::out_of_range    Si la posición inicial es superior al tamaño lógico del vector del que se pretenden copiar los elementos
     * @throws std::out_of_range    Si el numero de elementos que se pretende copiar es mayor que el numero de elementos disponibles para copiar.
     * */
    VDinamico(const VDinamico &original, long unsigned int posicionInicial, long unsigned int numElementos);

    /**
     * @brief   Destructor de la clase VDinamico
     * @post    Se destruye el objeto junto al resto de objetos almacenados en el vector.
     * */
    ~VDinamico();

    /**
     * @brief   Operador [] de la clase VDinamico
     * @details Devuelve el objeto situado en la posición del vector indicada como parámetro
     * @param[in]pos    Posición de la que se quiere devolver el objeto
     * @throw std::out_of_range si la posición a la que se quiere acceder es mayor que le tamaño lógico del vector
     * */
    T &operator[] (long unsigned int posicion);

    /**
     * @brief   Operador asignación de la clase VDinamico
     * @details Copia todos los atributos de un objeto a otro. Aunque copie los atributos, estos no deben apuntar a las mismas direcciones de memoria, por ello, en el caso de que haya punteros u objetos en memoria dinámica, el operador asignación debe estar correctamente implementado para que los dos objetos que son diferentes, no tengan atributos que apunten a la misma dirección de memoria.
     * @post    Asigna los atributos de un objeto VDinamico a otro objeto de tipo VDInamico
     * */
    VDinamico &operator=(VDinamico &original);

    /**
     * @brief   Inserta un dato en la posición indicada o al final del vector si la posición es igual a UINT_MAX
     * @details Utiliza la función T* crearCopiaAuxiliar(unsigned long desde, unsigned long hasta, unsigned long tamFisico) para crear un nuevo vector auxilar si tamFis == tamLog y ahora inserta el nuevo dato.
     * @param[in]posicion   Posición en la que se quiere insertar en dato, si es igual a UINT_MAX se coloca al final del vector(es decir en la posición tamLog)
     * @param[in]dato   Dato que se quiere insertar en el vector
     * @throws std::out_of_range si posicion es mayor que tamLog y distinto de UINT_MAX
     * @throws std::invalid_argument si el dato que se quiera insertar apunta a una dirección de memoria vacía
     * */
    void insertar(const T &dato, long unsigned int posicion = UINT_MAX);

    /**
     * @brief   Elimina el dato de la posición indicada
     * @details Elimina el dato de la posición indicada. Si la posición indicada coincide con UINT_MAX se acorta el tamaño lógico del vector en una unidad y el dato que se elimina es el ultimo del vector. En caso de que le tamaño lógico sea menor que la tercera parte del tamaño físico este se verá reducido a la mitad.
     * @param[in]pos    Posición del dato que se quiere eliminar
     * @throw   std::out_of_range si la posición es mayor que le tamaño lógico y distinta de UINT_MAX
     * @post    Si se elimina el ultimo objeto del vector este se devuelve con un return
     * @post    El objeto queda borrado
     * @return  El elemento borrado si este es el que ocupa la ultima posición del vector
     * */
    T& borrar(long unsigned int pos = UINT_MAX);

    /**
     * @brief   Ordena de menor a mayor el vector
     * @details Ordena de menor a mayor el vector usando la función sort de la biblioteca algorithm
     * @post    El vector queda ordenado de menor a mayor
     * */
    void ordenar();

    /**
     * @brief   Ordena de mayor a menor el vector
     * @details Ordena de mayor a menor usando la función sort de la biblioteca algorithm
     * @post    El vector queda ordenado de menor a mayor
     * */
    void ordenarRev();

    /**
     * @brief   Búsqueda binaria de un elemento dentro del vector
     * @return  Si se encuentra el objeto, devuelve la posición en la que se han encontrado
     * @return  Si no se encuentra el objeto devuelve un -1
     * */
    int busquedaBin(T &dato);

    /**
     * @brief   Devuelve el tamaño lógico del vector
     * @post    Devuelve el valor del atributo tamLog
     * */
    long unsigned int tamLogigo();

    /**
     * @brief   Cambia el valor del tamaño lógico
     * @param[in]tamLog Nuevo valor que tendrá el atributo tamLog
     * @post    El valor del atributo tamLog queda modificado
     * */
    void setTamLogico(long unsigned int tamLog);

    /**
     * @brief   Devuelve la dirección de memoria del vector del objeto VDinamico
     * */
    T *getMem() const;



};

template<class T>
VDinamico<T>::VDinamico():tamLog(0),tamFis(1) {
    mem = new T[tamFis];
}

template<class T>
VDinamico<T>::VDinamico(unsigned int tamLog):tamLog(tamLog) {
    mem = new T[tamFis = (pow(2,(log2(tamLog))+1))];
}

template<class T>
VDinamico<T>::VDinamico(const VDinamico<T> &original) {
    if (&original == nullptr){
        throw std::invalid_argument("VDinamico::VDinamico(const VDinamico &oiginal, se estan copiando valores de un objeto que no existe");
    }
    tamFis = original.tamFis;
    tamLog = original.tamLog;

    mem = new T[tamFis];
    //Al ser un vector de un solo puntero y hacer el new ya se crean objetos del tipo T por defecto, a diferencia del vector de doble puntero, que no se crearían los objetos, sino punteros a objetos.
    for (int i = 0; i < tamLog; ++i) {
        //Como los n = tam objetos ya han sido creados anteriormente, ahora solo aplicamos el operador asignación
        mem[i] = original.mem[i];
    }
}

template<class T>
VDinamico<T>::VDinamico(const VDinamico<T> &original, unsigned long posicionInicial, unsigned long numElementos) {
    if(posicionInicial >= original.tamLog){
        throw std::out_of_range("VDinamico::VDinamico(const VDinamico<T> &original, unsigned long posicionInicial, unsigned long numElementos), Error, la posicion inicial no puede ser mayor que el tamaño logico del vector.");
    }
    if((posicionInicial + numElementos) > original.tamLog){
        throw std::out_of_range("\"VDinamico::VDinamico(const VDinamico<T> &original, unsigned long posicionInicial, unsigned long numElementos), Error, el numero de elementos a copiar no puede ser mayor que el numero de elementos disponibles");
    }
    tamLog = numElementos;
    tamFis = (pow(2,(log2(tamLog))+1));

    mem = new T[tamFis];
    for (int i = 0; i < tamLog; ++i) {
        mem[i] = original.mem[i];
    }
}

template<class T>
VDinamico<T>::~VDinamico() {
    delete[] mem;
}

template<class T>
T &VDinamico<T>::crearCopiaAuxiliar(unsigned long desde, unsigned long hasta, unsigned long tamFisico) {
    T *aux = new T[tamFisico];
    for (int i = desde, j = 0; i < hasta; ++i, ++j) {
        aux[j] = mem[i];
    }
    delete[] mem;
    return *aux;
}

template<class T>
T &VDinamico<T>::operator[](long unsigned int pos) {
    if(pos > tamLog){
        throw std::out_of_range("VDinamico::&operator[], Error, la posición de memoria a la que se quiere acceder no almacena ningún objeto.");
    }
    return mem[pos];
}

template<class T>
VDinamico<T> &VDinamico<T>::operator=(VDinamico<T> &original) {
    if(this != &original){
        this->tamFis = original.tamFis;
        delete[] mem;
        mem = new T[tamFis];
        for (int i = 0; i < (this->tamLog = original.tamLog); ++i) {
            mem[i] = original.mem[i];
        }
    }

    return *this;
}


template<class T>
void VDinamico<T>::insertar(const T &dato, long unsigned int posicion) {
    if(posicion>tamLog && posicion!= UINT_MAX){
        throw std::out_of_range("VDinamico::insertar(sont T &dato, unsigned int posicion), Error, no se puede introducir el elemento en una posición superior a las disponibles");
    }
    if(&dato == nullptr){
        throw std::invalid_argument("VDinamico::insertar(sont T &dato, unsigned int posicion), Error, la posicón de memoria del dato que se pretende insertar está vacia");
    }
    if(posicion == UINT_MAX){
        if(tamLog == tamFis){
            mem = &crearCopiaAuxiliar(PRIMERA_POS,tamLog,tamFis = tamFis * 2);
        }
        mem[tamLog++] = dato;
    }else{
        if(tamLog == tamFis){
            mem = &crearCopiaAuxiliar(PRIMERA_POS,tamLog,tamFis = tamFis * 2);
        }
        if(tamLog == 0){
            for (int i = tamLog; i > posicion; --i) {
                mem[i+1] = mem[i];
            }
        }else{
            for (int i = tamLog - 1; i >= posicion; --i) {
                mem[i+1] = mem[i];
            }
        }
        mem[posicion] = dato;
        ++tamLog;
    }
}

template<class T>
T &VDinamico<T>::borrar(unsigned long int posiscion) {
    if (posiscion > tamLog  && posiscion != UINT_MAX){
        throw std::out_of_range("VDinamico::borrar(unsigned long int pos), Error, la posición a la que se intenta acceder no pertenece al vector.");
    }
    if(posiscion == UINT_MAX){
        if((tamLog*3) < tamFis){
            tamFis /= 2;
            T *aux = new T[tamFis];
            for (int i = 0; i < tamLog; ++i) {
                aux[i] = mem[i];
            }
            delete[] mem;
            mem = aux;
        }
        return mem[tamLog--];
    }else{
        if ((tamLog*3) < tamFis){
            tamFis /= 2;
            T *aux = new T[tamFis];
            for (int i = posiscion; i < tamLog; ++i) {
                aux[i] = mem[i+1];
            }
            delete[] mem;
            mem = aux;
        }else{
            for (int i = posiscion; i < tamLog; ++i) {
                mem[i] = mem[i+1];
            }
        }
        --tamLog;
    }
}

template<class T>
void VDinamico<T>::ordenar() {
    //El primer parametro es el iterador de acceso que dirige a la posicion del primer elemento del intervalo que se va a ordenar
    //El segundo parametro es el iterador de acceso aleatorio que dirige a la posicion situada en posicion despues del ultimo elemento del intervalo que se va a ordenar. Es por esto que ponemos mem + tamLog y no mem + tamLog-1

    std::sort(mem, mem + tamLog);
}

template<class T>
void VDinamico<T>::ordenarRev() {
    std::sort(mem, mem + tamLog, std::greater() );
}

template<class T>
int VDinamico<T>::busquedaBin(T &dato) {
    int inferior = 0;
    int superiror = tamLog - 1;
    int curIn;

    while (inferior <= superiror){
        curIn = (inferior + superiror)/2;
        if(mem[curIn] == dato){
            return curIn;
        }else{
            if(mem[curIn] < dato){
                inferior = curIn + 1;
            }else{
                superiror = curIn - 1;
            }
        }
    }
    return -1;
}

template<class T>
unsigned long VDinamico<T>::tamLogigo() {
    return tamLog;
}

template<class T>
void VDinamico<T>::setTamLogico(unsigned long tamLog) {
    this->tamLog = tamLog;
}

template<class T>
T *VDinamico<T>::getMem() const {
    return mem;
}


#endif //PRACTICA_1B_VDINAMICO_H
