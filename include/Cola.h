#ifndef COLA_H
#define COLA_H

#include <queue>
#include "Proceso.h"
using namespace std;

// Clase que representa una cola de procesos
class Cola {
public:
    int numeroCola;       // Número identificador de la cola
    int quantum;          // Quantum de la cola (0 si es FCFS)
    queue<Proceso> q;     // Cola de procesos

    Cola();               // Constructor por defecto
    Cola(int num, int qtm); // Constructor con parámetros

    bool estaVacia();     // Verifica si la cola está vacía
    int tamano();         // Devuelve el tamaño de la cola
    void agregarProceso(Proceso p); // Agrega un proceso a la cola
    Proceso sacarProceso();         // Saca el primer proceso de la cola
    Proceso verProceso();           // Ve el primer proceso sin sacarlo
    void reinsertar(Proceso p);     // Reinserta un proceso al final

    int obtenerQuantum() const;      // getter del quantum
    int obtenerNumeroCola() const;   // si lo usas en otros lados
};

#endif


