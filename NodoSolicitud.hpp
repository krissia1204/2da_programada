#ifndef NODOSOLICITUD.HPP
#define NODOSOLICITUD.HPP
#include "Solicitud.hpp"

class NodoSolicitud{

    private:
        Solicitud dato;
        NodoSolicitud siguiente;

    public:
        NodoSolicitud(Solicitud s);
        ~NodoSolicitud();

        Solicitud getSolicitud();
        NodoSolicitud getSiguiente();
        

};
#endif;
