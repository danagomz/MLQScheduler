#include "Planificador.h"

// Constructor: inicializa las tres colas con sus respectivos quantums
Planificador :: Planificador() {
    cola1 = Cola(1, 3); // RR con quantum 3
    cola2 = Cola(2, 5); // RR con quantum 5
    cola3 = Cola(3, 0); // FCFS (sin quantum)
    tiempoActual = 0;
}

// Carga la lista de procesos en el planificador
void Planificador :: cargarProcesos(vector<Proceso>& lista) {
    todosLosProcesos = lista;
}

// Verifica si hay procesos pendientes en alguna cola o sin completar
bool Planificador :: hayProcesosPendientesEnSistema() {
    if (!cola1.estaVacia() | !cola2.estaVacia() | !cola3.estaVacia()) return true;
    for (int i = 0; i < todosLosProcesos.size(); i++) {
        if (!todosLosProcesos[i].estaCompletado()) return true;
    }
    return false;
}

// Inserta procesos que ya llegaron al sistema en su cola correspondiente
void Planificador :: insertarProcesosLlegados() {
    for (int i = 0; i < todosLosProcesos.size(); i++) {
        Proceso& p = todosLosProcesos[i];
        if (p.tiempoLlegada <= tiempoActual && p.tiempoLlegada >= 0 &&
            !p.estaCompletado()) {
            if (p.numeroCola == 1) cola1.agregarProceso(p);
            else if (p.numeroCola == 2) cola2.agregarProceso(p);
            else cola3.agregarProceso(p);
            p.tiempoLlegada = -100; // Marca como ya insertado
        }
    }
}

// Devuelve el número de la cola que tiene prioridad (1 > 2 > 3)
int Planificador :: obtenerColaPrioritaria() {
    if (!cola1.estaVacia()) return 1;
    if (!cola2.estaVacia()) return 2;
    if (!cola3.estaVacia()) return 3;
    return 0; // No hay procesos
}

// Busca el índice de un proceso por su etiqueta
int Planificador :: indiceProcesoPorEtiqueta(string etiqueta) {
    for (int i = 0; i < todosLosProcesos.size(); i++) {
        if (todosLosProcesos[i].etiqueta == etiqueta) return i;
    }
    return -1;
}

bool Planificador::debeExpropiar(int colaActualId) {
    // Si estoy en cola 2 o 3 y hay procesos en cola 1 → expropiar
    if ((colaActualId == 2 || colaActualId == 3) && !cola1.estaVacia()) {
        return true;
    }
    // Si estoy en cola 3 y hay procesos en cola 2 → expropiar
    if (colaActualId == 3 && cola1.estaVacia() && !cola2.estaVacia()) {
        return true;
    }
    return false;
}

// Ejecuta la simulación completa de planificación
void Planificador :: ejecutarSimulacion() {
    tiempoActual = 0;
    procesosCompletados.clear();
    insertarProcesosLlegados();

    while (hayProcesosPendientesEnSistema()) {
        insertarProcesosLlegados();
        int colaId = obtenerColaPrioritaria();
        if (colaId == 0) {
            tiempoActual++; // Si no hay procesos, avanza el tiempo
            continue;
        }

        // Selecciona la cola según prioridad
        Cola* colaActual = (colaId == 1) ? &cola1 : (colaId == 2 ? &cola2 : &cola3);
        Proceso p = colaActual->sacarProceso();

        // Si es la primera vez que se ejecuta, guarda el tiempo de respuesta
        if (!p.haIniciado) {
            p.haIniciado = true;
            p.tiempoRespuesta = tiempoActual;
        }

        int quantum = colaActual->quantum;
        // Si es FCFS o el proceso termina en este quantum
        if (quantum == 0 | p.tiempoRestante() <= quantum) {
            tiempoActual += p.tiempoRestante();
            p.tiempoEjecutado = p.tiempoRafaga;
            p.tiempoCompletado = tiempoActual;
            procesosCompletados.push_back(p);
            int idx = indiceProcesoPorEtiqueta(p.etiqueta);
            if (idx != -1) todosLosProcesos[idx] = p;
        } else {
            // Si no termina, se ejecuta por quantum y se reinserta
            p.tiempoEjecutado += quantum;
            tiempoActual += quantum;
            colaActual->reinsertar(p);
        }

        insertarProcesosLlegados();
    }
}

// Devuelve la lista de procesos completados
vector<Proceso> Planificador :: obtenerProcesosCompletados() {
    return procesosCompletados;
}

// Calcula el promedio de WT
double Planificador :: promedioWT() {
    double suma = 0;
    for (int i = 0; i < procesosCompletados.size(); i++)
        suma += procesosCompletados[i].obtenerWT();
    return procesosCompletados.empty() ? 0 : suma / procesosCompletados.size();
}

// Promedio de Completion Time
double Planificador :: promedioCT() {
    double suma = 0;
    for (int i = 0; i < procesosCompletados.size(); i++)
        suma += procesosCompletados[i].tiempoCompletado;
    return procesosCompletados.empty() ? 0 : suma / procesosCompletados.size();
}

// Promedio de Response Time
double Planificador :: promedioRT() {
    double suma = 0;
    for (int i = 0; i < procesosCompletados.size(); i++)
        suma += procesosCompletados[i].obtenerRT();
    return procesosCompletados.empty() ? 0 : suma / procesosCompletados.size();
    }

// Promedio de Turnaround Time
double Planificador::promedioTAT() {
    double suma = 0;
    for (int i = 0; i < procesosCompletados.size(); i++) suma += procesosCompletados[i].obtenerTAT();
    return procesosCompletados.empty() ? 0 : suma / procesosCompletados.size();
}
