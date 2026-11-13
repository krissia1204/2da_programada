#ifndef NODOSOLICITUD_HPP
#define NODOSOLICITUD_HPP

#include "Solicitud.hpp"

class NodoSolicitud {
    private:
        Solicitud* dato;
        NodoSolicitud* siguiente;

    public:
        NodoSolicitud(Solicitud* s);
        ~NodoSolicitud();

        Solicitud* getSolicitud() const;
        NodoSolicitud* getSiguiente() const;
        void setSiguiente(NodoSolicitud* n);
};

#endif