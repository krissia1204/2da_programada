#ifndef ENCARGADO_HPP
#define ENCARGADO_HPP
#include <string>
class Encargado{
    private:
        std:: string id;
        std:: string nombre;
        int cantAtendidos;

    public:
        Encargado(std::string id, std:: string n);
        std::string getID();
        std::string getNombre();
        int getCantAtendidos();
};
#endif