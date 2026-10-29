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

4.3

inicializo el grafo
el objetivo es encontrar el tamaño del grafo conexo más grande 
del grafo general.
un bucle de todos los vertices(personas), y si no está visitado(false),
llamo a dfs y devuelvo el tamaño del grafo que incluye este vertice.

el coste: O(N + E)
N es vertices y E relaciones amistades
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

// coste: O(V+A) = O(V)
void dfs(Grafo const& g, int m, vector<bool>& visitado, int& tam) {
   // le marco que he visitado
   visitado[m] = true;
   tam++;


   // recorrer los adyacentes(amigos) de m
   for (int w : g.ady(m)) {
      if (!visitado[w]) { // si no esta marcado llamo a dfs y sigo
         dfs(g, w, visitado, tam);
      }
   }
}

void resuelveCaso() {
   int N, M;
   // N personas(vertices)
   cin >> N;

   // inicializo la lista
   Grafo g = Grafo(N);

   // M amistades(aristas)
   cin >> M;
   int m1, m2;
   // rellenar la lista
   // el coste: O(M(N+M))
   for (int i = 0; i < M; i++) {
      cin >> m1 >> m2;
      // el enunciado empieza a contar desde 1, pero mi grafo desde 0
      g.ponArista(m1 - 1, m2 - 1);
   }


   vector<bool> visitado(g.V(), false);
   int tamMax = 0; // empiezo con tam 0

   // el coste: O(N)
   // el coste es exactamente N porque llamo a dfs si no está marcado
   // recorro todas las N personas por si el grafo no es conexto.
   // si se repite la amistad, no pasa nada poque no paso dos veces 
   // por un vertice, porque miro si no está true.
   for (int i = 0; i < N; ++i) {
      if (!visitado[i]) { // si no está visitado, le llamo a dfs
         // tam para poder comparar con tamMax para grafos conexos separados
         int tam = 0;
         dfs(g, i, visitado, tam);

         if (tam > tamMax) tamMax = tam;
      }
   }

   // escribir la solución
   cout << tamMax << "\n";
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
