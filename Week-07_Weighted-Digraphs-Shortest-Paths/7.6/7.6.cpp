
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

using namespace std;


/*@ <answer>
7.6

no uso grafo, en vez de esto uso na matriz(vector de vector int).
lo inicializo con la fatiga(dificultad) de cada posicion.
en Dijkstra tengo f y c como tam del tablero. otra matriz de 
dificultad y la cola de prioridad que guardo la ubicacion de cada 
elemento con la formula: i * C + j.
inicializo la matriz dificultad al valor de la casilla 0 y pongo 
el elemento de la casilla 0 0 en la cola con prioridad 0.
en el bucle saco el elemento de la cola y miro sus vecinos si 
cumplen la condicion actualizo el valor en vector dificultad y
actualizo prioridad(su dificultad) en la cola.


 el coste: O(4.F.C.log(F.C))
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

const int INF = 1e9;

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

// el coste: O(4.F.C.log(F.C))
void caminoMin(const vector<vector<int>>& mapa) {
   int f = mapa.size();
   int c = mapa[0].size();

   vector<vector<int>> dificultad(f, vector<int>(c, INF));
   // en cola pq: vertice, su dificultad segun la formula: i * C + j
   IndexPQ<int> pq(f * c);

   dificultad[0][0] = mapa[0][0];
   pq.push(0, mapa[0][0]);

   // O(N + (C logV))
   while(!pq.empty()) {
      // u = i * c + j
      int u = pq.top().elem;
      pq.pop();
      // sacar i y j
      int i = u / c;
      int j = u % c;
      
      for (int k = 0; k < 4; k++) {  // las dirs
         int iVecino = i + dr[k];
         int jVecino = j + dc[k];
         if (iVecino >= 0 && iVecino < f && jVecino >= 0 && jVecino < c) {
            int dificultadActual = mapa[iVecino][jVecino];
            if (max(dificultad[i][j], dificultadActual) < dificultad[iVecino][jVecino]) {
               dificultad[iVecino][jVecino] = max(dificultad[i][j], dificultadActual);
               pq.update(iVecino * c + jVecino, dificultad[iVecino][jVecino]);
            }
         }
      }
   }

   // escribir la solucion
   cout << dificultad[f - 1][c - 1] << "\n";
}

// coste: O(F + (C logN))
void resuelveCaso() {
   int F, C; // interseccion, calle
   cin >> F >> C;
   //DigrafoValorado<int> g(F*C);
   vector<vector<int>> mapa(F, vector<int>(C));

   // coste: O(C*F) = O(C) * O(F)
   for (int i = 0; i < F; i++) {
      for (int j = 0; j < C; j++) {
         cin >> mapa[i][j];
      }
   }

   // coste: O(4.F.C.log(F.C))
   caminoMin(mapa);
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
