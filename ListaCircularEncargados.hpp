#ifndef LISTACIRCULARENCARGADOS_HPP
#define LISTACIRCULARENCARGADOS_HPP
#include "NodoEncargado.hpp"
#include <string>

class ListaCircularEncargados
{
    private:
        NodoEncargado* cabeza;
        NodoEncargado* turnoActual;
        int cant;

    public:
        ListaCircularEncargados();
        ~ListaCircularEncargados();

        void registrarEncargado(Encargado* e);
        void eliminarEncargado(std::string id);

        Encargado* consultarSiguiente();
        Encargado* asignarEncargado();
        void avanzarTurno();

        void mostrarEncargados();
        bool estaVacia();
}
;

#endif