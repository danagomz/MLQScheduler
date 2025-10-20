#ifndef PLANIFICADOR_H
#define PLANIFICADOR_H

#include <vector>
#include <iostream>
#include "Cola.h"
#include "Proceso.h"
using namespace std;

// Clase principal que gestiona la planificación de procesos
class Planificador {
public:
    Cola cola1; // Cola 1 con RR(3)
    Cola cola2; // Cola 2 con RR(5)
    Cola cola3; // Cola 3 con FCFS
    int tiempoActual; // Tiempo global del sistema
    vector<Proceso> procesosCompletados; // Lista de procesos que ya terminaron
    vector<Proceso> todosLosProcesos;    // Lista de todos los procesos cargados

    Planificador(); // Constructor

    void cargarProcesos(vector<Proceso>& lista); // Carga los procesos desde archivo
    void insertarProcesosLlegados();             // Inserta procesos que ya llegaron al sistema
    bool hayProcesosPendientesEnSistema();       // Verifica si aún hay procesos por ejecutar
    int obtenerColaPrioritaria();                // Determina cuál cola tiene prioridad
    int indiceProcesoPorEtiqueta(string etiqueta); // Busca el índice de un proceso por su nombre
    void ejecutarSimulacion();                   // Ejecuta toda la simulación


    vector<Proceso> obtenerProcesosCompletados(); // Devuelve los procesos terminados

    double promedioWT();   // Promedio de Waiting Time
    double promedioCT();   // Promedio de Completion Time
    double promedioRT();   // Promedio de Response Time
    double promedioTAT();  // Promedio de Turnaround Time
};

#endif
