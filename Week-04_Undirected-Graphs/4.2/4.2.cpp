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

4.2


 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

// coste: O(V+A) = O(V)
// dedico el vector de colores para asignar si 
// lo he visitado o no y el color
// 0 -> no visitado
// 1 -> azul
// 2 -> rojo
bool dfs(Grafo const& g, int v, vector<int>& colores, int color) {
   // le marco el color que le toca
   colores[v] = color;

   // cambio de color
   // uso de otra variable para no tener problema en la llamada recursiva
   int siguienteColor = (color == 1) ? 2 : 1;

   // recorrer los adyacentes de v
   for (int w : g.ady(v)) {
      if (colores[w] == 0) { // si no esta marcado llamale y marcale
         if (!dfs(g, w, colores, siguienteColor)) return false;
      }
      else if (colores[w] == color) return false;
   }

   return true;
}

void resuelveCaso() {
   int V, A;
   // leer los datos de la entrada
   cin >> V;

   // inicializo la lista
   Grafo g = Grafo(V);

   cin >> A;
   int v1, v2;
   // rellenar la lista
   // el coste: O(A(V+A))
   for (int i = 0; i < A; i++) {
      cin >> v1 >> v2;
      g.ponArista(v1, v2);
   }


   vector<int> colores(g.V(), 0);

   // el coste: O(V)
   // el coste es exactamente V porque llamo a dfs si no está marcado
   bool sol = true;
   // recorro todos los V por si el grafo no es conexto
   for (int i = 0; i < V; ++i) {
      if (colores[i] == 0) { // si es sin pintar, le llamo a dfs
         if (!dfs(g, i, colores, 1)) { // empiezo dfs con 1(azul)
            sol = false;
            break; // si hay conflicto, no sigue y para la busqueda
         }
      }
   }

   // escribir la solución
   if (sol) {
      cout << "SI\n";
   }
   else {
      cout << "NO\n";
   }
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
