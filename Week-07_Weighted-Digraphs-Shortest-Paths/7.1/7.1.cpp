
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
7.1


 el coste: O()
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

const int INF = 1e9;

// O((V + C) logV)
void resolverPedido(const DigrafoValorado<int>& g, int origen, int destino) {
   int v = g.V();
   vector<int> dist(v, INF);
   vector<int> ulti(v, -1);
   IndexPQ<int> pq(g.V());

   // vertice origen
   dist[origen] = 0;
   // en pq: vertice, su distancia
   pq.push(origen, 0);

   // O((V + C) logV)
   // C = A (tramo de calle)
   while(!pq.empty()) {
      int v = pq.top().elem;
      pq.pop();

      // un bucle de todos los vertices, y un if si
      // la dist del vertce(a) + su coste hasta el vertice 
      // que estoy mirando(w) es menor de la dist que tiene
      // w. y si es menor relajar: cambio dist y su anterior
      // (ulti) y update de pq porque se ha cambiado su dist.
      for (auto a : g.ady(v)) {
         //int v = a.desde();
         int w = a.hasta();
         int tiempo = a.valor();

         if (dist[v] + tiempo < dist[w]) {
            dist[w] = dist[v] + tiempo;
            ulti[w] = v;
            pq.update(w, dist[w]);
         }
      }

   }

   // O(V)
   // escribir la solucion
   if (dist[destino] == INF) {
      cout << "NO LLEGA\n";
   } else {
      cout << dist[destino] << ":";

      // O(V)
      // construyo el vector camino desde el destino
      // llendo uno uno hacia atras
      vector<int> camino;
      // en vez de i++ le igualo cada vez a su padre, y para su padre 
      //le igualo a su padre hasta que llegue a -1 que es la raiz(origen).
      for (int actual = destino; actual != -1; actual = ulti[actual]) {
         camino.push_back(actual);
      }

      // O(V)
      // recorriendo el vector pero esta al reves
      for (int i = camino.size() - 1; i >= 0; i--) {
         cout << " " << camino[i] + 1;
         if (i > 0) cout << " ->";
      }
      cout << "\n";
   }


}

// coste: O(K . (V + C) logV))
void resuelveCaso() {
   int N, C;
   cin >> N >> C;
   DigrafoValorado<int> g(N); // vértices de 0 a N-1

   int p1, p2, tiempo;
   // coste: O(C) = O(C) * O(1)
   for (int i = 0; i < C; i++) {
      cin >> p1 >> p2 >> tiempo;
      // inicializar el grafo con inicio, fin y coste
      p1--;
      p2--;
      // coste: O(1) = O(1) + O(1)
      g.ponArista({p1, p2, tiempo});
      g.ponArista({p2, p1, tiempo});
   }

   int K;
   cin >> K;

   int origen, destino;
   // coste: O(K . (V + C) logV))
   for (int i = 0; i < K; i++) {
      cin >> origen >> destino;
      resolverPedido(g, origen - 1, destino - 1);
   }

   
   cout << "---\n";
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
