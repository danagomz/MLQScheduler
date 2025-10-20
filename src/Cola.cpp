#include "Cola.h"

// Constructor por defecto
Cola :: Cola() {
    numeroCola = 0;
    quantum = 0;
}

// Constructor con par�metros
Cola :: Cola(int num, int qtm) {
    numeroCola = num;
    quantum = qtm;
}

// Verifica si la cola est� vac�a
bool Cola :: estaVacia() {
    return q.empty();
}

// Devuelve el n�mero de procesos en la cola
int Cola :: tamano() {
    return q.size();
}

// Agrega un proceso al final de la cola
void Cola :: agregarProceso(Proceso p) {
    q.push(p);
}

// Saca el primer proceso de la cola
Proceso Cola :: sacarProceso() {
    if (q.empty()) return Proceso(); // Si est� vac�a, devuelve uno vac�o
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



