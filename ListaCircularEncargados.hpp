#ifndef LISTACIRCULARENCARGADOS_HPP
#define LISTACIRCULARENCARGADOS_HPP

#include "NodoEncargado.hpp"
#include <string>

class ListaCircularEncargados {
    private:
        NodoEncargado* cabeza;
        NodoEncargado* turnoActual;
        int cant;

    public:
        class Iterador {
            private:
                NodoEncargado* actual;
                int restantes;
            public:
                Iterador(NodoEncargado* nodo, int total);
                Encargado& operator*() const;
                Iterador& operator++();
                bool operator!=(const Iterador& otro) const;
        };

        ListaCircularEncargados();
        ~ListaCircularEncargados();

        ListaCircularEncargados(const ListaCircularEncargados&) = delete;
        ListaCircularEncargados& operator=(const ListaCircularEncargados&) = delete;

        Iterador begin() const;
        Iterador end() const;

        void registrarEncargado(Encargado* e);
        void eliminarEncargado(std::string id);

        Encargado* consultarSiguiente() const;
        Encargado* asignarEncargado();
        void avanzarTurno();

        bool existeID(std::string id) const;
        void mostrarEncargados() const;
        void mostrarOrdenRotacion() const;
        bool estaVacia() const;
        int getCantidad() const;
};

#endif