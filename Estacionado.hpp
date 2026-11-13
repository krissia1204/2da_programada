#ifndef ESTACIONADO_HPP
#define ESTACIONADO_HPP

#include <string>
#include "Solicitud.hpp"

class Estacionado : public Solicitud {
    private:
        int fila;
        int columna;
        std::string idAutorizacion;

    public:
        Estacionado(std::string numP, std::string nom, bool tipo, int numS, std::string id, int f = -1, int c = -1);
        ~Estacionado();

        int getFila() const;
        int getColumna() const;
        std::string getID() const;

        void setFila(int f);
        void setColumna(int c);

        void mostrarDatos() const override;
};

#endif