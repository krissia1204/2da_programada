#include "Estacionamiento.hpp"
#include <iostream>
#include <iomanip>
#include <stdexcept>

Estacionamiento::Estacionamiento(int f, int c) {
    if (f <= 0 || c <= 0) {
        throw std::invalid_argument("Las dimensiones del estacionamiento deben ser mayores que cero.");
    }

    this->filas = f;
    this->columnas = c;

    this->espacios = new int*[this->filas];
    for (int i = 0; i < this->filas; i++) {
        this->espacios[i] = new int[this->columnas];
        for (int j = 0; j < this->columnas; j++) {
            this->espacios[i][j] = 0;
        }
    }
}

Estacionamiento::~Estacionamiento() {
    for (int i = 0; i < this->filas; i++) {
        delete[] this->espacios[i];
    }
    delete[] this->espacios;
}

bool Estacionamiento::buscarEspacioDisponible(int& f, int& c) const {
    for (int i = 0; i < this->filas; i++) {
        for (int j = 0; j < this->columnas; j++) {
            if (this->espacios[i][j] == 0) {
                f = i;
                c = j;
                return true;
            }
        }
    }
    return false;
}

void Estacionamiento::ingresarVehiculo(int f, int c) {
    if (f < 0 || f >= this->filas || c < 0 || c >= this->columnas) {
        throw std::out_of_range("Posicion fuera de rango en el estacionamiento.");
    }
    if (this->espacios[f][c] != 0) {
        throw std::logic_error("El espacio seleccionado ya esta ocupado.");
    }
    this->espacios[f][c] = 1;
}

void Estacionamiento::liberarEspacio(int f, int c) {
    if (f < 0 || f >= this->filas || c < 0 || c >= this->columnas) {
        throw std::out_of_range("Posicion fuera de rango en el estacionamiento.");
    }
    if (this->espacios[f][c] == 0) {
        throw std::logic_error("El espacio seleccionado ya se encuentra libre.");
    }
    this->espacios[f][c] = 0;
}

void Estacionamiento::mostrarEstado() const {
    std::cout << "\nESTADO DEL ESTACIONAMIENTO\n   ";
    for (int j = 0; j < this->columnas; j++) {
        std::cout << "C" << j + 1 << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < this->filas; i++) {
        std::cout << "F" << i + 1 << " ";
        for (int j = 0; j < this->columnas; j++) {
            std::cout << " " << (this->espacios[i][j] == 1 ? 'O' : 'L') << " ";
        }
        std::cout << "\n";
    }
    std::cout << "O = Ocupado | L = Libre\n";
    std::cout << "Espacios ocupados: " << this->calcOcupados() << "\n";
    std::cout << "Espacios libres: " << this->calcDisponibles() << "\n";
    std::cout << std::fixed << std::setprecision(2)
              << "Porcentaje de ocupacion: " << this->porcentajeOcupacion() << "%\n";
}

int Estacionamiento::calcDisponibles() const {
    int disponibles = 0;
    for (int i = 0; i < this->filas; i++) {
        for (int j = 0; j < this->columnas; j++) {
            if (this->espacios[i][j] == 0) {
                disponibles++;
            }
        }
    }
    return disponibles;
}

int Estacionamiento::calcOcupados() const {
    int ocupados = 0;
    for (int i = 0; i < this->filas; i++) {
        for (int j = 0; j < this->columnas; j++) {
            if (this->espacios[i][j] == 1) {
                ocupados++;
            }
        }
    }
    return ocupados;
}

double Estacionamiento::porcentajeOcupacion() const {
    int oc = this->calcOcupados();
    int total = this->filas * this->columnas;
    if (total == 0) {
        return 0.0;
    }
    return (static_cast<double>(oc) / total) * 100.0;
}