#include "NodoEncargado.hpp"

NodoEncargado::NodoEncargado(Encargado* e) {
    this->dato = e;
    this->siguiente = nullptr;
}

NodoEncargado::~NodoEncargado() {
    delete this->dato;
}

Encargado* NodoEncargado::getEncargado() const { return this->dato; }
NodoEncargado* NodoEncargado::getSiguiente() const { return this->siguiente; }
void NodoEncargado::setSiguiente(NodoEncargado* s) { this->siguiente = s; }
