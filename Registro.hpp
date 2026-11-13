#ifndef REGISTRO_HPP
#define REGISTRO_HPP

#include "ListaSolicitud.hpp"
#include "ListaEstacionados.hpp"
#include "ListaCircularEncargados.hpp"
#include "Estacionamiento.hpp"
#include <string>

class Registro {
    private:
        ListaSolicitud* solicitudes;
        ListaEstacionados* estacionados;
        ListaCircularEncargados* encargados;
        Estacionamiento* estacionamiento;
        int contadorSolicitudes;
        double totalRecaudado;

    public:
        Registro(int filas, int columnas);
        ~Registro();

        Registro(const Registro&) = delete;
        Registro& operator=(const Registro&) = delete;

        // 3.1 Gestion de solicitudes
        void registrarSolicitud(std::string placa, std::string propietario, bool tipoVehiculo);
        void mostrarSolicitudesPendientes() const;
        void consultarSolicitudPorPlaca(std::string placa) const;
        void cancelarSolicitud(std::string placa);
        int getTotalPendientes() const;

        // 3.2 Control de vehiculos estacionados
        void mostrarEstacionadosDirecto() const;
        void mostrarEstacionadosInverso() const;
        void consultarVehiculoEstacionado(std::string placa) const;
        int getTotalEstacionados() const;

        // 3.3 Rotacion de encargados
        void registrarEncargado(std::string id, std::string nombre);
        void eliminarEncargado(std::string id);
        void consultarSiguienteEncargado() const;
        void mostrarEncargados() const;
        void mostrarOrdenRotacion() const;

        // 3.4 Matriz del estacionamiento
        void mostrarEstadoEstacionamiento() const;

        // 3.5 Ingreso y salida
        void procesarSiguienteSolicitud();
        void registrarSalida(std::string placa, int horas);

        // 3.6 Reportes
        void generarReporteGeneral() const;
        double getTotalRecaudado() const;
};

#endif