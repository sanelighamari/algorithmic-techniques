
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

tengo struct Datos, tengo p(periodo) que es un valor fijo que me da al principio,
id y tiempo para saber en que momento estoy tras la vuelta(cuando quiero repetir 
los ids sé cuando le toca a cual, cada cuanto tiempo se repite). es como un
marcador de tiempo. sé cuando ha pasado y a quien toca segun lo que tiene menos
tiempo.
he hecho la funcion envios.
le doy la cola de ids con periodo añadido por orden de periodo
más pequeño, en el caso de igualdad id pequeño y K envios que
hay que hacer.
hago un bucle while(K--) k vueltas hasta que K llegue a 0.
por cada caso hago top(), el elemento menor y escribo su id por la pantalla.
actualizo el tiempo pasado(tiempo) con el periodo de este caso:
tiempo += periodo. y luego vuelvo a añadir este id a la cola pero con 
tiempo actualizado, asi que irá al final que todo porque tiene periodo
más grande que todo.
la función tiene coste: O(K(log(N)))

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Dato {
    long long id;
    int p;
    int tiempo;

    // p más pequeño sale primero
    // en el caso de igualdad de p vamos a id
    bool operator<(const Dato& otro) const {
        return (tiempo > otro.tiempo || 
         (tiempo == otro.tiempo && id > otro.id));
    }
};

// O(K(log(N))) = (K)(2log(N))
void envios(priority_queue<Dato>& pq, int K) {

   // N-1 veces
   while (K--) {
      // O(1) -> top()
      auto a = pq.top();
      // O(log(N)) -> pop() / push()
      pq.pop();
      // escribo el elemento con p menor que me ha salido
      cout << a.id << "\n";
      // actualizo su p con el tiempo pasado
      a.tiempo += a.p;
      // le vuelvo a añadir para que lo saque otra vez
      pq.push(a);
   }
   cout << "---\n";
}

bool resuelveCaso() {
   priority_queue<Dato> pq;
   int N, K, id, p;

   // leer los datos de la entrada
   cin >> N;
   if (N == 0) return false;

   // coste: O(N(log(N)))
   // cada push es logN y tengo bucle
   for (int i = 0; i < N; i++) {
      cin >> id;
      cin >> p;
      pq.push({id, p, p});
   }
   // numero de envios que hay que hacer
   cin >> K;
   // resolver el caso posiblemente llamando a otras funciones
   // escribir la solución
   envios(pq, K);

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
