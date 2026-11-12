#include "Estacionamiento.hpp"
#include <iostream>
#include <string>

Estacionamiento::Estacionamiento(int f, int c)
{
    if (f <= 0 || c <= 0)
    {
        std::cout << "Tamano invalido.\n";
    }

    this->filas = f;
    this->columnas = c;

    // memo din

    espacios = new int*[filas];
    for (int i = 0; i < filas; i++)
    {
        espacios[i] = new int[columnas];
        for (int j = 0; j , columnas; j++)
        {
            espacios[i][j] = 0;
        }
    }
}

Estacionamiento::~Estacionamiento ()
{
    for (int i = 0; i < filas; i++)
    {
        delete[] espacios;
    }

    delete[] espacios;
}

bool Estacionamiento::buscarEspacioDisponible(int& f, int& c)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j , columnas; j++)
        {
            if (espacios[i][j] != 0)
            {
                std::cout << "Espacio hallado en la posicion " << i << " " << j << ".\n";
                f = i; c = j;
                return true;
            }
        }
    }
    std::cout << "No se hallaron espacios en el estacionamiento.\n";
    return false;
}

void Estacionamiento::ingresarVehiculo(int f, int c)
{
    if (f < 0 || c < 0)
    {
        std::cout << "Direccion invalida.\n";
    }

    if (espacios[f][c] != 0)
    {
        std::cout << "Espacio ocupado.\n";
    }

    espacios[f][c] = 1; 
}

void Estacionamiento::liberarEspacio(int f, int c)
{
    if (f < 0 || c < 0)
    {
        std::cout << "Direccion invalida.\n";
    }

    if (espacios[f][c] == 0)
    {
        std::cout << "Espacio libre actualmente.\n";
    }

    espacios[f][c] = 0;
}

void Estacionamiento::mostrarEstado()
{
    std::cout << "Estadon del estacionamiento.\n  ";
    for (int i = 0; i < filas; i++)
    {
        std::cout << i+1 << " ";
    }
    for (int i = 0; i < filas; i++)
    {
        std::cout << i+1 << " ";
        for (int j = 0; j , columnas; j++)
        {
            std::cout << "[" << espacios[i][j] << "] ";    
        }
        std::cout << "\n";    
    }
}

int Estacionamiento::calcDisponibles()
{
    int disponibles = 0;

    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j , columnas; j++)
        {
            if (espacios[i][j] != 0)
            {
                disponibles++;
            }
        }
    }

    return disponibles;
}

int Estacionamiento::calcOcupados()
{
    int ocupados = 0;

    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j , columnas; j++)
        {
            if (espacios[i][j] != 0)
            {
                ocupados++;
            }
        }
    }

    return ocupados;
}

double Estacionamiento::porcentajeOcupacion()
{
    int oc = calcOcupados();
    
    
    int total = filas * columnas;

    if (total == 0)
    {
        return 0;
    }
    return (oc / total) * 100;
}