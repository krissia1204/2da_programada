#include "NodoSolicitud.hpp"
#include <iostream>

NodoSolicitud:: NodoSolicitud(Solicitud s){
    this->dato=s;
    this->siguiente = nullptr;
}

NodoSolicitud:: ~NodoSolicitud(){

}

Solicitud NodoSolicitud:: getSolicitud(){ return this->dato; }
NodoSolicitud NodoSolicitud:: getSiguiente(){ return this->siguiente; }