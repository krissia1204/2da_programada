#include "NodoEstacionado.hpp"

NodoEstacionado:: NodoEstacionado(Estacionado* s){
    this->dato= s;
    this->anterior= nullptr;
    this->siguiente= nullptr;
}

NodoEstacionado:: ~NodoEstacionado(){

}

Estacionado* NodoEstacionado:: getEstacionado(){ return dato;}
NodoEstacionado* NodoEstacionado:: getAnterior(){return anterior;}
NodoEstacionado* NodoEstacionado:: getSiguiente(){return siguiente;}
void NodoEstacionado:: setAnterior(NodoEstacionado* n){ anterior= n;}
void NodoEstacionado:: setSiguiente(NodoEstacionado* n){ siguiente= n;}
