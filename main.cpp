#include <iostream>
#include <fstream>

using namespace std;

const int FILAS = 11;   // Ajusta según el tamaño del laberinto
const int COLUMNAS = 22; 

void cargarLaberinto(char laberinto[FILAS][COLUMNAS], const string& nombreArchivo) {
    ifstream archivoEntrada("laberinto.txt");

    if (!archivoEntrada) {
        cerr << "Error al abrir el archivo." << endl;
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

int main() {
    char laberinto[FILAS][COLUMNAS];

    cargarLaberinto(laberinto, "laberinto.txt");

    cout << "Laberinto cargado:" << endl;
    mostrarLaberinto(laberinto);

    return 0;
}