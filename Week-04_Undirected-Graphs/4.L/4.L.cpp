/*@ <authors>
 *
 * E27 Saneli Ghamari
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

#include "Grafo.h"

/*@ <answer>

4.L

inicializo el grafo

el objetivo es encontrar lo que tarda Alex hasta el punto de encuentro + 
lo que tarda Lucas al punto de encuentro + desde el punto de encuentro
hasta trabajo.
llamo a bfs separado para cada uno para tener un vector ordenado de los 
vecinos(intersec.) a distancia 1 del inicio(Alex, Lucas y Trabajo).
necesito bfs porque mi prioridad es distancia desde el inicio. miro 
todos los vecinos a distancia 1.
Luego un bucle de N intersecciones, para cada interseccion segun mis 
tres vectores calculo el coste del camino, lo voy comparando con el 
coste optimo, y escribo el coste optimo por la pantalla.


el coste total: O(C(N + C)) + O(N + C) + O(N) = O(C(N + C))

el coste de tratar el caso(sin contar la inicialización
el grafo): O(N + C)

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

// coste: O(N + C)
vector<int> bfs(Grafo const& g, int inicio) {
   
   // vector de distancia(donde -1 es no visitado)
   vector<int> dist(g.V(), -1);
   queue<int> q;

   dist[inicio] = 0;
   q.push(inicio);

   while (!q.empty()) {
      int v = q.front();
      q.pop();

      for (int w : g.ady(v)) {
         // si aun no he visto w
         if (dist[w] == -1) {
            // su distancia = distancia del padre + 1
            dist[w] = dist[v] + 1;
            q.push(w); // lo saco para mirar sus adyacentes
         }
      }
   }
   return dist;
}

void resuelveCaso() {
   // num interseccion
   // num tramo de calle
   // intersec. Alex
   // intersec. Lucas
   // intersec. trabajo
   int N, C, A, L, T;
   cin >> N >> C >> A >> L >> T;
   A--;
   L--;
   T--;

   // inicializo la lista con num interseccion
   Grafo g = Grafo(N);

   // el coste: O(C(N + C))
   int u, v;
   for (int i = 0; i < C; i++) {
      cin >> u >> v;
      g.ponArista(u - 1, v - 1); // -1 porque g esta desde 0
   }

   // el coste: 3 * O(N + C) = O(N + C)
   // tengo tres vectores ordenando los vecinos 
   //por distancia de cada punto.
   vector<int> distA = bfs(g, A);
   vector<int> distL = bfs(g, L);
   vector<int> distT = bfs(g, T);

   int coste_minimo = 1e9; // un valor muy alto
   // el coste: O(N)
   // voy de intersecccion a interseccion para ver 
   // la suma de cual me da el coste optima.
   for (int v = 0; v < N; ++v) {
      int coste_v = distA[v] + distL[v] + distT[v];
      
      if (coste_v < coste_minimo) {
         coste_minimo = coste_v;
      }
   }

   // Escribir la solución
   cout << coste_minimo << "\n";
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
