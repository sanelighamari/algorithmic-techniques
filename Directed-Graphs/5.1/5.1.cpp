
/*@ <authors>
 *
 * E27 Saneli Ghamari
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;


/*@ <answer>
5.1

hago el grafo con los caminos posibles(los más cortos)

 el coste: O(N(V + A))
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

const int MAX = 10000; // solo 4 digitos puedo enseñar
const int INF = 1000000000;

// coste: O(1)
int adyacente(int v, int i) {
    switch (i) {
    case 0: return (v + 1) % MAX;
    case 1: return (v * 2) % MAX;
    case 2: return v / 3;
    }
}


// coste: O(V + A) = O(10000 + 30000) es constante
// bfs porque no me importa si en el primer paso es más pequeño o más grande, me importa 
int bfs(int origen, int destino) {
    if (origen == destino) return 0;

    vector<int> distancia(MAX, INF); // si es INF -> no visitado
    distancia[origen] = 0;

    queue<int> cola;
    cola.push(origen);

    while (!cola.empty()) {
        int v = cola.front();
        cola.pop();

        for (int i = 0; i < 3; i++) {
            int w = adyacente(v, i);
            if (distancia[w] == INF) { // no visitado
                distancia[w] = distancia[v] + 1; // su dist es de su padre + 1
                if (w == destino) return distancia[w];
                else cola.push(w);
            }
        }
    }
}

// coste: O(N(V + A))
void resuelveCaso() {
    int origen, destino;
    cin >> origen >> destino;

    cout << bfs(origen, destino) << "\n";
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
    // entrada/salida rápida
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ajustes para que cin extraiga directamente de un fichero (solamente en local)
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    if (!in.is_open()) {
        cout << "Error: no se ha podido abrir el archivo de entrada." << endl;
        // sin fichero no hay nada que leer, y cin >> ... dejaría las
        // variables sin tocar, con su valor basura
        return 1;
    }
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}
