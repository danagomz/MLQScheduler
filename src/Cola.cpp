#include "Cola.h"

// Constructor por defecto
Cola :: Cola() {
    numeroCola = 0;
    quantum = 0;
}

// Constructor con parámetros
Cola :: Cola(int num, int qtm) {
    numeroCola = num;
    quantum = qtm;
}

// Verifica si la cola está vacía
bool Cola :: estaVacia() {
    return q.empty();
}

// Devuelve el número de procesos en la cola
int Cola :: tamano() {
    return q.size();
}

// Agrega un proceso al final de la cola
void Cola :: agregarProceso(Proceso p) {
    q.push(p);
}

// Saca el primer proceso de la cola
Proceso Cola :: sacarProceso() {
    if (q.empty()) return Proceso(); // Si está vacía, devuelve uno vacío
    Proceso p = q.front();
    q.pop();
    return p;
}

// Ve el primer proceso sin sacarlo
Proceso Cola :: verProceso() {
    if (q.empty()) return Proceso();
    return q.front();
}

// Reinserta un proceso al final de la cola
void Cola :: reinsertar(Proceso p) {
    q.push(p);
}

int Cola::obtenerQuantum() const {
    return quantum;
}

int Cola::obtenerNumeroCola() const {
    return numeroCola;
}



