/*@ <authors>
 *
 * E27 Saneli Ghamari
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
#include "IndexPQ.h"
#include "DigrafoValorado.h"
using namespace std;

/*@ <answer>

El problema se resuelve calculando los caminos mínimos desde el origen y 
hacia el destino, para luego evaluar cada vuelo (arista) como el vuelo 
de regalo.
1- Un Dijkstra en el grafo normal desde la ciudad de origen para obtener 
las distancias mínimas desde el origen a todos los vértices (vector precio).
2- Un Dijkstra en el grafo inverso desde la ciudad destino para obtener las 
distancias mínimas desde todos los vértices hasta el destino (vector precioI).
3- Bucle sobre todas las aristas dirigidas u -> w del grafo. Si asumimos que
este es el vuelo gratis (coste 0), el coste de llegar desde el origen al destino 
usándolo será: precio[u] + 0 + precioI[w].
Nos quedamos con el mínimo de todos esos costes posibles.

 el coste en tiempo: O(M + N) + O(M . logN)



 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int INF = 1e9;


// coste: O(M.logN)
void precioMax(const DigrafoValorado<int>& g, int origen, int destino) {
    int v = g.V();

    // 1. Dijkstra desde el origen al resto de vértices
    // me hace falta un vector que me da precio total hasta tal vertice
    vector<int> precio(v, INF);
    IndexPQ<int> pq(v);

    // añado el valor de la primera ciudad a la cola y los vectores
    precio[origen] = 0;
    pq.push(origen, 0);

    // coste: O(M.logN)
    while (!pq.empty()) {
        int u = pq.top().elem;
        pq.pop();
        for (auto a : g.ady(u)) {
            int w = a.hasta();
            // mirando u -> w
            int precioW = precio[w];
            int precioU = precio[u] + a.valor();
            if (precioW > precioU) {
                precio[w] = precioU;
                pq.update(w, precio[w]);
            }
        }
    }


    // 2. Dijkstra desde el destino hacia el resto de vértices (Grafo Inverso)
    DigrafoValorado<int> gI = g.inverso();
    vector<int> precioI(v, INF);
    IndexPQ<int> pqI(v);

    precioI[destino] = 0;
    pqI.push(destino, 0);

    // coste: O(M.logN)
    while (!pqI.empty()) {
        int u = pqI.top().elem;
        pqI.pop();

        for (auto a : gI.ady(u)) {
            int w = a.hasta();
            // mirando u -> w
            int precioW = precioI[w];
            int precioU = precioI[u] + a.valor();
            if (precioW > precioU) {
                precioI[w] = precioU;
                pqI.update(w, precioI[w]);
            }
        }
    }

    // 3. Probar todas las aristas como el vuelo de regalo (coste 0)
    // coste: O(N + M)
    int m = g.A();
    int precioTotal = INF;
    for (int u = 0; u < v; u++) {
        for (auto a : g.ady(u)) {
            int w = a.hasta();
            if (precio[u] != INF && precioI[w] != INF) {
                int costeConRegalo = precio[u] + precioI[w]; // la arista cuesta 0
                precioTotal = min(precioTotal, costeConRegalo);
            }
        }
    }

    // escruibir la solución
    if (precioTotal == INF) {
        cout << "IMPOSIBLE\n";
    }
    else {
        cout << precioTotal << "\n";
    }

}

void resuelveCaso() {

    // leer los datos de la entrada
    int N, M, origen, destino;
    cin >> N >> M >> origen >> destino;

    // leer el resto del caso y resolverlo posiblemente llamando a otras funciones
    // cada ciudad es un vertice, grafo de N vertices:
    DigrafoValorado<int> g(N);
    // leer M aristas(vuelos) y ponerlas en el grafo solo de la direccion que me pone, 
    // de vuelta no lo pongo porque no es igual.
    // coste: O(M)
    int c1, c2, precio;
    for (int i = 0; i < M; i++) {
        cin >> c1 >> c2 >> precio;
        c1--;
        c2--;
        // coste: O(1)
        g.ponArista({ c1, c2, precio });
    }

    // funcion Dijkstra
    // coste: O(N + (M . logN))
    precioMax(g, origen - 1, destino - 1);
    // escribir la solución
    // escribo la soluciuon en la funcion de precioMax segun el estado de los vectores.
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
    cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    return 0;
}
