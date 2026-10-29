
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

2.4

el coste: O(n(log(N)))

struct de paciente con nombre y gravedad.
en cada caso si es I añado el paciento a la cola y ya,
si es A voy a atender y allí saco de la lista, el que
tiene prioridad(el que tiene gravedad más alto), lo escribo 
por la pantalla y ya está.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Paciente {
   string nombre;
    int gravedad;
    int turno;

    // gravedad más grande sale primero
    // en el caso de igualdad el que ha esperado más
    bool operator<(const Paciente& otro) const {
        return (gravedad < otro.gravedad ||
         (gravedad == otro.gravedad && turno > otro.turno));
    }
};

// O(log(N))
void atender(priority_queue<Paciente>& pq) {
   // O(1) -> top()
   auto a = pq.top();
   // O(log(N)) -> pop() / push()
   pq.pop();

   // escribir su nombre
   cout << a.nombre << "\n";
   
}

bool resuelveCaso() {
   priority_queue<Paciente> pq;
   int n, gravedad;
   char accion;
   string nombre;

   // leer los datos de la entrada
   cin >> n;
   if (n == 0) return false;

   // coste: O(n(log(N)))
   // cada push es logN o si va a atender tambien logN 
   // y tengo bucle de n
   for (int i = 0; i < n; i++) {
      cin >> accion;
      if (accion == 'A') {
         atender(pq);
      }
      else {
         cin >> nombre;
         cin >> gravedad;
         pq.push({nombre, gravedad, i});
      }
      
   }
   // resolver el caso posiblemente llamando a otras funciones
   // escribir la solución
   // se acabaron los casos
   cout << "---\n";

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
