
/*@ <authors>
 *
 * E27 Saneli Ghamari
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "Grafo.h"
/*@ <answer>

4.1

el coste: O(n(V + A)) + O(1) + O(V)

si es conexo y acíclico es árbol.
no tiene ciclos -> si A == V - 1
conexo -> si hago DFS o BFS y me da V

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

// coste: O(V+A) = O(V)
void dfs(Grafo const& g, int v, vector<bool>& visitado, int& cont) {
   visitado[v] = true;
   cont++;

   // recorrer los adyacentes de v
    for (int w : g.ady(v)) {
        if (!visitado[w]) {
            dfs(g, w, visitado, cont);
        }
    }
}

bool resuelveCaso() {
   int n;

   if (!(cin >> n)) return false;

   for (int j = 0; j < n; j++) {
      int V, A;
      // leer los datos de la entrada
      cin >> V;

      // inicializo la lista
      Grafo g = Grafo(V);

      cin >> A;

      int v1, v2;
      // coste: O(A(V+A))
      for (int i = 0; i < A; i++) {
         cin >> v1 >> v2;
         // coste: O(V+A)
         g.ponArista(v1, v2);
      }

      // O(1)
      if (A != V - 1) {
         cout << "NO\n";
         continue;;
      }

      vector<bool> visitado(g.V(), false);
      int visitados = 0;
      int cont = 0;

      // O(V)
      dfs(g, 0, visitado, cont);

      if (cont == V) {
         cout << "SI\n";
      }
      else {
         cout << "NO\n";
      }
      // escribir la solución
   }
   return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("casos.txt");
   if (!in.is_open())
      cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
   auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

   while (resuelveCaso());

   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   cin.rdbuf(cinbuf);
#endif
   return 0;
}
