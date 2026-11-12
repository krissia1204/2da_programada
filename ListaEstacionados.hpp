#ifndef LISTAESTACIONADOS_HPP
#define LISTAESTACIONADOS_HPP
#include <iostream>
#include "NodoEstacionado.hpp"
class ListaEstacionados{
    private:
        NodoEstacionado* cabeza;
        NodoEstacionado* cola;
    public:
        ListaEstacionados();
        ~ListaEstacionados();
        bool vacio();
        void agregarVehiculo( Estacionado* e);
        void recorrerPrimero();
        void recorrerUltimo();
        Estacionado* buscar(std:: string p);
        Estacionado* eliminar(std:: string p);
        int totalEstacionados();

};
#endif