#include "Estacionado.hpp"
#include <iostream>

Estacionado::Estacionado(std::string numP, std::string nom, bool tipo, int numS, std::string id, int f, int c)
    : Solicitud(numP, nom, tipo, numS) {
    this->idAutorizacion = id;
    this->fila = f;
    this->columna = c;
}

Estacionado::~Estacionado() {}

int Estacionado::getFila() const { return this->fila; }
int Estacionado::getColumna() const { return this->columna; }
std::string Estacionado::getID() const { return this->idAutorizacion; }

void Estacionado::setFila(int f) { this->fila = f; }
void Estacionado::setColumna(int c) { this->columna = c; }

void Estacionado::mostrarDatos() const {
    std::cout << "Placa: " << this->numPlaca
              << " | Propietario: " << this->nombrePropietario
              << " | Tipo: " << (this->tipoVehiculo ? "Automovil" : "Motocicleta")
              << " | Espacio: (" << this->fila + 1 << "," << this->columna + 1 << ")"
              << " | Encargado: " << this->idAutorizacion << std::endl;
}