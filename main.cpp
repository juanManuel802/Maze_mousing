#include <iostream>
#include <fstream>
#include "List.h"
#include "Stack.h"
#include "Spot.h"
#include <vector>
using namespace std;

const int FILAS = 11;    // Ajusta según el tamaño del laberinto
const int COLUMNAS = 22;

// Función para cargar el laberinto desde el archivo usando getline()
void cargarLaberinto(char laberinto[FILAS][COLUMNAS], const string& nombreArchivo) {
    ifstream archivoEntrada(nombreArchivo);
    if (!archivoEntrada) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }
    
    string linea;
    int fila = 0;
    while (getline(archivoEntrada, linea) && fila < FILAS) {
        // Copiamos solo los primeros COLUMNAS caracteres de cada línea
        for (int j = 0; j < COLUMNAS && j < linea.size(); j++) {
            laberinto[fila][j] = linea[j];
        }
        fila++;
    }
    
    if (fila < FILAS) {
        cout << "Advertencia: El archivo tiene menos filas de las esperadas." << endl;
    }
    
    archivoEntrada.close();
}

// Función para imprimir el laberinto
void mostrarLaberinto(char laberinto[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            cout << laberinto[i][j];
        }
        cout << endl;
    }
}

// Función que verifica si una posición es válida para avanzar
bool es_valido(const Spot& dot, char laberinto[FILAS][COLUMNAS]) {
    int r = dot.getLoc_r();
    int c = dot.getLoc_c();
    return (r >= 0 && r < FILAS && c >= 0 && c < COLUMNAS &&
            laberinto[r][c] != '#' && laberinto[r][c] != 'O');
}

// Función para actualizar la posición del ratón
void moveMouse(Spot &mouse, const Spot& new_dot) {
    mouse.setLoc_r(new_dot.getLoc_r());
    mouse.setLoc_c(new_dot.getLoc_c());
}

// Función DFS para encontrar la salida ('E') en el laberinto
void dfs(Spot &mouse, char laberinto[FILAS][COLUMNAS]) {
    // Usamos las pilas implementadas (no tienen empty(), así que usamos size())
    Stack<Spot> ruta;           // Pila para la ruta del ratón
    Stack<Spot> intersecciones; // Pila para las intersecciones

    ruta.push(mouse);
    laberinto[mouse.getLoc_r()][mouse.getLoc_c()] = 'O';  // Marcamos la celda visitada

    while (ruta.size() != 0) {
        Spot current = ruta.top();

        // Si encontramos la salida, terminamos la búsqueda
        if (laberinto[current.getLoc_r()][current.getLoc_c()] == 'E') {
            cout << "¡Salida encontrada en (" << current.getLoc_r() << ", " 
                 << current.getLoc_c() << ")!" << endl;
            return;
        }

        vector<Spot> opciones;
        Spot up(current.getLoc_r() - 1, current.getLoc_c());
        Spot down(current.getLoc_r() + 1, current.getLoc_c());
        Spot left(current.getLoc_r(), current.getLoc_c() - 1);
        Spot right(current.getLoc_r(), current.getLoc_c() + 1);

        if (es_valido(up, laberinto))
            opciones.push_back(up);
        if (es_valido(down, laberinto))
            opciones.push_back(down);
        if (es_valido(left, laberinto))
            opciones.push_back(left);
        if (es_valido(right, laberinto))
            opciones.push_back(right);

        if (opciones.empty()) {  
            // Retrocede si no hay movimientos posibles
            ruta.pop();
            // Solo verificamos si ambas pilas tienen elementos para evitar acceso indebido
            if (intersecciones.size() > 0 && ruta.size() > 0 &&
                ruta.top().getLoc_r() == intersecciones.top().getLoc_r() &&
                ruta.top().getLoc_c() == intersecciones.top().getLoc_c()) {
                intersecciones.pop();
            }
        } else {
            // Si hay más de una opción, guardamos la posición actual como intersección
            if (opciones.size() > 1) {
                intersecciones.push(current);
            }
            // Elegimos la última opción (puedes cambiar la estrategia si lo deseas)
            Spot next = opciones.back();
            opciones.pop_back();
            moveMouse(mouse, next);
            ruta.push(next);
            laberinto[next.getLoc_r()][next.getLoc_c()] = 'O';  // Marcamos la celda visitada
        }
    }
    cout << "No se encontró salida." << endl;
}

int main() {
    char laberinto[FILAS][COLUMNAS];
    cargarLaberinto(laberinto, "laberinto.txt");

    Spot mouse;
    int row, column;
    cout << "Ingrese la fila donde desea colocar al ratón: ";
    cin >> row;
    cout << "Ingrese la columna donde desea colocar al ratón: ";
    cin >> column;
    mouse.setLoc_r(row);
    mouse.setLoc_c(column);
    
    dfs(mouse, laberinto);
    mostrarLaberinto(laberinto);
    return 0;
}
