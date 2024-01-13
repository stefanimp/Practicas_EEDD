//
// Created by stefan on 16/10/2023.
//

#ifndef PRACTICA_1B_LISTAENLAZA_H
#define PRACTICA_1B_LISTAENLAZA_H

#include <iostream>

template<typename T>
class ListaEnlazada {
private:
    class Nodo{
    public:
        //Atributos
        T dato;
        Nodo *siguiente;
        //Constructores y destructor

        /**
         * @brief   Constructor parametrizado de la clase Nodo
         * @details El atributo siguiente, por defecto, hace que el puntero a siguiente apunte a nulo.
         * @param[in]dato   dato que se quiere almacenar en el nodo
         * @param[in]siguiente  puntero al siguiente nodo en la secuencia
         * @post    El objeto es creado
         * */
        Nodo(const T &dato, Nodo *siguiente = nullptr):dato(dato), siguiente(siguiente){

        };

    };

    Nodo *cabecera = nullptr;
    Nodo *cola = nullptr;
    long int tam = 0;


public:
    class Iterador{
        //TODO ¿porqué estos no se ponen en private?
        Nodo *nodo = nullptr;
        template<class> friend class ListaEnlazada;
    public:
        //Constructores y destructor

        /**
         * @brief   Constructor parametrizado de la clase Iterador
         * @param[in]nodo   Nodo desde el que se quiere iterar
         * @post    El objeto es creado
         * */
        Iterador(Nodo *nodo):nodo(nodo){
        };

        /**
         * @brief   Destructor de la clase Iterador
         * @post    El objeto es destruido
         * */
        ~Iterador(){
            nodo = nullptr;
        };

        //Otros métodos
        /**
         * @brief   Devuelve true si se el atributo nodo es igual a nullptr.
         * @details Esto quiere decir, desde el punto de vista de un Iterador de listas Simplemente Enlazadas, se ha llegado al final de la lista
         * @return  Devuelve el valor verdadero si nodo = nullptr.
         * @return  Devuelve el valor falso si nodo = nullptr.
         * */
        bool fin(){
            return nodo == nullptr;
        };

        /**
         * @brief   Actualiza el atributo nodo al siguiente del que había antes.
         * @post    El atributo nodo queda modificado y  se avanza una posición en la lista
         * */
        void siguiente(){
            nodo = nodo->siguiente;
        };

        /**
         * @brief   Devuelve el dato que se encuentra almacenado en el atributo Nodo
         * @post    El dato es devuelto
         * */
        T &dato(){
            return nodo->dato;
        };

        //Operadores

        /**
         * @brief   Operador *
         * @details Devuelve el dato que se encuentra almacenado en el atributo Nodo
         * */
        T &operator*(){
            return nodo->dato;
        };

        /**
         * @brief   Operador de comparación de la clase Iterador
         * @details Develve true si los Nodos que contienen son iguales y false si no lo són
         * @return  Un booleano con el resultado de comparar ambos iteradores
         * */
        bool operator==(const Iterador &original){
            return (nodo == original.nodo);
        };

    };


    /**
     * @brief   Constructor por defecto de la clase ListaEnlazada.
     * @details Por defecto no tiene contiene nodos por lo que sus parámetros apuntan a nulo.
     * @post    La lista enlazada es creada pero no contiene Nodos o datos.
     * */
    ListaEnlazada();

    /**
     * @brief   Constructor parametrizado de la clase ListaEnlazada.
     * @details Crea otra lista enlazada independiente de la original pero con una copia de los datos que había.
     * @param[in]original   Lista de la que copiaremos los datos o Nodos
     * */
    ListaEnlazada(const ListaEnlazada &original);

    /**
     * @brief   Destructor de la clase ListaEnlazada
     * @details Destruye el objeto y todos los Nodos o datos que contiene, comenzado desde la cabecera.
     * @post    El objeto y todos los qe contiene quedan destruidos
     * */
    ~ListaEnlazada();

    /**
     * @brief   Operador asignación de la clase ListaEnlazada
     * @details Destruye los datos de la lista actual y los reemplaza por una copia de los que figuran en la lista original.
     * @param[in]original   Lista enlazada de la que se copiarán los Nodos o datos.
     * @post    Los datos de la lista se eliminar y reemplazan por los de la lista original
     * */
    ListaEnlazada &operator=(const ListaEnlazada &original);

    /**
     * @brief   Crea un iterador que comienza en la cabecera de la lista
     * @details Creamos el objeto iterador dentro de esta función y lo devolvemos completo ya que ha sido creado dentro de este método y lo necesitaremos desde donde se esté llamando.
     * @return  Devuelve un iterador para la lista enlazada uqe comienza en la cabecera de la lista.
     * @post    El objeto Iterador es creado y devuelto
     * */
    Iterador iterador();

    /**
     * @brief   Inserta un Nodo con el dato dado en el inicio de la lista.
     * @details La inserción en el principio tiene un coste de O(1). El valor del atributo tam se incrementa en una unidad.
     * @param[in]dato   dato que contendrá el Nodo que será insertado en el principio de la lista enlazada.
     * @post    El nuevo Nodo que contiendo el dato pasado como parámetro es insertado al principio de la lista enlazada
     * */
    void insertarInicio(const T &dato);

    /**
     * @brief   Inserta un Nodo con el dato dado el final de la lista.
     * @details La inserción se realiza en el final y tiene un coste de O(1). El valor del atributo tam se incrementa en una unidad.
     * @param[in]dato   dato que contendrá el Nodo el cual será insertado en el principio de la lista enlazada.
     * @post    El nuevo  Nodo que contiendo el dato pasado como parámetro es insertado al final de la lista enlazada.
     * */
    void insertarFinal(const T &dato);

    /**
     * @brief   Inserta el dato en la posición anterior apuntada por el parámetro iterador
     * @details Se inserta un Nodo que contiene el dato dado como parámetro delante del Nodo al que apunta el iterador pasado como parámetro. Si no se encuentra el nodo no se inserta nada. Tiene un coste O(n). El valor del atributo tam se incrementa en una unidad.
     * @param[in]iterador   Iterador que ocontiene el Nodo que quedará detras del nuevo Nodo con el dato.
     * @param[in]dato   Dato que se quiere insertar en la lista enlazada
     * @pre El dato del iterador pasado como parámetro debe pertenecer a la lista.
     * @post    El objeto es insertado.
     * @warning Si la precondición deja de existir, deberemos modificar la condición de parada del bucle while para que pare si llega el final de la lista.
     * */
    void insertar(const Iterador &iterador,const  T &dato);

    /**
     * @brief   Inserta el dato en la posición posterior apuntada por el parámetro iterador
     * @details Se inserta un Nodo que contiene el dato dado como parámetro detrás del Nodo al que apunta el iterador pasado como parámetro. Tiene un coste de O(1). El valor del atributo tam se incrementa en una unidad.
     * @param[in]iterador   Iterador que ocontiene el Nodo que quedará delante del nuevo Nodo con el dato.
     * @param[in]dato   Dato que se quiere insertar en la lista enlazada
     * @pre El dato del iterador pasado como parámetro debe pertenecer a la lista.
     * */
    void insertarDetras(const Iterador &iterador, const T &dato);

    /**
     * @brief   Borra el nodo sitiado en el inicio de la lista enlazada
     * @details Borra el nodo sitiado en el inicio de la lista enlazada coon un coste de O(n). El valor del atributo tam se decrementa en una unidad.
     * @post    El nodo queda eliminado
     * */
    void borrarIncicio();

    /**
     * @brief   Borra el nodo sitiado en el final de la lista enlazada
     * @details Borra el nodo sitiado en el final de la lista enlazada coon un coste de O(1), El valor del atributo tam se decrementa en una unidad.
     * @post    El nodo queda eliminado
     * */
    void borrarFinal();

    /**
     * @brief   Borrar el elemento sitiado el la posición indicada por el iterador
     * @details Coste O(n). Si no se encuentra el nodo que se quiere borrar, ninguno será borrado. El valor del atributo tam se decrementa en una unidad.
     * @pre     El dato del iterador pasado como parámetro debe pertenecer a la lista,ya que si no estaremos haciendo una opreracíon O(n).
     * @warning Si la precondición deja de existir, deberemos modificar la condición de parada del bucle while para que pare si llega el final de la lista.
     * @post    El elemento queda eliminado
     * */
    void borrar(const Iterador &iterador);

    /**
     * @brief   Devuelve el dato almacenado en el primer Nodo de la lista
     * @return  Devuelve el dato almacenado en el primer Nodo de la lista
     * @post    El dato almacenado en el primer Nodo de la lista es devuelto
     * */
    T& inicio() const;

    /**
     * @brief   Devuelve el dato almacenado en el último Nodo de la lista
     * @return  Devuelve el dato almacenado en el último Nodo de la lista
     * @post    El dato almacenado en el último Nodo de la lista es devuelto
     * */
    T& fin() const;

    /**
     * @brief   Devuelve el tamaño de la lista
     * */
    long int getTam() const;

    /**
     * @brief   Concatena la lista actual con la lista proporcionada por parámetro.
     * @details Concatena la lista actual con la lista proporcionada por parámetro. El método devuelve una referencia a la lista concatenada.
     * @param[in]original   Lista que se va a concatener con la lista actual
     * @return  Una referencia a la lista concatenada
     * */
    ListaEnlazada<T> concatena(const ListaEnlazada<T> &original);

    /**
     * @brief   Operador suma de dos listas enlazadas que las concatena
     * @details Concatena la lista actual con la lista proporcionada por parámetro. El método devuelve una referencia a la lista concatenada.
     * @param[in]original   Lista que se va a concatener con la lista actual
     * @return  Una referencia a la lista concatenada
     * */
    ListaEnlazada<T> operator+(const ListaEnlazada<T> &original);


};

template<typename T>
ListaEnlazada<T>::ListaEnlazada():cabecera(nullptr), cola(nullptr) {

}

template<typename T>
typename ListaEnlazada<T>::Iterador ListaEnlazada<T>::iterador(){
    return Iterador(cabecera);
}

template<typename T>
ListaEnlazada<T>::ListaEnlazada(const ListaEnlazada<T> &original):cabecera(original.cabecera), cola(original.cola),tam(original.tam) {
    //Consructor con Nodos
    if(original.cabecera){ // Comprobamos si la lista de la que queremos copiar los objetos está vacía, si lo está, no se hace nada
        //Creamos el primer nodo del nuevo objeto
        cabecera = new Nodo(original.cabecera->dato);
        // Creamos dos nodos auxiliares para asignar los nuevos nodos y recorrer la lista
        Nodo *nodoActual = cabecera;
        Nodo *nodoOriginal = original.cabecera;

        while (nodoOriginal->siguiente){
            nodoActual->siguiente = new Nodo(nodoOriginal->siguiente->dato);
            nodoOriginal = nodoOriginal->siguiente;
            nodoActual = nodoActual->siguiente;
        }
        cola = nodoActual;
    }
}

template<typename T>
ListaEnlazada<T>::~ListaEnlazada() {
    Nodo *nodoeliminado;
    while(cabecera){
        nodoeliminado = cabecera;
        cabecera = cabecera->siguiente;
        delete nodoeliminado;
    }
    cola = nullptr; // Importante que al eliminar el objeto, todos sus atributos apunten a nullptr
}


template<typename T>
ListaEnlazada<T> &ListaEnlazada<T>::operator=(const ListaEnlazada<T> &original) {
    //Primero borramos el contenido de la lista enlazada, es el mismo código que le del destructor
    Nodo *nodoeliminado;
    while(cabecera){
        nodoeliminado = cabecera;
        cabecera = cabecera->siguiente;
        delete nodoeliminado;
    }   
    cola = nullptr; // Importante que al eliminar el objeto, todos sus atributos apunten a nullptr
    // Este es el mismo código que el del constructor por copia
    if(original.cabecera){ // Comprobamos si la lista de la que queremos copiar los objetos está vacía, si lo está, no se hace nada
        //Creamos el primer nodo del nuevo objeto
        cabecera = new Nodo(original.cabecera->dato);
        // Creamos dos nodos auxiliares para asignar los nuevos nodos y recorrer la lista
        Nodo *nodoActual = cabecera;
        Nodo *nodoOriginal = original.cabecera;

        while (nodoOriginal->siguiente){
            nodoActual->siguiente = new Nodo(nodoOriginal->siguiente->dato);
            nodoOriginal = nodoOriginal->siguiente;
            nodoActual = nodoActual->siguiente;
        }
        cola = nodoActual;
    }
    tam = original.tam;
    return *this;
}

template<typename T>
void ListaEnlazada<T>::insertarInicio(const T &dato) {
    Nodo *nuevo = new Nodo(dato, cabecera);
    if(cola == nullptr){ // Si la lista está vacia
        cola = nuevo;
    }
    cabecera = nuevo;
    ++tam;
}

template<typename T>
void ListaEnlazada<T>::insertarFinal(const T &dato) {
    Nodo *nuevo; // Creamos un nuevo nodo que será el primero de la lista
    nuevo = new Nodo(dato, nullptr); // Llamamos al constructor de la clase Nodo y  le pasamos el dato que queremos insertar en la lista y nullptr ya que será el último elemento de la lista

    if(cola != nullptr){
        // Este fragmento se ejecutará solo si la lista no está vacia
        cola->siguiente = nuevo;
    }
    if(cabecera == nullptr){ // Esto se ejecutará si la lista está vacía
        cabecera = nuevo;
    }
    ++tam;
    cola = nuevo;
}

template<typename T>
void ListaEnlazada<T>::insertar(const Iterador &iterador, const T &dato) {
    Nodo *nuevo = new Nodo(dato,iterador.nodo);
    if(iterador.nodo == cabecera){
        cabecera = nuevo;
    }else{
        if(cabecera != cola){
            Nodo *nodoActual = cabecera;
            while (nodoActual->siguiente != iterador.nodo){ // Como tenemos la precondición de que el dato del iterador debe existir en la lista, por lo que no será necesaria la condición de que el bucle pare si se acaba la lista.
                nodoActual = nodoActual->siguiente;
                if(nodoActual->siguiente == iterador.nodo){
                    nodoActual->siguiente = nuevo;
                }
            }
        }
        if(cabecera == nullptr){
            cabecera = cola = nuevo;
        }
    }
    ++tam;
}

template<typename T>
void ListaEnlazada<T>::insertarDetras(const Iterador &iterador, const T &dato) {
    Nodo *nuevo = new Nodo(dato, iterador.nodo->siguiente);
    iterador.nodo->siguiente = nuevo; // Hacemos que el atributo siguiente de p apunte al nuevo dato.
    if(cola == iterador.nodo){
        cola = nuevo;
    }
    ++tam;
}


template<typename T>
T &ListaEnlazada<T>::inicio() const{
    return cabecera->dato;
}

template<typename T>
T &ListaEnlazada<T>::fin() const{
    return cola->dato;
}

template<typename T>
void ListaEnlazada<T>::borrarIncicio() {
    Nodo *borrado = cabecera;
    cabecera = cabecera->siguiente;
    delete borrado;
    if(cabecera == nullptr){
        cola = nullptr;
    }
    --tam;
}

template<typename T>
void ListaEnlazada<T>::borrarFinal() {
    Nodo *anterior = nullptr;
    if(cabecera != cola){
        anterior = cabecera;
        while(anterior->siguiente != cola){
            anterior = anterior->siguiente;
        }
    }
    delete cola;
    cola = anterior;

    if(anterior != nullptr){
        anterior->siguiente = nullptr;
    }else{
        cabecera = nullptr;
    }
    --tam;
}

template<typename T>
void ListaEnlazada<T>::borrar(const Iterador &iterador) {

    //CON NODO
    if (iterador.nodo == cabecera){
        Nodo *borrado = cabecera;
        cabecera = cabecera->siguiente;
        delete borrado;
        if(cabecera == nullptr){
            cola = nullptr;
        }
    } else{
        Nodo *nodoActual = cabecera;
        while (nodoActual->siguiente != iterador.nodo){ // Como tenemos la precondición de que el dato del iterador debe existir en la lista, por lo que no será necesaria la condición de que el bucle pare si se acaba la lista.
            nodoActual = nodoActual->siguiente;
        }
        nodoActual->siguiente = iterador.nodo->siguiente;
        delete iterador.nodo;
    }
    --tam;
}

template<typename T>
long int ListaEnlazada<T>::getTam() const {
    return tam;
}

//TODO esto est'a bien devolviendo una copia? Xq si devolvemos una referencia de un ojeto que ha sido creado aqui estaria mal ya qu el objeto desaparece al acabar la funcion
template<typename T>
ListaEnlazada<T> ListaEnlazada<T>::concatena(const ListaEnlazada<T> &original) {

    ListaEnlazada<T> nueva;
    Nodo *nodoActual = cabecera;
    Nodo *nodoActualOriginal = original.cabecera;
    while (nodoActual){
        nueva.insertarFinal(nodoActual->dato);
        nodoActual = nodoActual->siguiente;
    }
    while (nodoActualOriginal){
        nueva.insertarFinal(nodoActualOriginal->dato);
        nodoActualOriginal = nodoActualOriginal->siguiente;
    }

    return nueva;
}

template<typename T>
ListaEnlazada<T> ListaEnlazada<T>::operator+(const ListaEnlazada<T> &original) {
    this->concatena(original);
}


#endif //PRACTICA_1B_LISTAENLAZA_H
