#include <iostream>
#include "Planificador.h"
#include "Utilidades.h"
#include <iomanip>
#include <algorithm>
using namespace std;

int main() {
    // Mensaje de bienvenida
    cout << " === Simulador MLQ (RR(3), RR(5), FCFS) === " << endl;

    // Solicita el nombre del archivo de entrada
    string nombreArchivo;
    cout << "Nombre del archivo de entrada (ej: mlq001.txt): ";
    cin >> nombreArchivo;

    // Usa ruta relativa para carpeta de entradas
    string rutaEntrada = "entradas/" + nombreArchivo;

    // Lee los procesos desde el archivo
    vector<Proceso> lista = leerArchivoProcesos(rutaEntrada);
    if (lista.empty()) {
        cout << "No se encontraron procesos válidos en el archivo." << endl;
        return 0; // Termina si no hay procesos
    }

    // Crea el planificador y carga los procesos
    Planificador plan;
    plan.cargarProcesos(lista);
    plan.ejecutarSimulacion(); // Ejecuta la simulación

    // Obtiene los procesos que se completaron
    vector<Proceso> completados = plan.obtenerProcesosCompletados();

        //Ordena los procesos por etiqueta antes de imprimir
    sort(completados.begin(), completados.end(), [](const Proceso &a, const Proceso &b) {
        return a.etiqueta < b.etiqueta; // orden alfabético
    });

    // Muestra los resultados en consola
    cout << "\n === RESULTADOS DE LA PLANIFICACION === " << endl;
    cout << left
         << setw(8) << "Proceso"
         << setw(8) << "BT"
         << setw(8) << "AT"
         << setw(6) << "Cola"
         << setw(8) << "Prior"
         << setw(8) << "CT"
         << setw(8) << "TAT"
         << setw(8) << "WT"
         << setw(8) << "RT" << endl;

    // Imprime cada proceso con sus métricas
    for (int i = 0; i < completados.size(); i++) {
        Proceso p = completados[i];
        cout << left
             << setw(8) << p.etiqueta
             << setw(8) << p.tiempoRafaga
             << setw(8) << p.tiempoOriginal
             << setw(6) << p.numeroCola
             << setw(8) << p.prioridad
             << setw(8) << p.tiempoCompletado
             << setw(8) << p.obtenerTAT()
             << setw(8) << p.obtenerWT()
             << setw(8) << p.obtenerRT() << endl;
    }

    // Calcula los promedios de las métricas
    double wt = plan.promedioWT();
    double ct = plan.promedioCT();
    double rt = plan.promedioRT();
    double tat = plan.promedioTAT();

    // Solicita nombre del archivo de salida
    string nombreSalida;
    cout << "\nNombre del archivo de salida (ej: resultado001.txt): ";
    cin >> nombreSalida;

    // Usa ruta relativa para carpeta de salidas
    string rutaSalida = "salidas/" + nombreSalida;

    // Escribe los resultados en el archivo
    escribirSalida(rutaSalida, completados, wt, ct, rt, tat);

    // Mensaje final
    cout << "\nArchivo generado en: " << rutaSalida << endl;
    cout << "Simulación terminada correctamente." << endl;
    return 0;
}

