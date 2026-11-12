#include "Encargado.hpp"
#include <iostream>
#include <string>

Encargado::Encargado(std::string id,  std::string nom)
{
    this->id = id;
    this->nombre = nom;
    cantAtendidos = 0;
}

std::string Encargado::getID ()
{
    return id;
}

std::string Encargado::getNombre ()
{
    return nombre;
}

int Encargado::getCantAtendidos ()
{
    return cantAtendidos;
}