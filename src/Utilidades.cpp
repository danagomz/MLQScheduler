#include "Utilidades.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

// Divide una línea por punto y coma, eliminando espacios innecesarios
vector<string> splitPorPuntoYComa(string linea) {
    vector<string> partes;
    string temp = "";
    for (int i = 0; i < (int)linea.size(); i++) {
        char c = linea[i];
        if (c == ';') {
            // Elimina espacios al inicio y final
            int s = 0;
            while (s < (int)temp.size() && temp[s] == ' ') s++;
            int e = temp.size() - 1;
            while (e >= 0 && temp[e] == ' ') e--;
            if (e >= s) partes.push_back(temp.substr(s, e - s + 1));
            else partes.push_back("");
            temp = "";
        } else temp.push_back(c);
    }
    // Procesa el último fragmento
    int s = 0;
    while (s < (int)temp.size() && temp[s] == ' ') s++;
    int e = temp.size() - 1;
    while (e >= 0 && temp[e] == ' ') e--;
    if (e >= s) partes.push_back(temp.substr(s, e - s + 1));
    else if (!temp.empty()) partes.push_back("");
    return partes;
}

// Convierte una línea en un objeto Proceso
Proceso parsearLinea(const string &linea) {
    if (linea.empty() || linea[0] == '#') {
        return Proceso(); // línea vacía o comentario
    }

    vector<string> partes = splitPorPuntoYComa(linea);

    if (partes.size() < 5) {
        return Proceso(); // no hay suficientes datos
    }

    string etiqueta = partes[0];
    int bt = stoi(partes[1]);   // Burst Time
    int at = stoi(partes[2]);   // Arrival Time
    int q  = stoi(partes[3]);   // Número de Cola
    int pr = stoi(partes[4]);   // Prioridad

    return Proceso(etiqueta, bt, at, q, pr);
}

// Lee todos los procesos desde un archivo
vector<Proceso> leerArchivoProcesos(string nombreArchivo) {
    vector<Proceso> lista;
    ifstream archivo(nombreArchivo.c_str());
    if (!archivo.is_open()) {
        cout << "Error al abrir " << nombreArchivo << endl;
        return lista;
    }
    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        // Ignora líneas vacías o con caracteres especiales
        int i = 0;
        while (i < (int)linea.size() && (linea[i] == ' ' || linea[i] == '\t' || linea[i] == '\r')) i++;
        if (i >= (int)linea.size()) continue;
        string sub = linea.substr(i);
        if (sub.size() == 0) continue;
        if (sub[0] == '#') continue; // Ignora comentarios
        Proceso p = parsearLinea(sub);
        if (p.tiempoRafaga > 0) lista.push_back(p); // Solo agrega si tiene BT válido
    }
    archivo.close();
    cout << "Se leyeron " << lista.size() << " procesos del archivo: " << nombreArchivo << endl;
    return lista;
}

// Escribe los resultados de la simulación en un archivo
void escribirSalida(string nombreSalida, vector<Proceso> procesos,
                    double wtProm, double ctProm, double rtProm, double tatProm) {
    ofstream out(nombreSalida.c_str());
    if (!out.is_open()) {
        cout << "Error al crear archivo de salida: " << nombreSalida << endl;
        return;
    }
    // Encabezado del archivo
    out << "# etiqueta; BT; AT; Q; Pr; WT; CT; RT; TAT\n";
    for (int i = 0; i < (int)procesos.size(); i++) {
        Proceso p = procesos[i];
        out << p.etiqueta << ";" << p.tiempoRafaga << ";" << p.tiempoOriginal << ";"
            << p.numeroCola << ";" << p.prioridad << ";" << p.obtenerWT() << ";"
            << p.tiempoCompletado << ";" << p.obtenerRT() << ";" << p.obtenerTAT() << "\n";
    }
    // Promedios finales
    out << "\nWT=" << wtProm << "; CT=" << ctProm << "; RT=" << rtProm << "; TAT=" << tatProm << ";\n";
    out.close();
    cout << "Archivo de salida escrito: " << nombreSalida << endl;
}

