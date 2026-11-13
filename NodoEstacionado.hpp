#ifndef NODOESTACIONADO_HPP
#define NODOESTACIONADO_HPP

#include "Estacionado.hpp"

class NodoEstacionado {
    private:
        Estacionado* dato;
        NodoEstacionado* siguiente;
        NodoEstacionado* anterior;

    public:
        NodoEstacionado(Estacionado* s);
        ~NodoEstacionado();

        Estacionado* getEstacionado() const;
        NodoEstacionado* getSiguiente() const;
        NodoEstacionado* getAnterior() const;
        void setSiguiente(NodoEstacionado* s);
        void setAnterior(NodoEstacionado* s);
};

#endif