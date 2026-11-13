#include <iostream>
#include <string>
#include <stdexcept>
#include "Registro.hpp"

void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

int leerEntero(const std::string& mensaje) {
    int valor;
    while (true) {
        std::cout << mensaje;
        if (std::cin >> valor) {
            limpiarBuffer();
            return valor;
        }
        std::cout << "Entrada invalida. Por favor ingrese un numero entero.\n";
        limpiarBuffer();
    }
}

void verificarPrueba(bool condicion, const std::string& descripcion) {
    if (!condicion) {
        throw std::runtime_error("Fallo la prueba: " + descripcion);
    }
}

void ejecutarPruebasAutomatizadas() {
    std::cout << "\nEjecutando bateria de 14 pruebas automatizadas...\n";

    // Pruebas 1, 2, 3 y 14: Lista simple e iteradores en lista vacia
    ListaSolicitud listaSol;
    int conteoVacio = 0;
    for (ListaSolicitud::Iterador it = listaSol.begin(); it != listaSol.end(); ++it) {
        conteoVacio++;
    }
    verificarPrueba(conteoVacio == 0, "Prueba 14: Iterador en lista vacia");

    listaSol.registrarNueva(new Solicitud("AAA111", "Carlos", true, 1));
    listaSol.registrarNueva(new Solicitud("BBB222", "Daniela", false, 2));
    listaSol.registrarNueva(new Solicitud("CCC333", "Pedro", true, 3));
    verificarPrueba(listaSol.consultarPendientes() == 3, "Prueba 1: Registrar solicitudes al final");

    Solicitud* canc1 = listaSol.cancelarSolicitud("AAA111");
    delete canc1;
    verificarPrueba(listaSol.consultarSolicitud("BBB222")->getNumeroSolicitud() == 2, "Prueba 2: Cancelar primera solicitud");

    listaSol.registrarNueva(new Solicitud("DDD444", "Sofia", true, 4));
    Solicitud* cancMid = listaSol.cancelarSolicitud("CCC333");
    delete cancMid;
    verificarPrueba(listaSol.consultarPendientes() == 2, "Prueba 3: Cancelar solicitud intermedia");

    // Pruebas 4 y 5: Lista doble e iteradores directo/inverso
    ListaEstacionados listaEst;
    listaEst.agregarVehiculo(new Estacionado("EST001", "Ana", true, 1, "E01", 0, 0));
    listaEst.agregarVehiculo(new Estacionado("EST002", "Luis", false, 2, "E02", 0, 1));
    listaEst.agregarVehiculo(new Estacionado("EST003", "Maria", true, 3, "E03", 1, 0));

    ListaEstacionados::Iterador itDir = listaEst.begin();
    verificarPrueba((*itDir).getNumeroPlaca() == "EST001", "Prueba 5a: Iterador directo inicio");
    ++itDir;
    verificarPrueba((*itDir).getNumeroPlaca() == "EST002", "Prueba 5b: Iterador directo avance");

    ListaEstacionados::Iterador itInv = listaEst.rbegin();
    verificarPrueba((*itInv).getNumeroPlaca() == "EST003", "Prueba 5c: Iterador inverso inicio");
    --itInv;
    verificarPrueba((*itInv).getNumeroPlaca() == "EST002", "Prueba 5d: Iterador inverso retroceso");

    Estacionado* elim = listaEst.eliminar("EST002");
    delete elim;
    verificarPrueba(listaEst.totalEstacionados() == 2, "Prueba 4: Eliminar nodo intermedio lista doble");

    // Pruebas 6 y 7: Lista circular de encargados
    ListaCircularEncargados listaEnc;
    listaEnc.registrarEncargado(new Encargado("E01", "Ana"));
    listaEnc.registrarEncargado(new Encargado("E02", "Luis"));
    listaEnc.registrarEncargado(new Encargado("E03", "Maria"));

    verificarPrueba(listaEnc.asignarEncargado()->getNombre() == "Ana", "Prueba 6a: Turno 1");
    verificarPrueba(listaEnc.asignarEncargado()->getNombre() == "Luis", "Prueba 6b: Turno 2");
    verificarPrueba(listaEnc.asignarEncargado()->getNombre() == "Maria", "Prueba 6c: Turno 3");
    verificarPrueba(listaEnc.asignarEncargado()->getNombre() == "Ana", "Prueba 6d: Rotacion circular al primero");

    listaEnc.eliminarEncargado("E02");
    verificarPrueba(listaEnc.getCantidad() == 2 && listaEnc.consultarSiguiente()->getNombre() == "Luis" == false, "Prueba 7: Eliminar encargado y mantener rotacion");

    // Pruebas 8, 9, 10, 11, 12 y 13: Integracion completa en Registro
    Registro reg(1, 2); // 2 espacios totales
    reg.registrarEncargado("E01", "Ana");
    reg.registrarEncargado("E02", "Luis");

    reg.registrarSolicitud("PLACA1", "Usuario 1", true);
    bool duplicadaCapturada = false;
    try {
        reg.registrarSolicitud("PLACA1", "Otro", false);
    } catch (const std::logic_error&) {
        duplicadaCapturada = true;
    }
    verificarPrueba(duplicadaCapturada, "Prueba 11: Rechazar placa duplicada");

    reg.registrarSolicitud("PLACA2", "Usuario 2", false);
    reg.registrarSolicitud("PLACA3", "Usuario 3", true);

    reg.procesarSiguienteSolicitud();
    reg.procesarSiguienteSolicitud();
    verificarPrueba(reg.getTotalEstacionados() == 2, "Prueba 8: Ocupacion al 100%");

    bool llenoCapturado = false;
    try {
        reg.procesarSiguienteSolicitud();
    } catch (const std::overflow_error&) {
        llenoCapturado = true;
    }
    verificarPrueba(llenoCapturado && reg.getTotalPendientes() == 1, "Prueba 9: Excepcion estacionamiento lleno sin perder solicitud");

    bool horasNegCapturadas = false;
    try {
        reg.registrarSalida("PLACA1", -3);
    } catch (const std::invalid_argument&) {
        horasNegCapturadas = true;
    }
    verificarPrueba(horasNegCapturadas, "Prueba 10: Rechazar horas negativas");

    reg.registrarSalida("PLACA1", 3);
    verificarPrueba(reg.getTotalEstacionados() == 1 && reg.getTotalRecaudado() == 2700.0, "Prueba 12: Retirar vehiculo y liberar espacio");

    reg.procesarSiguienteSolicitud(); // Entra PLACA3
    bool vaciaCapturada = false;
    try {
        reg.procesarSiguienteSolicitud();
    } catch (const std::underflow_error&) {
        vaciaCapturada = true;
    }
    verificarPrueba(vaciaCapturada, "Prueba 13: Procesar lista de espera vacia");

    std::cout << "Todas las 14 pruebas automatizadas finalizaron exitosamente!\n\n";
}

void submenuSolicitudes(Registro& sistema) {
    int op = -1;
    while (op != 0) {
        std::cout << "\n--- GESTION DE SOLICITUDES ---\n"
                  << "1. Registrar nueva solicitud\n"
                  << "2. Mostrar solicitudes pendientes\n"
                  << "3. Consultar solicitud por placa\n"
                  << "4. Cancelar solicitud\n"
                  << "0. Volver al menu principal\n";
        op = leerEntero("Seleccione una opcion: ");

        try {
            if (op == 1) {
                std::string placa, prop;
                std::cout << "Ingrese placa: ";
                std::getline(std::cin, placa);
                std::cout << "Ingrese nombre del propietario: ";
                std::getline(std::cin, prop);
                int tipoInt = leerEntero("Tipo de vehiculo (1: Automovil, 2: Motocicleta): ");
                if (tipoInt != 1 && tipoInt != 2) {
                    throw std::invalid_argument("Tipo de vehiculo invalido. Debe ser 1 o 2.");
                }
                sistema.registrarSolicitud(placa, prop, tipoInt == 1);
            } else if (op == 2) {
                sistema.mostrarSolicitudesPendientes();
            } else if (op == 3) {
                std::string placa;
                std::cout << "Ingrese placa a consultar: ";
                std::getline(std::cin, placa);
                sistema.consultarSolicitudPorPlaca(placa);
            } else if (op == 4) {
                std::string placa;
                std::cout << "Ingrese placa de la solicitud a cancelar: ";
                std::getline(std::cin, placa);
                sistema.cancelarSolicitud(placa);
            } else if (op != 0) {
                std::cout << "Opcion invalida.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
}

void submenuEstacionados(Registro& sistema) {
    int op = -1;
    while (op != 0) {
        std::cout << "\n--- CONSULTAR VEHICULOS ESTACIONADOS ---\n"
                  << "1. Listar desde el primero al ultimo (orden directo)\n"
                  << "2. Listar desde el ultimo al primero (orden inverso)\n"
                  << "3. Buscar vehiculo por placa\n"
                  << "4. Consultar total de vehiculos estacionados\n"
                  << "0. Volver al menu principal\n";
        op = leerEntero("Seleccione una opcion: ");

        try {
            if (op == 1) {
                sistema.mostrarEstacionadosDirecto();
            } else if (op == 2) {
                sistema.mostrarEstacionadosInverso();
            } else if (op == 3) {
                std::string placa;
                std::cout << "Ingrese placa a buscar: ";
                std::getline(std::cin, placa);
                sistema.consultarVehiculoEstacionado(placa);
            } else if (op == 4) {
                std::cout << "Total de vehiculos estacionados: " << sistema.getTotalEstacionados() << "\n";
            } else if (op != 0) {
                std::cout << "Opcion invalida.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
}

void submenuEncargados(Registro& sistema) {
    int op = -1;
    while (op != 0) {
        std::cout << "\n--- GESTION DE ENCARGADOS ---\n"
                  << "1. Registrar encargado\n"
                  << "2. Eliminar encargado\n"
                  << "3. Consultar siguiente encargado en turno\n"
                  << "4. Mostrar todos los encargados y atenciones\n"
                  << "5. Mostrar orden de rotacion\n"
                  << "0. Volver al menu principal\n";
        op = leerEntero("Seleccione una opcion: ");

        try {
            if (op == 1) {
                std::string id, nombre;
                std::cout << "Ingrese ID del encargado: ";
                std::getline(std::cin, id);
                std::cout << "Ingrese nombre del encargado: ";
                std::getline(std::cin, nombre);
                sistema.registrarEncargado(id, nombre);
                std::cout << "Encargado registrado correctamente.\n";
            } else if (op == 2) {
                std::string id;
                std::cout << "Ingrese ID del encargado a eliminar: ";
                std::getline(std::cin, id);
                sistema.eliminarEncargado(id);
                std::cout << "Encargado eliminado correctamente.\n";
            } else if (op == 3) {
                sistema.consultarSiguienteEncargado();
            } else if (op == 4) {
                sistema.mostrarEncargados();
            } else if (op == 5) {
                sistema.mostrarOrdenRotacion();
            } else if (op != 0) {
                std::cout << "Opcion invalida.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
}

int main() {
    try {
        ejecutarPruebasAutomatizadas();
    } catch (const std::exception& e) {
        std::cout << "Error critico en pruebas: " << e.what() << "\n";
        return 1;
    }

    Registro* sistema = nullptr;
    std::cout << "=== CONFIGURACION INICIAL DEL ESTACIONAMIENTO ===\n";
    while (sistema == nullptr) {
        try {
            int filas = leerEntero("Ingrese cantidad de filas: ");
            int columnas = leerEntero("Ingrese cantidad de columnas: ");
            sistema = new Registro(filas, columnas);
            std::cout << "Estacionamiento creado correctamente. Espacios disponibles: "
                      << filas * columnas << "\n";
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << " Intente nuevamente.\n";
        }
    }

    int opcion = -1;
    while (opcion != 0) {
        std::cout << "\n=========================================\n"
                  << "        SISTEMA DE ESTACIONAMIENTO\n"
                  << "=========================================\n"
                  << "1. Gestionar solicitudes de ingreso\n"
                  << "2. Procesar siguiente solicitud\n"
                  << "3. Consultar vehiculos estacionados\n"
                  << "4. Registrar salida de vehiculo\n"
                  << "5. Gestionar encargados\n"
                  << "6. Mostrar matriz del estacionamiento\n"
                  << "7. Generar reportes\n"
                  << "0. Salir\n";
        opcion = leerEntero("Seleccione una opcion: ");

        try {
            switch (opcion) {
                case 1:
                    submenuSolicitudes(*sistema);
                    break;
                case 2:
                    sistema->procesarSiguienteSolicitud();
                    break;
                case 3:
                    submenuEstacionados(*sistema);
                    break;
                case 4: {
                    std::string placa;
                    std::cout << "Ingrese placa del vehiculo que sale: ";
                    std::getline(std::cin, placa);
                    int horas = leerEntero("Ingrese horas de permanencia: ");
                    sistema->registrarSalida(placa, horas);
                    break;
                }
                case 5:
                    submenuEncargados(*sistema);
                    break;
                case 6:
                    sistema->mostrarEstadoEstacionamiento();
                    break;
                case 7:
                    sistema->generarReporteGeneral();
                    break;
                case 0:
                    std::cout << "Liberando memoria y finalizando programa...\n";
                    break;
                default:
                    std::cout << "Opcion invalida.\n";
                    break;
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    delete sistema;
    std::cout << "Memoria liberada. Programa finalizado.\n";
    return 0;
}