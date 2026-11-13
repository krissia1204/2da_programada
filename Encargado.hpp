#ifndef ENCARGADO_HPP
#define ENCARGADO_HPP

#include <string>

class Encargado {
    private:
        std::string id;
        std::string nombre;
        int cantAtendidos;

    public:
        Encargado(std::string id, std::string n);
        std::string getID() const;
        std::string getNombre() const;
        int getCantAtendidos() const;
        void incrementarAtendidos();
};

#endif