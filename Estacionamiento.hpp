#ifndef ESTACIONAMIENTO_HPP
#define ESTACIONAMIENTO_HPP

class Estacionamiento
{
    private:
        int columnas;
        int filas;
        int** espacios;

        
    public: // los separe por lo q hacen
        Estacionamiento(int f, int c);
        ~Estacionamiento();

        bool buscarEspacioDisponible(int& f, int& c);
        void ingresarVehiculo(int f, int c);
        void liberarEspacio(int f, int c);

        void mostrarEstado();
        int calcDisponibles();
        int calcOcupados();
        double porcentajeOcupacion();
}
;

#endif