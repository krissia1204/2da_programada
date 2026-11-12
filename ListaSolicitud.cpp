#include "ListaSolicitud.hpp"
#include <iostream>
#include <stdexcept>

ListaSolicitud:: ListaSolicitud(){
    this->cabeza = nullptr;
}

ListaSolicitud:: ~ListaSolicitud(){

}

void  ListaSolicitud:: registrarNueva(Solicitud* s){
    NodoSolicitud* nuevo = new NodoSolicitud(s);

        if (cabeza == nullptr) {
            cabeza = nuevo;
            return;
        }

        NodoSolicitud* actual = cabeza;
        while (actual->getSiguiente() != nullptr) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(nuevo);
}

void ListaSolicitud:: mostrarPendientes(){
    NodoSolicitud* actual = cabeza;
        while (actual != nullptr) {
            actual->getSolicitud()->mostrarDatos();
            actual = actual->getSiguiente();
        }
        
}

Solicitud* ListaSolicitud:: consultarSolicitud(std:: string p){
    NodoSolicitud* actual = cabeza;
        while (actual->getSolicitud()->getNumeroPlaca() != p) {
            actual = actual->getSiguiente();
        }

        return actual->getSolicitud();
        
}

Solicitud* ListaSolicitud:: cancelarSolicitud(std:: string p){
      NodoSolicitud* actual = cabeza;
        while (actual->getSiguiente()->getSolicitud()->getNumeroPlaca() != p) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(actual->getSiguiente()->getSiguiente());


        return actual->getSolicitud();
}


Solicitud* ListaSolicitud:: procesarPrimera(){
    if(cabeza==nullptr){
        throw std::underflow_error("Lista vacia");
    
    }

    NodoSolicitud* procesar= cabeza;
    Solicitud* p= procesar->getSolicitud();

    cabeza= cabeza->getSiguiente();

    delete procesar;

    return p;
}

