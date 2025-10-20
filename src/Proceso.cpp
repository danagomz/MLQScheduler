#include "Proceso.h"

// Constructor por defecto: inicializa todos los valores
Proceso :: Proceso() {
    etiqueta = "";
    tiempoRafaga = 0;
    tiempoLlegada = 0;
    numeroCola = 0;
    prioridad = 0;
    tiempoEjecutado = 0;
    tiempoCompletado = 0;
    tiempoRespuesta = -1; // -1 indica que aún no ha respondido
    haIniciado = false;
    tiempoOriginal = 0;
}

// Constructor con parámetros: inicializa con valores dados
Proceso :: Proceso(string etiqueta_, int bt, int at, int q, int pr) {
    etiqueta = etiqueta_;
    tiempoRafaga = bt;
    tiempoLlegada = at;
    tiempoOriginal = at;
    numeroCola = q;
    prioridad = pr;
    tiempoEjecutado = 0;
    tiempoCompletado = 0;
    tiempoRespuesta = -1;
    haIniciado = false;
}

// Verifica si el proceso ya ejecutó todo su tiempo de ráfaga
bool Proceso :: estaCompletado() {
    return tiempoEjecutado >= tiempoRafaga;
}

// Calcula cuánto tiempo le falta por ejecutar
int Proceso :: tiempoRestante() {
    return tiempoRafaga - tiempoEjecutado;
}

// Devuelve una cadena con la información del proceso
string Proceso :: toString() {
    stringstream ss;
    ss << etiqueta << ": BT=" << tiempoRafaga << ", AT=" << tiempoLlegada
       << ", Q=" << numeroCola << ", Pr=" << prioridad;
    return ss.str();
}

// Calcula el Turnaround Time
int Proceso :: obtenerTAT() {
    return tiempoCompletado - tiempoOriginal;
}

// Calcula el Waiting Time
int Proceso :: obtenerWT() {
    return obtenerTAT() - tiempoRafaga;
}

// Calcula el Response Time
int Proceso :: obtenerRT() {
    if (tiempoRespuesta < 0) return 0; // aún no inició
    return tiempoRespuesta - tiempoOriginal;
}
