//
// Created by stefan on 02/11/2023.
//

#ifndef PRACTICA_2_AVL_H
#define PRACTICA_2_AVL_H
#include "VDinamico.h"

template<typename T>
class AVL{
private:
    class Nodo{
    public:
            Nodo *izq = nullptr;
            Nodo *derch = nullptr;
            T dato;
            char balance; //-1, 0, 1 para un árbol avl

            /**
             * @brief   Constructor por defecto de la clase Nodo implementada dentro del AVL
             * @warning El balance debe ser gestionado desde la función en la que se creen los nodos
             * @post    El nodo es creado con el dato pasado como parámetro, con balance 0 y sin apuntar a ningún lado
             * */
            Nodo(const T &elemento):izq(nullptr), derch(nullptr), balance(0),dato(elemento){
            }
    };
    Nodo *raiz = nullptr;
    long int numElementos = 0;

    Nodo *preordenCrea(const Nodo* p);
    void postordenDestruye(Nodo* &p);
    void inOrden(Nodo *nodoActual, VDinamico<T*> &vectorDinam);

    //Aquí c guarda la dirección de memoria de un puntero que apunta a un Nodo
    int inserta(Nodo* &nodoInicial, T &dato);
    void rotDerch(Nodo* &nodo);
    void rotIzq(Nodo* &nodo);
    Nodo *buscaClave(T &dato, Nodo *nodoActual);
    unsigned int obtenerAltura(const Nodo *nodo);

public:

    /**
     * @brief   Constructor por defecto de la clase AVL
     * @details Crea un objeto AVL que no contiene ningún dato y cuya raíz apunta a nulo.
     * @post    El objeto AVL es creado
     * */
    AVL();

    /**
     * @brief   Constructor por copia de la clase AVL
     * @param[in]original   objeto AVL del que se copiarán los datos para crear un nuevo AVL.
     * @details  Los datos serán iguales pero independientes.
     * @post    El nuevo AVL es creado como una copia del original.
     * */
    AVL(const AVL<T> &original);

    /**
     * @brief   Destructor de la clase AVL
     * @details Destruye todos los nodos y hace que apunten a nulo
     * @post    El objeto AVL es destruido
     * */
    ~AVL();

    /**
     * @brief   Inserta un dato en el AVL
     * @details Inserta el dato y si el árbol queda desbalanceado lo balancea llamando a las funciones rotDerch y rotIzq
     * @param[in]dato   dato que se quiere insertar en el AVL
     * */
    void inserta( T &dato);

    /**
     * @brief   Operador asignación de la clase AVL
     * @details Destruye los objetos que había al principio y asignas los nuevos creando una copia del original. Llama a las funciones postordenDestruye y preordenCrea
     * @param[in]original   AVL de la que se copiarán los datos.
     * @post    Los datos del AVL se eliminar y reemplazan por una copia del AVL original
     * */
    AVL<T> &operator=(const AVL<T> &original);

    /**
     * @brief   Busca un dato en el AVL de forma recursiva
     * @details Llama a la función buscaClave que realiza la recursividad para encontrar el dato y devuelve nullptr si no se encuentra.
     * @param[in]dato   dato que se quiere buscar en el AVL
     * @return  si se encuentra el dato devuelve un puntero a este
     * @return  si no se encuentra el dato devuelve nullptr.
     * */
    T* buscaRec(T &dato);
    T* buscaIt(const T &dato);
    VDinamico<T*> recorreInOrden();
    unsigned int cantElementos();
    unsigned int altura();
};

template<typename T>
AVL<T>::AVL():raiz(nullptr),numElementos(0) {

}

template<typename T>
typename AVL<T>::Nodo *AVL<T>::preordenCrea(const Nodo *p) {
    if(p){
        Nodo *nodo = new Nodo(p->dato);
        ++numElementos;
        nodo->izq = preordenCrea(p->izq);
        nodo->derch = preordenCrea(p->derch);
        return nodo;
    }
    return nullptr;
}

template<typename T>
void AVL<T>::postordenDestruye(Nodo *&p) {
    if(p){
        postordenDestruye(p->izq);
        postordenDestruye(p->derch);
        delete p;
        p = nullptr;
    }
}


template<typename T>
AVL<T>::AVL(const AVL<T> &original):raiz(original.raiz) {
    if(raiz){
        raiz = preordenCrea(raiz);
    }
}


template<typename T>
AVL<T>::~AVL() {
    postordenDestruye(raiz);
}

template<typename T>
AVL<T> &AVL<T>::operator=(const AVL<T> &original) {
    postordenDestruye(raiz);
    numElementos = 0;
    raiz = preordenCrea(original.raiz);
    return *this;
}

template<typename T>
void AVL<T>::rotDerch(Nodo *&nodo) {
    Nodo *q = nodo;
    Nodo *l;

    nodo = l = q->izq;
    q->izq = l->derch;
    l->derch = q;
    q->balance--;
    if (l->balance > 0){
        q->balance -= l->balance;
    }
    l->balance--;
    if(q->balance < 0){
        l->balance -= -q->balance;
    }
}

template<typename T>
void AVL<T>::rotIzq(Nodo *&nodoOrig) {
    // Creamos las variables auxiliares para poder rotar
    Nodo *nodoAuxiliar1 = nodoOrig; // Asignamos al nodo auxiliar el nodo que queremos rotar
    Nodo *nodoAuxiliar2; // Creamos el segundo nodo auxiliar

    nodoOrig = nodoAuxiliar2 = nodoAuxiliar1->derch; // Asignamos a nodoOrig y a nodoAuxiliar2 el nodo que se encuentra a la izquierda del que queremos rotar
    nodoAuxiliar1->derch = nodoAuxiliar2->izq; // La izquierda del nodo que queremos rotar hacemos que apunte a la derecha del nodoAuxiliar2 (que está apuntando a la izquierda del nodo que queremos rotar)
    nodoAuxiliar2->izq = nodoAuxiliar1; // Hacemos que la derecha del nodoAuxiliar2 apunte al nodo que queremos rotar
    nodoAuxiliar1->balance++;
    if(nodoAuxiliar2->balance < 0){ // Si el nodo que ahora ha quedado por encima del que queríamos rotar tiene un balance superior a 0
        nodoAuxiliar1->balance += -nodoAuxiliar2->balance;
    }
    nodoAuxiliar2->balance++; // Decrementamos en una unidad el balance del nodo que queda por encima del nodo que queríamos rotar
    if(nodoAuxiliar1->balance > 0){ // Si el balance del nodo que queríamos rotar es menor que 0
        nodoAuxiliar2->balance +=   nodoAuxiliar1->balance;
    }
}

template<typename T>
void AVL<T>::inserta(T &dato) {
    inserta(raiz, dato);
}

template<typename T>
int AVL<T>::inserta(Nodo *&nodoInicial, T &dato) {
    Nodo *auxiliar = nodoInicial; // Igualamos el nodo auxiliar a nodoInicial
    int deltaH = 0;

    if(!auxiliar){ //Si no hay nada en el nodoInicial, es decir, hemos llegado a una hoja
        auxiliar = new Nodo(dato); // Creamos un nuevo nodo con el dato
        nodoInicial = auxiliar;
        ++numElementos;
        deltaH = 1;
    } else if(dato > auxiliar->dato){ // Si es igual a 0
        if(inserta(auxiliar->derch, dato)){
            auxiliar->balance--;
            if (auxiliar->balance == -1){
                deltaH = 1;
            } else if(auxiliar->balance == -2){
                if (auxiliar->derch->balance == 1){ // Rotación doble
                    rotDerch(auxiliar->derch);
                }
                rotIzq(nodoInicial); // rotación simple
            }
        }
    } else if(dato < auxiliar->dato){
        if(inserta(auxiliar->izq, dato)){
            auxiliar->balance++;
            if(auxiliar->balance == 1){
                deltaH = 1;
            } else if(auxiliar->balance == 2){
                if(auxiliar->izq->balance == -1){
                    rotIzq(auxiliar->izq);
                }
                rotDerch(nodoInicial);
            }
        }
    }
    return deltaH;
}

template<typename T>
typename AVL<T>::Nodo *AVL<T>::buscaClave( T &dato, Nodo *nodoActual) {
    if(!nodoActual){
        return nullptr;
    }else if(dato < nodoActual->dato){
        return buscaClave(dato, nodoActual->izq);
    }else if(dato > nodoActual->dato){
        return buscaClave(dato, nodoActual->derch);
    }else{
        return nodoActual; // Encontrado
    }
}

template<typename T>
T *AVL<T>::buscaRec(T &dato) {
    Nodo *nodo = buscaClave(dato, raiz);
    return (nodo)? &nodo->dato : nullptr;
}

template<typename T>
T *AVL<T>::buscaIt(const T &dato) {
    Nodo *nodoActual = raiz;
    while (nodoActual){
        if(nodoActual->dato == dato){
            return &nodoActual->dato;
        }else if(dato < nodoActual->dato){
            nodoActual = nodoActual->izq;
        }else if(dato > nodoActual->dato){
            nodoActual = nodoActual->derch;
        }
    }
    return nullptr;
}

template<typename T>
void AVL<T>::inOrden(Nodo *nodoActual, VDinamico<T*> &vectorDinam) {
    if(nodoActual){
        inOrden(nodoActual->izq, vectorDinam);
        vectorDinam.insertar( &(nodoActual->dato));
        inOrden(nodoActual->derch, vectorDinam);
    }
}

template<typename T>
VDinamico<T*> AVL<T>::recorreInOrden() {
    VDinamico<T*> vectorDinam;
    inOrden(raiz, vectorDinam);
    return vectorDinam;
}

template<typename T>
unsigned int AVL<T>::cantElementos() {
    return numElementos;
}

template<typename T>
unsigned int AVL<T>::obtenerAltura(const Nodo *nodo) {
    return (!nodo)? 0 : ((std::max(obtenerAltura(nodo->izq) + 1, obtenerAltura(nodo->derch) + 1) ));
}

template<typename T>
unsigned int AVL<T>::altura() {
    return (obtenerAltura(raiz));
}


#endif //PRACTICA_2_AVL_H
