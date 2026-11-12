#ifndef NODOSOLICITUD_HPP
#define NODOSOLICITUD_HPP
#include "Solicitud.hpp"

class NodoSolicitud{

    private:
        Solicitud* dato;
        NodoSolicitud* siguiente;

    public:
        NodoSolicitud(Solicitud* s);
        ~NodoSolicitud();

        Solicitud* getSolicitud();
        NodoSolicitud* getSiguiente();
        void setSiguiente(NodoSolicitud* n);
        

};
#endif;
