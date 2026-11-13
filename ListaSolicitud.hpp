#ifndef LISTASOLICITUD_HPP
#define LISTASOLICITUD_HPP

#include "NodoSolicitud.hpp"
#include <string>

class ListaSolicitud {
    private:
        NodoSolicitud* cabeza;

    public:
        class Iterador {
            private:
                NodoSolicitud* actual;
            public:
                Iterador(NodoSolicitud* nodo);
                Solicitud& operator*() const;
                Iterador& operator++();
                bool operator!=(const Iterador& otro) const;
        };

        ListaSolicitud();
        ~ListaSolicitud();

       
        ListaSolicitud(const ListaSolicitud&) = delete;
        ListaSolicitud& operator=(const ListaSolicitud&) = delete;

        Iterador begin() const;
        Iterador end() const;

        void registrarNueva(Solicitud* s);
        void mostrarPendientes() const;
        Solicitud* consultarSolicitud(std::string p) const;
        Solicitud* cancelarSolicitud(std::string p);
        Solicitud* procesarPrimera();
        int consultarPendientes() const;
        bool existePlaca(std::string p) const;
};

#endif