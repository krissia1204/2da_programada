#include <NodoEncargado.hpp>

NodoEncargado::NodoEncargado(Encargado* e)
{
    this->dato = e;
    this->siguiente = nullptr;
}

NodoEncargado::~NodoEncargado()
{
    delete dato;
}

Encargado* NodoEncargado::getEncargado()
{
    return dato;
}

NodoEncargado* NodoEncargado::getSiguiente()
{
    return siguiente;
}

void NodoEncargado::setSiguiente(NodoEncargado* s)
{
    siguiente = s;
}
