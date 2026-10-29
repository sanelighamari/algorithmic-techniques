
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
2.3

tengo un struct para cada caja, guardo el tiempo(empezando 0 y sumandole 
el tiempo de cada cliente que le toca) y el numero de la caja.
tengo una cola de prioridad con las cajas, saco la caja que tiene el tiempo
menor y en el caso de igualdad la que tiene el numero menor.
 el coste: O((N + C)log N))
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Caja {
    int numero;
    int tiempo;

    // tiempo más pequeño sale primero
    // en el caso de igualdad de p vamos a numero
    bool operator<(const Caja& otro) const {
        return (tiempo > otro.tiempo ||
            (tiempo == otro.tiempo && numero > otro.numero));
    }
};


// coste: O(log(N))
void buscar_fila(priority_queue<Caja>& pq, int t) {
    // O(1) -> top()
    Caja c = pq.top();

    // O(log(N)) -> pop() / push()
    pq.pop();
        
    // actualizo su tiempo con el t
    c.tiempo += t;

    // le vuelvo a añadir para que lo saque otra vez
    pq.push(c);        
}

// coste: O((N + C)log N))
// cada push es logN
bool resuelveCaso() {
    priority_queue<Caja> pq;
    int N, C, t;

    // leer los datos de la entrada
    //cin >> N >> C;
    if (!(cin >> N >> C) || (N == 0 && C == 0)) return false;

    // coste: O(N(logN))
    for (int i = 1; i <= N; i++) {
        Caja c = { i, 0 };
        // O(log(N))
        pq.push(c);
    }

    // coste: O(C(logN))
    for (int i = 0; i < C; i++) {
        cin >> t;
        // O(log(N))
        buscar_fila(pq, t);
    }
    // resolver el caso posiblemente llamando a otras funciones
    // escribir la solución
    // O(1)
    cout << pq.top().numero << "\n";

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
