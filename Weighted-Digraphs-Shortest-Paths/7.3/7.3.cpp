
/*@ <authors>
 *
 * E27 Saneli Ghamari
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <vector>
#include "DigrafoValorado.h"
#include "IndexPQ.h"

using namespace std;


/*@ <answer>
7.3


 el coste: O(N + (C.logN)
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

const int INF = 1e9;

// O((N + C) logN)
void caminoMin(const DigrafoValorado<int>& g) {
   int v = g.V();

   vector<int> dist(v, INF);
   // en cola pq: vertice, su distancia
   IndexPQ<int> pq(g.V());
   // un vector para contar las formas que puedo 
   // llegar de un vertice, empezando en 0(casa).
   // voy sustituyendo las formas si avanzo, si hay 
   // otro vertice con longitud igual le sumo.
   vector<int> cont(v, 0);

   // vertice casa
   dist[0] = 0;
   cont[0] = 1;
   pq.push(0, 0);

   // O((N + C) logV)
   while(!pq.empty()) {
      int u = pq.top().elem;
      pq.pop();

      for (auto a : g.ady(u)) {
         int w = a.hasta();
         int longitud = a.valor();

         if (dist[u] + longitud < dist[w]) {
            dist[w] = dist[u] + longitud;
            cont[w] = cont[u]; // se hereda
            pq.update(w, dist[w]);
         } else if (dist[u] + longitud == dist[w]) {
            cont[w] += cont[u]; // se acumula
         }
      }
   }

   // escribir la solucion
   cout << cont[v - 1] << "\n";
}

// coste: O(N + C) logN))
void resuelveCaso() {
   int N, C; // interseccion, calle
   cin >> N >> C;
   DigrafoValorado<int> g(N); // vértices de 0 a N-1

   int p1, p2, longitud;
   // coste: O(C) = O(C) * O(1)
   for (int i = 0; i < C; i++) {
      cin >> p1 >> p2 >> longitud;
      // inicializar el grafo con inicio, fin y coste
      p1--;
      p2--;
      // coste: O(1) = O(1) + O(1)
      // calle de doble sentido, pongo cada arista 2 veces
      g.ponArista({p1, p2, longitud});
      g.ponArista({p2, p1, longitud});
   }

   // coste: O(N + C) logN)
   caminoMin(g);
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
