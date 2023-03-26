#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// Estructura que representa un estado del juego de pancakes
struct Estado {
    vector<char> pancakes;
    int costo; // cantidad de volteos realizados
    vector<int> camino; // lista de los índices de los pancakes volteados

    Estado(vector<char> p, int c, vector<int> cam) {
        pancakes = p;
        costo = c;
        camino = cam;
    }
};

// Función que imprime el camino de volteos de pancakes para llegar a la solución
void imprimir_camino(vector<int> camino) {
    for (int i = 0; i < camino.size(); i++) {
        cout << camino[i] << " ";
    }
    cout << endl;
}

// Función que verifica si el estado actual es la solución (pancakes ordenados de forma ascendente)
bool es_solucion(vector<char> pancakes) {
    vector<char> pancakes_ordenados = pancakes;
    sort(pancakes_ordenados.begin(), pancakes_ordenados.end());
    return pancakes == pancakes_ordenados;
}

// Función que realiza el volteo de los pancakes
void voltear_pancakes(vector<char>& pancakes, int desde, int hasta) {
    while (desde < hasta) {
        char temp = pancakes[desde];
        pancakes[desde] = pancakes[hasta];
        pancakes[hasta] = temp;
        desde++;
        hasta--;
    }
}

// Función que imprime el arreglo de pancakes
void imprimir_pancakes(vector<char> pancakes) {
    for (int i = 0; i < pancakes.size(); i++) {
        cout << pancakes[i] << " ";
    }
    cout << endl;
}

// Función que realiza la búsqueda en profundidad
void busqueda_profundidad(vector<char> pancakes) {
    Estado estado_inicial(pancakes, 0, {});
    stack<Estado> pila;
    pila.push(estado_inicial);
    int profundidad_maxima = 15;

    while (!pila.empty()) {

        Estado estado_actual = pila.top();
        pila.pop();

        // Funcion para imprimir el camino de volteos y terminar la búsqueda
        if (es_solucion(estado_actual.pancakes)) {

            cout << "Voltear pancakes: ";
            imprimir_camino(estado_actual.camino);
            cout << " "<< endl;
            cout << "Arreglo ordenado: ";
            imprimir_pancakes(estado_actual.pancakes);
            cout << " "<< endl;
            cout << "Nodos visitados: " << estado_actual.costo << endl;
            return;
        }

        // Funcion si se alcanza la profundidad máxima, pasar al siguiente estado
        if (estado_actual.costo >= profundidad_maxima) {
            continue;
        }

        // Funcion para generar todos los sucesores del estado actual y despues agregarlos a la pila
        for (int i = 2; i <= estado_actual.pancakes.size(); i++) {
            vector<char> pancakes_sucesor = estado_actual.pancakes;
            voltear_pancakes(pancakes_sucesor, 0, i-1);
            Estado estado_sucesor(pancakes_sucesor, estado_actual.costo+1, estado_actual.camino);
            estado_sucesor.camino.push_back(i);
            pila.push(estado_sucesor);
        }
    }


}

// Función principal
int main() {
    string entrada;
    vector<char> pancakes;

    cout << "Pancakes con busqueda en profundidad";
    cout << " "<< endl;
    cout << "Ingrese los caracteres a ordenar(letras) Ejemplo( flrpmend ) caracteres: ";
    getline(cin, entrada);
    istringstream iss(entrada);

    char c;
    while (iss >> c) {
        pancakes.push_back(c);
    }

    // Imprimir arreglo de pancakes
    cout << "Arreglo de pancakes: ";
    imprimir_pancakes(pancakes);

   busqueda_profundidad(pancakes);
    return 0;
}
