
/*@ <authors>
 *
 * E27 Saneli Ghamari
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include "Digrafo.h"

using namespace std;


/*@ <answer>
5.4

hay que hacer un bfs dando valor y mirar si lo que está arriba es 
menor de lo que está abajo(la flecha de arriba a abajo). 
intento sacar el orden topológico con dfs como que x1<x2 es x1->x2.
si hay ciclo no puedo sacar ningun desigualdad por ejemplo x1->x2->x1
que es x1 < x2 < x1 que es imposible.

 el coste: O(N + M) = O(M) + O(N + M)
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


// coste: O(N + M) es lineal
// dfs porque no me importa si tardo más o paso del sitio repetido
bool dfs(Digrafo const& g, int v, vector<bool>& visitados, vector<bool>& apilados, 
                              deque<int>& orden) {
   visitados[v] = true;
   apilados[v] = true;

   for (int w : g.ady(v)) {
      if (!visitados[w]) {
         if (dfs(g, w, visitados, apilados, orden)) { // hay ciclo
            return true; // hay ciclo
         }

      }
      else if (apilados[w]) {
         return true; // hay ciclo
      }
   }

   apilados[v] = false;
   orden.push_front(v);

   return false; // sin ciclo
}

// coste: O(N + M)
void resuelveCaso() {
   int N, M, i, j;
   cin >> N >> M;

   Digrafo g(N);
   // coste: O(M)
   for (int k = 0; k < M; k++) {
      cin >> i >> j;
      i--;
      j--;

      g.ponArista(i, j);
   }
    
   vector<bool> visitados(N, false);
   vector<bool> apilados(N, false);
   deque<int> orden;
   bool hayCiclo = false;

   // coste: O(N + M)
   // lanzamr el dfs desde cada vertice no visitado asi que 
   // se ve cada vertice solo una vez y el coste es lineal.
   for (int n = 0; n < N; n++) {
      if (!visitados[n]) {
         if (dfs(g, n, visitados, apilados, orden)) {
            hayCiclo = true;
            break; // hay ciclo
         }
      }
   }

   if (hayCiclo) {
      cout << "NO\n";
   } 
   else {
      // hace falta dos bucles porque no quiero escribir todos de 1 a 5, 
      // quiero escribir los valores de la ordenación de la cola(orden).
      vector<int> valores(N);
      int valor_actual = 1;

      for (int v : orden) {
         valores[v] = valor_actual;
         valor_actual++;
      }

      cout << "SI";
      for (int k = 0; k < N; k++) {
         cout << " " << valores[k];
      }
      cout << "\n";
   }
   

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
