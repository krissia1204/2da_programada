#ifndef SOLICITUD_HPP
#define SOLICITUD_HPP
#include <string>

class Solicitud{
    protected:
        std::string numPlaca;
        std::string nombrePropietario;
        bool tipoVehiculo;
        int numSolicitud;

    public:
        Solicitud(std::string numP, std::string nom, bool tipo, int numS);
        virtual ~Solicitud();
        std::string getNumeroPlaca();
        std::string getNombrePropietario();
        bool getTipoVehiculo();
        int getNumeroSolicitud();
        void mostrarDatos();


};

#endif