#ifndef ESTACIONAMIENTO_HPP
#define ESTACIONAMIENTO_HPP

class Estacionamiento {
    private:
        int filas;
        int columnas;
        int** espacios;

    public:
        Estacionamiento(int f, int c);
        ~Estacionamiento();

        Estacionamiento(const Estacionamiento&) = delete;
        Estacionamiento& operator=(const Estacionamiento&) = delete;

        bool buscarEspacioDisponible(int& f, int& c) const;
        void ingresarVehiculo(int f, int c);
        void liberarEspacio(int f, int c);

        void mostrarEstado() const;
        int calcDisponibles() const;
        int calcOcupados() const;
        double porcentajeOcupacion() const;
};

#endif