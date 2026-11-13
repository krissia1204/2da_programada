#include "Solicitud.hpp"
#include <iostream>
#include <stdexcept>

Solicitud::Solicitud(std::string numP, std::string nom, bool tipo, int numS) {
    if (numP.empty()) {
        throw std::invalid_argument("La placa no puede estar vacia.");
    }
    if (nom.empty()) {
        throw std::invalid_argument("El nombre del propietario no puede estar vacio.");
    }
    this->numPlaca = numP;
    this->nombrePropietario = nom;
    this->tipoVehiculo = tipo;
    this->numSolicitud = numS;
}

Solicitud::~Solicitud() {}

std::string Solicitud::getNumeroPlaca() const { return this->numPlaca; }
std::string Solicitud::getNombrePropietario() const { return this->nombrePropietario; }
bool Solicitud::getTipoVehiculo() const { return this->tipoVehiculo; }
int Solicitud::getNumeroSolicitud() const { return this->numSolicitud; }

void Solicitud::mostrarDatos() const {
    std::cout << "S" << (this->numSolicitud < 100 ? (this->numSolicitud < 10 ? "00" : "0") : "")
              << this->numSolicitud << " | Placa: " << this->numPlaca
              << " | Propietario: " << this->nombrePropietario
              << " | Tipo: " << (this->tipoVehiculo ? "Automovil" : "Motocicleta") << std::endl;
}