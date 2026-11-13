#include "Encargado.hpp"
#include <stdexcept>

Encargado::Encargado(std::string id, std::string nom) {
    if (id.empty() || nom.empty()) {
        throw std::invalid_argument("El ID y el nombre del encargado no pueden estar vacios.");
    }
    this->id = id;
    this->nombre = nom;
    this->cantAtendidos = 0;
}

std::string Encargado::getID() const { return this->id; }
std::string Encargado::getNombre() const { return this->nombre; }
int Encargado::getCantAtendidos() const { return this->cantAtendidos; }
void Encargado::incrementarAtendidos() { this->cantAtendidos++; }