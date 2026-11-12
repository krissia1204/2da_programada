#ifndef NODOENCARGADO_HPP
#define NODOENCARGADO_HPP
#include "Encargado.hpp"

class NodoEncargado{

    private:
        Encargado dato;
        NodoEncargado* siguiente;

    public: 
        NodoEncargado(Encargado e);
        ~NodoEncargado();

        Encargado getEncargado();
        NodoEncargado getSiguiente();
        void setSiguiente(NodoEncargado);
        

};
#endif;
