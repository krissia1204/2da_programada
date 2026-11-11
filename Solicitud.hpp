#ifndef SOLICITUD.HPP
#define SOLICITUD.HPP
#include <string>

class Solicitud{
    private:
        std::string numPlaca;
        std::string nombrePropietario;
        bool tipoVehiculo;
        int numSolicitud;

    public:
        Solicitud(std::string numP, std::string nom, bool tipo, int numS);
        ~Solicitud();
        std::string getNumeroPlaca();
        std::string getNombrePropietario();
        bool getTipoVehiculo();
        int getNumeroSolicitud();
        void mostrarDatos();


};

#endif