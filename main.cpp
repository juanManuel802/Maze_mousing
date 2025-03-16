#include <iostream>
#include <fstream>
#include "Spot.h"
using namespace std;

const int FILAS = 11;   // Ajusta según el tamaño del laberinto
const int COLUMNAS = 22; 

void cargarLaberinto(char laberinto[FILAS][COLUMNAS], const string& nombreArchivo) {
    ifstream archivoEntrada("laberinto.txt");

    if (!archivoEntrada) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            laberinto[i][j] = archivoEntrada.get(); // Lectura directa
        }
        archivoEntrada.ignore(); // Ignorar el salto de línea
    }

    archivoEntrada.close();
}

void mostrarLaberinto(char laberinto[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            cout << laberinto[i][j];
        }
        cout << endl;
    }
}

void placeMouse(int row, int column, char laberinto[FILAS][COLUMNAS], Spot &mouse) {
    if (mouse.getLoc_r() >= 0 && mouse.getLoc_r() < FILAS && mouse.getLoc_c() >= 0 && mouse.getLoc_c() < COLUMNAS) {
        if (laberinto[row][column] != '#') {
            laberinto[row][column] = 'O'; // Place the mouse
            cout << "Mouse placed at [" << row << ", " << column << "]." << endl;
        } else {
            cout << "Invalid position: Wall detected at [" << row << ", " << column << "]." << endl;
        }
    } else {
        cout << "Invalid position: Out of bounds [" << row << ", " << column << "]." << endl;
    }

}

int main() {
    char laberinto[FILAS][COLUMNAS];

    cargarLaberinto(laberinto, "laberinto.txt");

    // cout << "Laberinto cargado:" << endl;
    // mostrarLaberinto(laberinto);

    Spot mouse;
    int row, column;
    cout << "Ingrese la fila donde desea colocar al ratón: ";
    cin >> row;
    cout << "Ingrese la columna donde desea colocar al ratón: ";
    cin >> column;
    mouse.setLoc_r(row);
    mouse.setLoc_c(column);
    
    placeMouse(mouse.getLoc_r(), mouse.getLoc_c(), laberinto, mouse);
    mostrarLaberinto(laberinto);
    return 0;
}