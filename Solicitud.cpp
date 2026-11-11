#include "Solicitud.hpp"
#include <iostream>

Solicitud:: Solicitud(std::string numP,std::string nom, bool tipo, int numS ){
    this->numPlaca= numP;
    this->nombrePropietario=nom;
    this->tipoVehiculo=tipo;
    this->numSolicitud=numS;
}
Solicitud:: ~Solicitud(){}

std:: string Solicitud:: getNumeroPlaca(){ return this->numPlaca; }
std:: string Solicitud:: getNombrePropietario(){ return this->nombrePropietario; }
bool Solicitud:: getTipoVehiculo(){ return this->tipoVehiculo; }
int Solicitud:: getNumeroSolicitud(){ return this->numSolicitud; }