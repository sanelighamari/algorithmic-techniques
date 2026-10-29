/*@ <authors>
 *
 * E27 Saneli Ghamari
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

#include "IndexPQ.h"

/*@ <answer>

3.L


tengo una cola que su prioridad es su audiencia.
añado los casos de minuto 0, luego en cada cambio actualizo la cola.


 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

// tiempo descendente, y si son iguales por id del canal ascendente
bool comp(const pair<long long, int>& a, const pair<long long, int>& b) {
    if (a.first != b.first) return a.first > b.first;
    return a.second < b.second;
}

void resuelveCaso() {
   // D minutos, C canales, N actualizaciones
   int D, C, N;
   cin >> D >> C >> N;

   // .top() tiene el elemento mayor
   IndexPQ<int, std::greater<int>> pq(C + 1);

   // 
   vector<long long> tiempo_lider(C + 1, 0);

   // O(Clog(C))
   // minuto 0 (inicializar)
   for (int i = 1; i <= C; i++) {
      int audiencia;
      cin >> audiencia;
      // log(C)
      pq.push(i, audiencia); // canal i con su prioridad
   }

   long long tiempo_actual = 0;


   // N cambios
   for (int i = 0; i < N; i++) { // N cambios
      long long min;
      int num, canal, valor_nuevo;
      cin >> min >> num;

      // tiempo pasado y sumarlo
      int lider = pq.top().elem;
      tiempo_lider[lider] += (min - tiempo_actual);

      // actualizar el reloj(tiempo actual)
      tiempo_actual = min;

      for (int j = 0; j < num; j++) {
         cin >> canal >> valor_nuevo;
         // actualizar
         pq.update(canal, valor_nuevo);
      }
   }

   // actualizar el tiempo desde el último evento hasta final
   int lider_fin = pq.top().elem;
   tiempo_lider[lider_fin] += (D - tiempo_actual);

   // solo los canales que mayor 0 min(lider)
   vector<pair<long long, int>> resultados;
   for (int i = 1; i <= C; i++) {
      if (tiempo_lider[i] > 0) {
         resultados.push_back({tiempo_lider[i], i});
      }
   }

   // O(n(log(n))) n es num canales en lider
   // ordenar
   sort(resultados.begin(), resultados.end(), comp);

   // escribir la solución
   for (const auto& r : resultados) {
      cout << r.second << " " << r.first << "\n";
   }

   cout << "---\n";
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
