#include "NodoSolicitud.hpp"

NodoSolicitud::NodoSolicitud(Solicitud* s) {
    this->dato = s;
    this->siguiente = nullptr;
}

NodoSolicitud::~NodoSolicitud() {}

Solicitud* NodoSolicitud::getSolicitud() const { return this->dato; }
NodoSolicitud* NodoSolicitud::getSiguiente() const { return this->siguiente; }
void NodoSolicitud::setSiguiente(NodoSolicitud* n) { this->siguiente = n; }