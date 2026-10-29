
/*@ <authors>
 *
 * E27 Saneli Ghamari
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include "Digrafo.h"

using namespace std;


/*@ <answer>
5.2

busco los restaurantes que pueden ser visitados en el camino entre 
origen y destino, tengo que hacer dos dfs.
primero en el grafo original desde origen para marcar los restaurantes
alcanzables.
segundo en el grafo inverso desde destino para marcar los restaurantes 
desde los que se puede llegar a la meta.
los restaurantes que deben ofrecer paella son aquellos visitados en ambos recorridos.

 el coste: O(Q(V + A)) = O(NA) + Q(2 * O(NV + NA)) = O(Q *(NV + NA))
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


// coste: O(NV + NA) es constante
// dfs porque no me importa si tardo más o paso del sitio repetido
void dfs(Digrafo const& g, int v, vector<bool>& visitados) {
    visitados[v] = true;
    for (int w : g.ady(v)) {
        if (!visitados[w]) {
            //visitados[w] = true;
            dfs(g, w, visitados);
        }
    }
}

// coste: O(Q *(NV + NA))
void resuelveCaso() {
    int NV, NA, origen, destino, Q;
    cin >> NV >> NA;

    Digrafo g(NV);
    // coste: O(NA)
    for (int i = 0; i < NA; i++) {
        cin >> origen >> destino;
        origen--;
        destino--;

        g.ponArista(origen, destino);
    }
    
    Digrafo inverso = g.inverso();
    cin >> Q;
    // coste: O(Q *(NV + NA))
    while (Q--) {
        cin >> origen >> destino;
        origen--;
        destino--;

        vector<bool> visitados(NV, false);
        // coste: O(NV + NA)
        dfs(g, origen, visitados);

        if (!visitados[destino]) cout << "IMPOSIBLE\n";
        else { // grafo inverso para ver si el camino es correcto
            vector<bool> visitadosInv(NV, false);
            // coste: O(NV + NA)
            dfs(inverso, destino, visitadosInv); // empezando del destino, inverso

            int cont = 0;
            // coste: O(NV)
            for (int i = 0; i < NV; i++) {
                if (visitados[i] && visitadosInv[i]) cont++;
            }

            cout << cont - 2 << "\n"; // no vale ni origen ni destino(-2)
        }
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
