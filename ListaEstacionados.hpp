#ifndef LISTAESTACIONADOS_HPP
#define LISTAESTACIONADOS_HPP

#include "NodoEstacionado.hpp"
#include <string>

class ListaEstacionados {
    private:
        NodoEstacionado* cabeza;
        NodoEstacionado* cola;

    public:
        class Iterador {
            private:
                NodoEstacionado* actual;
            public:
                Iterador(NodoEstacionado* nodo);
                Estacionado& operator*() const;
                Iterador& operator++();
                Iterador& operator--();
                bool operator!=(const Iterador& otro) const;
        };

        ListaEstacionados();
        ~ListaEstacionados();

        ListaEstacionados(const ListaEstacionados&) = delete;
        ListaEstacionados& operator=(const ListaEstacionados&) = delete;

        Iterador begin() const;
        Iterador end() const;
        Iterador rbegin() const;
        Iterador rend() const;

        bool vacio() const;
        void agregarVehiculo(Estacionado* e);
        void recorrerPrimero() const;
        void recorrerUltimo() const;
        Estacionado* buscar(std::string p) const;
        bool existePlaca(std::string p) const;
        Estacionado* eliminar(std::string p);
        int totalEstacionados() const;
        int contarAutomoviles() const;
        int contarMotocicletas() const;
};

#endif