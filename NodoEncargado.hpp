#ifndef NODOENCARGADO_HPP
#define NODOENCARGADO_HPP

#include "Encargado.hpp"

class NodoEncargado {
    private:
        Encargado* dato;
        NodoEncargado* siguiente;

    public:
        NodoEncargado(Encargado* e);
        ~NodoEncargado();

        Encargado* getEncargado() const;
        NodoEncargado* getSiguiente() const;
        void setSiguiente(NodoEncargado* e);
};

#endif