
/*@ <authors>
 *
 * E27 Saneli Ghamari
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;


/*@ <answer>
5.5

hay que usar bfs porque voy mirando nivel por nivel(distancia 1, 2 y...).
no uso Digrafo, uso un vector siguiente que guardo desde qué pos hay algo
(escalera o serpiente) para moverse a qué pos(que guardo como valor en el 
vector siguiente).
miro todos los numeros posibles de cara para moverse y a ver dónde se cae
(como los adyacentes).
para cada casilla probable calculo donde cae si hay S o E o si no hay, luego
le añado a la cola para que en la ronda siguiente calcule la casilla siguiente 
de esta.


 el coste: O(N * N + S + E) = O(S + E) + O(S +E) + O(N * N + S + E)
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


// coste: O(N * N + S + E) es lineal
// bfs(anchura) porque voy mirando con distancia
int bfs(int N, int K, const vector<int>& siguiente) {
   int V = N * N;
   vector<int> distancia(V, -1); // no visitado es -1
   queue<int> cola;

   distancia[0] = 0;
   cola.push(0);

   while(!cola.empty()) {
      int v = cola.front();
      cola.pop();

      // caso base, si hemos llegado a la ultima casilla
      if (v == V - 1) {
         return distancia[v];
      }

      // probar todas las caras posibles (de 1 a K)
      for (int d = 1; d <= K; d++) {
         int posSig = v + d;
         
         if (posSig < V) { // para no pasar el limite(el tablero)
            int destino = siguiente[posSig]; // si hay E o S avanza si no apunta a si misma

            if (distancia[destino] == -1) { // si no he visitad esta casilla
               distancia[destino] = distancia[v] + 1; // es como cont++ (lo que me ha costado hasta ahora)
               cola.push(destino); // vuelve a la cola para poder avanzar
            }
         }
      }
   }


   return -1; // 
}

// coste: O(N * N + S + E)
void resuelveCaso() {
   int N, K, S, E, i, j;
   cin >> N >> K >> S >> E;

   int V = N * N;
   // coste: O(N * N) = O(V)
   // vector auxiliar(siguiente) para saber a donde lleva S o E
   // cada casilla (lo inicializo a la misma casilla)
   vector<int> siguiente(V);
   for (int i = 0; i < V; i++) {
      siguiente[i] = i;
   }

   // coste: O(S + E)
   // leer serpientes y escaleras (guardamos en base 0 restando 1)
   for (int k = 0; k < S + E; k++) {
      cin >> i >> j;
      siguiente[i - 1] = j - 1;
   }
    
   // coste: O(N * N + S + E)
   int sol = bfs(N, K, siguiente);

   cout << sol << "\n";
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
