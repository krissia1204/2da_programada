#ifndef LISTASOLICITUD_HPP
#define LISTASOLICITUD_HPP
#include "NodoSolicitud.hpp"

class ListaSolicitud{
    private:
        NodoSolicitud* cabeza;
    public:
        ListaSolicitud();
        ~ListaSolicitud();
        void registrarNueva(Solicitud* s);
        void mostrarPendientes();
        Solicitud* consultarSolicitud(std:: string p);
        Solicitud* cancelarSolicitud(std:: string p);
        Solicitud* procesarPrimera();
        void consultarPendientes();


};

#endif