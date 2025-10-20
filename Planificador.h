#ifndef PLANIFICADOR_H
#define PLANIFICADOR_H

#include <vector>
#include <iostream>
#include "Cola.h"
#include "Proceso.h"
using namespace std;

// Clase principal que gestiona la planificaci�n de procesos
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
    bool hayProcesosPendientesEnSistema();       // Verifica si a�n hay procesos por ejecutar
    int obtenerColaPrioritaria();                // Determina cu�l cola tiene prioridad
    int indiceProcesoPorEtiqueta(string etiqueta); // Busca el �ndice de un proceso por su nombre
    void ejecutarSimulacion();                   // Ejecuta toda la simulaci�n


    vector<Proceso> obtenerProcesosCompletados(); // Devuelve los procesos terminados

    double promedioWT();   // Promedio de Waiting Time
    double promedioCT();   // Promedio de Completion Time
    double promedioRT();   // Promedio de Response Time
    double promedioTAT();  // Promedio de Turnaround Time
};

#endif
