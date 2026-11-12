#include <iostream>
#include "Estacionado.hpp"

Estacionado:: Estacionado(std::string numP, std::string nom, bool tipo, int numS, std:: string id): Solicitud(numP, nom, tipo, numS){
    this->idAutorizacion=id;
    this->columna=-1;
    this->fila=-1;

}
Estacionado:: ~Estacionado(){

}

int Estacionado:: getFila(){
    return fila;
}

int Estacionado:: getColumna(){
    return columna;
}

std:: string Estacionado:: getID(){
    return idAutorizacion;
}

