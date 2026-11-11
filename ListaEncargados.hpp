#ifndef LISTAENCARGADOS_HPP
#define  LISTAENCARGADOS_HPP
#include "NodoEncargado.hpp"

class ListaSolicitud{
    private:
        NodoSolicitud cabeza;
    public:
        ListaEncargados();
        ~ListaEncargados();
        void registrarEncargado();
        void mostrarEncargados();
        Encargado consultarEncargado(std:: string p);
        Encargado eliminarEncargado(std:: string p);
        Encargado asignarEncargado();

};

#endif