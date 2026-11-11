#include "ListaSolicitud.hpp"
#include <iostream>

ListaSolicitud:: ListaSolicitud(){
    this->cabeza= nullptr;
}

ListaSolicitud:: ~ListaSolicitud(){

}

void  ListaSolicitud:: registrarNueva(Solicitud s){
    NodoSolicitud* nuevo = new NodoSolicitud(s);

        if (cabeza == nullptr) {
            cabeza = nuevo;
            return;
        }

        NodoSolicitud* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
}

void ListaSolicitud:: mostrarPendientes(){
    NodoSolicitud* actual = cabeza;
        while (actual != nullptr) {
            actual->getSolicitud()->mostrarDatos();
            actual = actual->siguiente;
        }
        
}

Solicitud ListaSolicitud:: consultarSolicitud(std:: string p){
    NodoSolicitud* actual = cabeza;
        while (actual->getSolicitud().getNumeroPlaca() != p) {
            actual = actual->siguiente;
        }

        return actual;
        
}

Solicitud ListaSolicitud:: cancelarSolicitud(std:: string p){
      NodoSolicitud* actual = cabeza;
        while (actual->getSiguiente->getSolicitud()->getNumeroPlaca() != p) {
            actual = actual->siguiente;
        }
        actual->setSiguiente(actual->getSiguiente()->getSiguiente());


        return actual;
}


Solicitud ListaSolicitud:: procesarPrimera(){
    if(cabeza==null){
        throw underflow_error("Lista vacia")
        return null;
    }

    NodoSolicitud* procesar= cabeza;
    Solicitud p= procesar->getSolicitud();

    cabeza= cabeza->getSiguiente();

    delete procesar;

    return p;
}

