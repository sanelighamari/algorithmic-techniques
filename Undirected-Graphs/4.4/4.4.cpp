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

4.4

inicializo el grafo.

cada fila es un string para ahorra en el coste, 
y luego leo cada posicion de este string como si 
fuese un vector también.

en dfs:
vector de visitado para no contar una casilla dos veces.
pasar F y C para comprobar la validez de f y c.
y la variable tam para actualizarlo dentro mientras que 
sigo con la misma mancha.
tiene coste lineal. en peor de los casos miro todas las casillas una vez.




el coste: O(F) + O(F + C) + O(1) = O(F + C)

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

// coste: O(F + C)
void dfs(vector<string> const& mapa, vector<vector<bool>>& visitado, 
      int f, int c, int F, int C, int& tam) {

   if (f >= F || f < 0 || c >= C || c < 0
      || mapa[f][c] == '-' || visitado[f][c]) {
         // no me vale esta casilla y sale
         return;
   }

   // me vale, actualizo
   visitado[f][c] = true;
   tam++;
   
   // llamo a los 4 vecinos (arriba, abajo, izquierda, derecha)
   dfs(mapa, visitado, f - 1, c, F, C, tam); // arriba
   dfs(mapa, visitado, f + 1, c, F, C, tam); // abajo
   dfs(mapa, visitado, f, c - 1, F, C, tam); // izquierda
   dfs(mapa, visitado, f, c + 1, F, C, tam); // derecha
}

void resuelveCaso() {
   int F, C;
   cin >> F >> C;

   vector<string> mapa(F);
   vector<vector<bool>> visitado(F, vector<bool>(C, false));

   // el coste: O(F)
   // leer el mapa
   for (int i = 0; i < F; i++) {
      cin >> mapa[i];
   }

   int cont = 0;
   int tamMax = 0;

   // el coste: O(F + C) 
   // tengo que mirar todas las casillas si o si, pero solo una vez.

   // tratar cada caso con dfs si cumple las condiciones y
   // actualizar los datos
   for (int i = 0; i < F; i++) {
      for (int j = 0; j < C; j++) {
         // no entro a dfs si la casillaes blanca o ya está visitada
         if (!visitado[i][j] && mapa[i][j] == '#') {
            int tam = 0;
            dfs(mapa, visitado, i, j, F, C, tam);

            if (tam > tamMax) tamMax = tam;
            // si cumple if y es una mancha con tam >= 1 me vale
            if(tam > 0) cont++;
         }
      }
      
   }

   // escribir la solución
   cout << cont << " " << tamMax << "\n";
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
