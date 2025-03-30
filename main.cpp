#include <iostream>
#include <fstream>
#include <vector>
#include "List.h"
#include "Stack.h"
#include "Spot.h" 
using namespace std;

const int FILAS = 11; // Ajusta según el tamaño del laberinto
const int COLUMNAS = 22;

// Función para cargar el laberinto desde el archivo usando getline()
void cargarLaberinto(char laberinto[FILAS][COLUMNAS], const string &nombreArchivo)
{
    ifstream archivoEntrada(nombreArchivo);
    if (!archivoEntrada)
    {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    string linea;
    int fila = 0;
    while (getline(archivoEntrada, linea) && fila < FILAS)
    {
        // Copiamos solo los primeros COLUMNAS caracteres de cada línea
        for (int j = 0; j < COLUMNAS && j < linea.size(); j++)
        {
            laberinto[fila][j] = linea[j];
        }
        fila++;
    }

    if (fila < FILAS)
    {
        cout << "Advertencia: El archivo tiene menos filas de las esperadas." << endl;
    }

    archivoEntrada.close();
}

// Función para imprimir el laberinto
void mostrarLaberinto(char laberinto[FILAS][COLUMNAS])
{
    for (int i = 0; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
        {
            cout << laberinto[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

// Función que verifica si una posición es válida para avanzar
bool es_valido(const Spot &dot, char laberinto[FILAS][COLUMNAS])
{
    int r = dot.getLoc_r();
    int c = dot.getLoc_c();

    return (r >= 0 && r < FILAS && c >= 0 && c < COLUMNAS &&
            (laberinto[r][c] == ' ' || laberinto[r][c] == 'E'));
}

// Función para actualizar la posición del ratón
void moveMouse(Spot &mouse, const Spot &new_dot)
{
    mouse.setLoc_r(new_dot.getLoc_r());
    mouse.setLoc_c(new_dot.getLoc_c());
}

// Función para obtener vecinos válidos
vector<Spot> obtener_opciones(const Spot &current, char laberinto[FILAS][COLUMNAS])
{
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
    return opciones;
}

void dfs(Spot &mouse, char laberinto[FILAS][COLUMNAS])
{
    Stack<Spot> ruta;            // Pila de visitados (camino recorrido)
    Stack<Spot> alternativas;    // Pila de alternativas en intersecciones

    // Iniciamos en el punto de partida
    ruta.push(mouse);
    // Marcamos el inicio si no es la salida
    if(laberinto[mouse.getLoc_r()][mouse.getLoc_c()] != 'E')
        laberinto[mouse.getLoc_r()][mouse.getLoc_c()] = 'O';
    mostrarLaberinto(laberinto);

    while (ruta.size() != 0)
    {
        Spot current = ruta.top();
        // Verificamos si se encontró la salida
        if(laberinto[current.getLoc_r()][current.getLoc_c()] == 'E')
        {
            cout << "¡Salida encontrada en (" << current.getLoc_r() << ", " 
                 << current.getLoc_c() << ")!" << endl;
            return;
        }

        vector<Spot> opciones = obtener_opciones(current, laberinto);

        if (opciones.size() > 1)
        {
            // En intersección: se guarda el token de decisión (-1, -1)
            ruta.push(Spot(-1, -1));  // Token de decisión
            // Se guardan todas las alternativas menos una (la que se tomará ahora)
            for (int i = 0; i < opciones.size() - 1; i++)
            {
                alternativas.push(opciones[i]);
            }
            // Se elige la última opción para avanzar
            Spot next = opciones.back();
            moveMouse(mouse, next);
            ruta.push(next);
            if(laberinto[next.getLoc_r()][next.getLoc_c()] != 'E')
                laberinto[next.getLoc_r()][next.getLoc_c()] = 'O';
            mostrarLaberinto(laberinto);
        }
        else if (opciones.size() == 1)
        {
            // Solo hay una opción, se sigue avanzando
            Spot next = opciones[0];
            moveMouse(mouse, next);
            ruta.push(next);
            if(laberinto[next.getLoc_r()][next.getLoc_c()] != 'E')
                laberinto[next.getLoc_r()][next.getLoc_c()] = 'O';
            mostrarLaberinto(laberinto);
        }
        else
        {
            // Callejón sin salida, se retrocede
            // Marcamos la celda actual con '-' para indicar retroceso (si no es token)
            if (!(current.getLoc_r() == -1 && current.getLoc_c() == -1))
                laberinto[current.getLoc_r()][current.getLoc_c()] = '-';
            mostrarLaberinto(laberinto);
            ruta.pop();  // Retiramos la celda sin salida

            // Si el tope de la pila es un token de decisión, se elimina y se toma una alternativa
            if (!ruta.size() == 0 && ruta.top().getLoc_r() == -1 && ruta.top().getLoc_c() == -1)
            {
                ruta.pop();  // Se descarta el token de decisión
                if (!alternativas.size() == 0)
                {
                    Spot alt = alternativas.top();
                    alternativas.pop();
                    moveMouse(mouse, alt);
                    ruta.push(alt);
                    if(laberinto[alt.getLoc_r()][alt.getLoc_c()] != 'E')
                        laberinto[alt.getLoc_r()][alt.getLoc_c()] = 'O';
                    cout << "Retroceso y cambio de camino en (" << alt.getLoc_r() << ", " 
                         << alt.getLoc_c() << ")..." << endl;
                    mostrarLaberinto(laberinto);
                }
            }
        }
    }
    cout << "El ratón quedó atrapado. No se encontró salida." << endl;
}

int main()
{
    char laberinto[FILAS][COLUMNAS];
    cargarLaberinto(laberinto, "laberinto.txt");

    Spot mouse;
    int row, column;
    // Se valida que el punto de entrada sea un espacio blanco (o la salida 'E')
    bool entradaValida = false;
    do {
        cout << "Ingrese la fila donde desea colocar al ratón: ";
        cin >> row;
        cout << "Ingrese la columna donde desea colocar al ratón: ";
        cin >> column;
        if (row < 0 || row >= FILAS || column < 0 || column >= COLUMNAS)
        {
            cout << "Coordenadas fuera de rango. Intente de nuevo." << endl;
            continue;
        }
        if (laberinto[row][column] == '#' )
        {
            cout << "La posición corresponde a una pared. Ingrese otro punto de entrada." << endl;
        }
        else
        {
            entradaValida = true;
        }
    } while (!entradaValida);

    mouse.setLoc_r(row);
    mouse.setLoc_c(column);

    char opcion;
    do {
        // Se ejecuta la búsqueda DFS
        dfs(mouse, laberinto);
        cout << "¿Desea ejecutar otro intento? (S/N): ";
        cin >> opcion;
        if(tolower(opcion) == 's')
        {
            // Reiniciamos el laberinto para el siguiente intento
            cargarLaberinto(laberinto, "laberinto.txt");
            // Se valida nuevamente el punto de entrada, ya que el laberinto se reinició
            mouse.setLoc_r(row);
            mouse.setLoc_c(column);
        }
    } while(tolower(opcion) == 's');

    return 0;
}
