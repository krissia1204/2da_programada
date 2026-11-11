#ifndef LISTASOLICITUD.HPP
#define LISTASOLICITUD.HPP
#include "NodoSolicitud.hpp"

class ListaSolicitud{
    private:
        NodoSolicitud cabeza;
    public:
        ListaSolicitud();
        ~ListaSolicitud();
        void registrarNueva();
        void mostrarPendientes();
        Solicitud consultarSolicitud(std:: string p);
        Solicitud cancelarSolicitud(std:: string p);
        void procesarPrimera();
        void consultarPendientes();


};

#endif