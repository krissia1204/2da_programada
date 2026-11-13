#include "NodoEstacionado.hpp"

NodoEstacionado::NodoEstacionado(Estacionado* s) {
    this->dato = s;
    this->anterior = nullptr;
    this->siguiente = nullptr;
}

NodoEstacionado::~NodoEstacionado() {}

Estacionado* NodoEstacionado::getEstacionado() const { return this->dato; }
NodoEstacionado* NodoEstacionado::getAnterior() const { return this->anterior; }
NodoEstacionado* NodoEstacionado::getSiguiente() const { return this->siguiente; }
void NodoEstacionado::setAnterior(NodoEstacionado* n) { this->anterior = n; }
void NodoEstacionado::setSiguiente(NodoEstacionado* n) { this->siguiente = n; }