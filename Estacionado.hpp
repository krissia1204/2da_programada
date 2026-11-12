#ifndef ESTACIONADO_HPP
#define ESTACIONADO_HPP
#include <string>
#include "Solicitud.hpp"
class Estacionado: public Solicitud {
    private:
       int fila;
       int columna;
       std:: string idAutorizacion;

    public:
        Estacionado();
        ~Estacionado();
        int getFila();
        int getColumna();
        std:: string getID();
};
#endif