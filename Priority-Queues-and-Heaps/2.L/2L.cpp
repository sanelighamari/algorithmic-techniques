
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
2.L

el coste: O(p-n(log(N)))

la idea es tener un struct para cada instrumento,
dentro tengo numero de partituras que he dedicado para 
cada instrumento(empezando 1), numero de personas para
cada partitura(empezando numero de personas total dde cada 
instrumento) y el num total de personas(el del enunciado).
tengo una cola de prioridad de instrumentos que el primer 
elemento para sacar es cual tiene mas personas.
tengo una funcion de dividir las partituras, voy sacando de 
la cola cual instrumento que tiene mas prioridad(mas personas), 
y le dedico otra partitura, repito el proceso p-n veces.
luego tengo que actualilzar cada instrumento que le he dedicado
una partitura.
y alfinal escribir personas del elemento con prioridad de la lista.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Instrumento {
    int num_p;
    int total_personas;
    int personas;

    // más personas sale primero
    bool operator<(const Instrumento& otro) const {
        return (personas < otro.personas);
    }
};

// O(p-n(log(N)))
void dividir_p(priority_queue<Instrumento>& pq, int p) {

   // p-n veces
   while (p--) {
      // O(1) -> top()
      auto a = pq.top();
      // O(log(N)) -> pop() / push()
      pq.pop();

      // actualizo su p_num y personas
      a.num_p++;

      // de nuevo miro personas totales
      // ejemplo: 
      // 20/3 tengo aux=6 y resto=1 asi que mi resultado es 6+1
      int aux = a.total_personas / a.num_p;
      int resto = a.total_personas % a.num_p;

      a.personas = (resto > 0) ? aux + 1 : aux;

      //a.personas = (a.total_personas + a.num_p - 1) / a.num_p;

      // le vuelvo a añadir para que lo saque otra vez
      pq.push(a);
   }
}

bool resuelveCaso() {
   priority_queue<Instrumento> pq;
   int p, n, num_personas;

   // leer los datos de la entrada
   cin >> p >> n;

   // coste: O(N(log(N)))
   // cada push es logN y tengo bucle
   for (int i = 1; i <= n; i++) {
      cin >> num_personas;
      // siempre hay 1
      // O(logN)
      pq.push({1,num_personas, num_personas});
   }
   // resolver el caso posiblemente llamando a otras funciones
   // le paso p-n porque ya he asignado un p para cada instrumento(n)
   // O(p-n(log(N)))
   dividir_p(pq, p-n);

   // escribir la solución
   cout << pq.top().personas << "\n";

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
