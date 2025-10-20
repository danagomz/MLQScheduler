#ifndef PROCESO_H
#define PROCESO_H

#include <string>
#include <sstream>
using namespace std;

// Clase que representa un proceso en el sistema
class Proceso {
public:
    string etiqueta;           // Nombre o identificador del proceso
    int tiempoRafaga;          // Tiempo total que necesita para ejecutarse (Burst Time)
    int tiempoLlegada;         // Momento en que llega al sistema (Arrival Time)
    int numeroCola;            // N�mero de la cola a la que pertenece (1, 2 o 3)
    int prioridad;             // Prioridad del proceso (no usada directamente en la simulaci�n)
    int tiempoEjecutado;       // Tiempo que ya ha sido ejecutado
    int tiempoCompletado;      // Tiempo en que termin� completamente
    int tiempoRespuesta;       // Tiempo en que empez� a ejecutarse por primera vez
    bool haIniciado;           // Indica si ya comenz� a ejecutarse
    int tiempoOriginal;        // Guarda el tiempo de llegada original (AT)

    Proceso(); // Constructor por defecto
    Proceso(string etiqueta_, int bt, int at, int q, int pr); // Constructor con par�metros

    bool estaCompletado(); // Verifica si el proceso ya termin�
    int tiempoRestante();  // Calcula cu�nto tiempo le falta por ejecutar
    string toString();     // Devuelve una descripci�n del proceso
    int obtenerTAT();      // Turnaround Time = CT - AT
    int obtenerWT();       // Waiting Time = TAT - BT
    int obtenerRT();       // Response Time = tiempoRespuesta - AT
};

#endif

