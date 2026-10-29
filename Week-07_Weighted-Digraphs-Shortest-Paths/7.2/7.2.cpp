
/*@ <authors>
 *
 * E27 Saneli Ghamari
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include "DigrafoValorado.h"
#include "IndexPQ.h"

using namespace std;


/*@ <answer>
7.2



el coste(tiempo): O((N + M) log N)
el coste(espacio): O()
@ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

const int INF = 1e9;

void caminoMinimo(const DigrafoValorado<int>& g, int tiempoInicial) {
   int v = g.V();
   vector<int> dist(v, INF);
   vector<int> ulti(v, -1);
   IndexPQ<int> pq(g.V());

   dist[0] = tiempoInicial;
   // en pq: vertice, su distancia
   pq.push(0, dist[0]);

   // O((M + N) logN)
   while(!pq.empty()) {
      int v = pq.top().elem;
      pq.pop();

      for (auto a : g.ady(v)) {
         int w = a.hasta();
         int tiempo = a.valor();

        if (dist[v] + tiempo < dist[w]) {
            if (dist[w] == INF) {
                dist[w] = dist[v] + tiempo;
                pq.push(w, dist[w]);
            } else {
                dist[w] = dist[v] + tiempo;
                pq.update(w, dist[w]);
            }
        }
    }

   }

   // escribir la solucion
    if (dist[v - 1] == INF) {
        cout << "IMPOSIBLE\n";
    } else {
        cout << dist[v - 1] << "\n";
    }


}

void resuelveCaso() {
   int N, tiempo;
   cin >> N;
   // vector que guardo el tiempo de que tarda en cargarse cada pagina
   // tiempo = tiempos[pagina 6 - 1]
   // coste: O(N)
   vector<int> tiempos(N);
    for (int i = 0; i < N; i++) {
        cin >> tiempo;
        tiempos[i] = tiempo;
    }

    int M, p1, p2, tEnlace;
    cin >> M;
    DigrafoValorado<int> g(N);
    // coste: O(M)
    // tiempo(coste) de las aristas
    for (int j = 0; j < M; j++) {
        cin >> p1 >> p2 >> tEnlace;
        p1--;
        p2--;
        g.ponArista({p1, p2, tEnlace + tiempos[p2]});
    }

    // O((N + M) log N)
    caminoMinimo(g, tiempos[0]);    

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
