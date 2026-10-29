
/*@ <authors>
 *
 * E27 Saneli Ghamari
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector> 
#include <functional> 
using namespace std;

/*@ <answer>

3.1

el coste: O(n(log(N)))

en cada bucle que va 2 en 2 hasta num_parejas, 
añado cada pajaro a la cola correspondiente(si es 
mayor que el primero va a mayores, que esta ordenado 
de mayor a menor, que .top() me da el elemento menor,
y si es menor que el primero va a menores que .top() de 
esta cola me da el mayor elemento). al añadir los dos 
pajaros miro si hace falta mover el pajaro primero, haciendo 
desplazamiento. y luego se que el mediano es el primero.
y lo escribo por la pantalla.


 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
   priority_queue<int> menores;
   priority_queue<int, vector<int>, greater<int>> mayores;
   int primero, num_parejas;
   int p1, p2;

   // leer los datos de la entrada
   cin >> primero >> num_parejas;
   if (primero == 0 && num_parejas == 0) return false;

   // considero parejas como N

   // coste: O(N(log(N)))
   // cada push es log(N) = log(N)
   // y tengo bucle de N
   for (int i = 0; i < num_parejas; i++) {
      cin >> p1 >> p2;

      // O(log(N) + log(N)) = O(log(N))
      if (p1 < primero) menores.push(p1);
      else mayores.push(p1);
      
      if (p2 < primero) menores.push(p2);
      else mayores.push(p2);
      

      if (menores.size() > mayores.size()) {
         // O(1)
         int aux = menores.top();
         // O(log(N) + log(N)) = O(log(N))
         menores.pop();
         // desplazamiento a la der
         mayores.push(primero);
         primero = aux;
      }
      else if (mayores.size() > menores.size()) {
         // O(1)
         int aux = mayores.top();
         // O(log(N) + log(N)) = O(log(N))
         mayores.pop();
         // desplazamiento a la izq
         menores.push(primero);
         primero = aux;
      }

      cout << primero << " ";
   }

   cout << "\n";

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
