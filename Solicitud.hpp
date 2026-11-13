#ifndef SOLICITUD_HPP
#define SOLICITUD_HPP

#include <string>

class Solicitud {
    protected:
        std::string numPlaca;
        std::string nombrePropietario;
        bool tipoVehiculo; // true: Automovil, false: Motocicleta
        int numSolicitud;

    public:
        Solicitud(std::string numP, std::string nom, bool tipo, int numS);
        virtual ~Solicitud();

        std::string getNumeroPlaca() const;
        std::string getNombrePropietario() const;
        bool getTipoVehiculo() const;
        int getNumeroSolicitud() const;
        virtual void mostrarDatos() const;
};

#endif