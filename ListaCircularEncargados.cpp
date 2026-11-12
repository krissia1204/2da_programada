#include "ListaCircularEncargados.hpp"
#include <iostream>
#include <stdexcept>


ListaCircularEncargados::ListaCircularEncargados()
{
    this->cabeza = nullptr;
    this->turnoActual = nullptr;
    this->cant = 0;
}

ListaCircularEncargados::~ListaCircularEncargados()
{
    if (cabeza != nullptr)
    {
        NodoEncargado* actual = cabeza;
        NodoEncargado* siguiente = nullptr;

        NodoEncargado* ultimo = cabeza;
        while (ultimo->getSiguiente() != cabeza)
        {
            ultimo = ultimo->getSiguiente();
        }
        ultimo->setSiguiente(nullptr);

        while (actual != nullptr)
        {
            siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        }
    }
}

bool ListaCircularEncargados::estaVacia() 
{
    return cabeza == nullptr;
}

void ListaCircularEncargados::registrarEncargado(Encargado* e) 
{
    NodoEncargado* nuevo = new NodoEncargado(e);
    if (estaVacia()) {
        cabeza = nuevo;
        nuevo->setSiguiente(cabeza);
        turnoActual = cabeza;
    } else {
        NodoEncargado* actual = cabeza;
        while (actual->getSiguiente() != cabeza) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(nuevo);
        nuevo->setSiguiente(cabeza);
    }
    cant++;
}

void ListaCircularEncargados::eliminarEncargado(std::string id) 
{
    if (estaVacia()) 
    {
        std::cout << ("No hay encargados registrados para eliminar.\n");
    }

    NodoEncargado* actual = cabeza;
    NodoEncargado* anterior = nullptr;
    bool encontrado = false;

    do {
        if (actual->getEncargado()->getID() == id) 
        {
            encontrado = true;
            break;
        }
        anterior = actual;
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    if (!encontrado) 
    {
        std::cout << ("El encargado no existe.\n");
    }

    if (cant == 1) 
    {
        delete actual;
        cabeza = nullptr;
        turnoActual = nullptr;
    } 

    else if (actual == cabeza) 
    {
        NodoEncargado* ultimo = cabeza;
        while (ultimo->getSiguiente() != cabeza) 
        {
            ultimo = ultimo->getSiguiente();
        }
        cabeza = cabeza->getSiguiente();
        ultimo->setSiguiente(cabeza);
        if (turnoActual == actual) 
        {
            turnoActual = cabeza;
        }
        delete actual;
    } 

    else 
    {
        anterior->setSiguiente(actual->getSiguiente());
        if (turnoActual == actual) 
        {
            turnoActual = actual->getSiguiente();
        }
        delete actual;
    }
    cant--;
}

Encargado* ListaCircularEncargados::consultarSiguiente() 
{
    if (estaVacia()) 
    {
        std::cout << ("No hay encargados disponibles.");
    }
    return turnoActual->getEncargado();
}

void ListaCircularEncargados::avanzarTurno() 
{
    if (!estaVacia()) 
    {
        turnoActual = turnoActual->getSiguiente();
    }
}

Encargado* ListaCircularEncargados::asignarEncargado() 
{
    if (estaVacia()) 
    {
        std::cout << ("No hay encargados disponibles.\n");
    }
    Encargado* asignado = turnoActual->getEncargado();
    avanzarTurno();
    return asignado;
}

void ListaCircularEncargados::mostrarEncargados() 
{
    if (estaVacia()) 
    {
        std::cout << "No hay encargados registrados.\n";
        return;
    }

    NodoEncargado* actual = cabeza;

    do 
    {
        std::cout << "ID: " << actual->getEncargado()->getID();
        std::cout << " Nombre: " << actual->getEncargado()->getNombre(); 
        std::cout << " | Atendidos: " << actual->getEncargado()->getCantAtendidos(); 
        std::cout << "\n";
        actual = actual->getSiguiente();
    } while (actual != cabeza);
}