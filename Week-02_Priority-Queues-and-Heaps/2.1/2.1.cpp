
/*@ <authors>
 *
 * E27 Saneli Ghamari
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

/*@ <answer>

escribo un struct, Numero, como el ejemplo del video.
solo tengo un long long que es valor y el operator para facilitar.
está estructura me pone la cola de menor a mayor, 
ose que cuando hago top(), me da el minimo.
por esta caracteristica hago dos tops y tengo a y b los
dos más pequeños. así actualizo el esfuerzo. y añado la suma
de a y b a la cola para poder sumar con los demas, la suma va en orden.

coste: 


 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Numero {
    long long valor;

    bool operator<(const Numero& otro) const {
        return valor > otro.valor; 
    }
};

// O(N(log(N))) = (N-1)(2log(N))
long long esfuerzo(priority_queue<Numero>& pq) {
   long long esfuerzo = 0;

   // N-1 veces
   while (pq.size() > 1) {
      // O(1) -> top()
       long long a = pq.top().valor;
       // O(log(N)) -> pop() / push()
       pq.pop();

       long long b = pq.top().valor;
       pq.pop();

       long long suma = a + b;
       esfuerzo += suma;
       
       pq.push({suma});
   }
   
   return esfuerzo;
}

bool resuelveCaso() {
   priority_queue<Numero> pq;
   int N, num;
   // leer los datos de la entrada
   cin >> N;
   if (N == 0)
      return false;

   // resolver el caso posiblemente llamando a otras funciones
   // coste: O(N(log(N)))
   // cada push es logN y tengo bucle
   for (int i = 0; i < N; i++) {
      cin >> num;
      pq.push({num});
   }
   
   // escribir la solución
   cout << esfuerzo(pq) << endl;

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
