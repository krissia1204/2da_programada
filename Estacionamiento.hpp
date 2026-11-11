#ifndef ESTACIONAMIENTO_HPP
#define ESTACIONAMIENTO_HPP

class Estacionamiento{
    private:
        int columnas;
        int filas;
        int** espacios;
    public:
        Estacionamiento(int f, int c);
        ~Estacionamiento();
        void ingresarVehiculo();
        void liberarEspacio(int f, int c);
        void mostrarEstado();
        int calcDisponibles();
        int calcOcupados();
        double porcentajeOcupacion();
};
#endif