#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <vector>
#include <string>
#include "Proceso.h"
using namespace std;

// Funciones auxiliares para leer y escribir archivos de procesos
vector<Proceso> leerArchivoProcesos(string nombreArchivo); // Lee procesos desde archivo
void escribirSalida(string nombreSalida, vector<Proceso> procesos,
                    double wtProm, double ctProm, double rtProm, double tatProm); // Escribe resultados en archivo

#endif


