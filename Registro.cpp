#include "Registro.hpp"
#include <iostream>
#include <iomanip>
#include <stdexcept>

Registro::Registro(int filas, int columnas) {
    this->estacionamiento = new Estacionamiento(filas, columnas);
    this->solicitudes = new ListaSolicitud();
    this->estacionados = new ListaEstacionados();
    this->encargados = new ListaCircularEncargados();
    this->contadorSolicitudes = 0;
    this->totalRecaudado = 0.0;
}

Registro::~Registro() {
    delete this->solicitudes;
    delete this->estacionados;
    delete this->encargados;
    delete this->estacionamiento;
}

// --- 3.1 Gestion de solicitudes ---
void Registro::registrarSolicitud(std::string placa, std::string propietario, bool tipoVehiculo) {
    if (placa.empty() || propietario.empty()) {
        throw std::invalid_argument("La placa y el propietario no pueden estar vacios.");
    }
    if (this->solicitudes->existePlaca(placa) || this->estacionados->existePlaca(placa)) {
        throw std::logic_error("La placa ya esta registrada.");
    }

    this->contadorSolicitudes++;
    Solicitud* nueva = nullptr;
    try {
        nueva = new Solicitud(placa, propietario, tipoVehiculo, this->contadorSolicitudes);
        this->solicitudes->registrarNueva(nueva);
    } catch (...) {
        this->contadorSolicitudes--;
        delete nueva;
        throw;
    }

    std::cout << "Solicitud S"
              << (this->contadorSolicitudes < 100 ? (this->contadorSolicitudes < 10 ? "00" : "0") : "")
              << this->contadorSolicitudes << " registrada correctamente.\n";
}

void Registro::mostrarSolicitudesPendientes() const {
    this->solicitudes->mostrarPendientes();
    std::cout << "Total de solicitudes pendientes: " << this->solicitudes->consultarPendientes() << "\n";
}

void Registro::consultarSolicitudPorPlaca(std::string placa) const {
    Solicitud* s = this->solicitudes->consultarSolicitud(placa);
    std::cout << "Resultado: ";
    s->mostrarDatos();
}

void Registro::cancelarSolicitud(std::string placa) {
    Solicitud* cancelada = this->solicitudes->cancelarSolicitud(placa);
    int num = cancelada->getNumeroSolicitud();
    delete cancelada;
    std::cout << "Solicitud S" << (num < 100 ? (num < 10 ? "00" : "0") : "")
              << num << " cancelada correctamente.\n";
}

int Registro::getTotalPendientes() const {
    return this->solicitudes->consultarPendientes();
}

// --- 3.2 Control de vehiculos estacionados ---
void Registro::mostrarEstacionadosDirecto() const {
    std::cout << "VEHICULOS ESTACIONADOS - ORDEN DIRECTO\n";
    this->estacionados->recorrerPrimero();
}

void Registro::mostrarEstacionadosInverso() const {
    std::cout << "VEHICULOS ESTACIONADOS - ORDEN INVERSO\n";
    this->estacionados->recorrerUltimo();
}

void Registro::consultarVehiculoEstacionado(std::string placa) const {
    Estacionado* e = this->estacionados->buscar(placa);
    e->mostrarDatos();
}

int Registro::getTotalEstacionados() const {
    return this->estacionados->totalEstacionados();
}

// --- 3.3 Rotacion de encargados ---
void Registro::registrarEncargado(std::string id, std::string nombre) {
    Encargado* nuevo = new Encargado(id, nombre);
    try {
        this->encargados->registrarEncargado(nuevo);
    } catch (...) {
        delete nuevo;
        throw;
    }
}

void Registro::eliminarEncargado(std::string id) {
    this->encargados->eliminarEncargado(id);
}

void Registro::consultarSiguienteEncargado() const {
    Encargado* sig = this->encargados->consultarSiguiente();
    std::cout << "Proximo encargado: " << sig->getNombre() << " (" << sig->getID() << ")\n";
}

void Registro::mostrarEncargados() const {
    this->encargados->mostrarEncargados();
}

void Registro::mostrarOrdenRotacion() const {
    this->encargados->mostrarOrdenRotacion();
}

// --- 3.4 Matriz del estacionamiento ---
void Registro::mostrarEstadoEstacionamiento() const {
    this->estacionamiento->mostrarEstado();
}

// --- 3.5 Ingreso y salida ---
void Registro::procesarSiguienteSolicitud() {
    // Validaciones previas antes de modificar ninguna estructura
    if (this->solicitudes->consultarPendientes() == 0) {
        throw std::underflow_error("No hay solicitudes pendientes.");
    }

    int filaLibre = -1;
    int colLibre = -1;
    if (!this->estacionamiento->buscarEspacioDisponible(filaLibre, colLibre)) {
        throw std::overflow_error("No hay espacios disponibles.");
    }

    if (this->encargados->estaVacia()) {
        throw std::logic_error("No existen encargados disponibles para autorizar el ingreso.");
    }

    // Ejecucion atomica una vez validado todo
    Solicitud* sol = this->solicitudes->procesarPrimera();
    Encargado* encargadoAsignado = this->encargados->asignarEncargado();

    Estacionado* nuevoEstacionado = new Estacionado(
        sol->getNumeroPlaca(),
        sol->getNombrePropietario(),
        sol->getTipoVehiculo(),
        sol->getNumeroSolicitud(),
        encargadoAsignado->getID(),
        filaLibre,
        colLibre
    );

    this->estacionamiento->ingresarVehiculo(filaLibre, colLibre);
    this->estacionados->agregarVehiculo(nuevoEstacionado);
    encargadoAsignado->incrementarAtendidos();

    int numSol = sol->getNumeroSolicitud();
    std::string placa = sol->getNumeroPlaca();
    delete sol;

    std::cout << "Solicitud: S" << (numSol < 100 ? (numSol < 10 ? "00" : "0") : "")
              << numSol << " - " << placa << "\n";
    std::cout << "Espacio asignado: Fila " << filaLibre + 1 << ", Columna " << colLibre + 1 << "\n";
    std::cout << "Encargado: " << encargadoAsignado->getNombre() << "\n";
    std::cout << "Ingreso registrado correctamente.\n";
    std::cout << "Siguiente encargado: " << this->encargados->consultarSiguiente()->getNombre() << "\n";
}

void Registro::registrarSalida(std::string placa, int horas) {
    if (horas <= 0) {
        throw std::invalid_argument("Las horas deben ser positivas.");
    }

    // Verificar existencia antes de eliminar
    Estacionado* vehiculo = this->estacionados->buscar(placa);

    double tarifa = vehiculo->getTipoVehiculo() ? 900.0 : 500.0;
    double monto = horas * tarifa;
    int f = vehiculo->getFila();
    int c = vehiculo->getColumna();
    std::string prop = vehiculo->getNombrePropietario();
    std::string tipoStr = vehiculo->getTipoVehiculo() ? "Automovil" : "Motocicleta";

    // Retirar de la lista doble, liberar matriz y sumar recaudacion
    Estacionado* retirado = this->estacionados->eliminar(placa);
    this->estacionamiento->liberarEspacio(f, c);
    this->totalRecaudado += monto;
    delete retirado;

    std::cout << "\n--- COMPROBANTE DE SALIDA ---\n";
    std::cout << "Placa: " << placa << "\n";
    std::cout << "Propietario: " << prop << "\n";
    std::cout << "Tipo: " << tipoStr << "\n";
    std::cout << "Horas de permanencia: " << horas << "\n";
    std::cout << "Tarifa por hora: " << std::fixed << std::setprecision(0) << tarifa << " colones\n";
    std::cout << "Monto a pagar: " << monto << " colones\n";
    std::cout << "Espacio (" << f + 1 << "," << c + 1 << ") liberado.\n";
    std::cout << "Vehiculo retirado del registro.\n";
}

// --- 3.6 Reportes ---
void Registro::generarReporteGeneral() const {
    std::cout << "\n=== REPORTE GENERAL DEL ESTACIONAMIENTO ===\n";
    std::cout << "Solicitudes pendientes: " << this->solicitudes->consultarPendientes() << "\n";
    std::cout << "Vehiculos estacionados: " << this->estacionados->totalEstacionados() << "\n";
    std::cout << "Automoviles estacionados: " << this->estacionados->contarAutomoviles() << "\n";
    std::cout << "Motocicletas estacionadas: " << this->estacionados->contarMotocicletas() << "\n";
    std::cout << "Espacios ocupados: " << this->estacionamiento->calcOcupados() << "\n";
    std::cout << "Espacios libres: " << this->estacionamiento->calcDisponibles() << "\n";
    std::cout << std::fixed << std::setprecision(2)
              << "Porcentaje de ocupacion: " << this->estacionamiento->porcentajeOcupacion() << "%\n";
    std::cout << std::fixed << std::setprecision(0)
              << "Total recaudado: " << this->totalRecaudado << " colones\n";
    std::cout << "\nVEHICULOS ATENDIDOS POR ENCARGADO:\n";
    this->encargados->mostrarEncargados();
}

double Registro::getTotalRecaudado() const {
    return this->totalRecaudado;
}