/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

/*@ <authors>
 *
 * E27 Saneli Ghamari
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

#include "TreeSet_AVL_tami.h"

/*@ <answer>
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 he añadido el elemento int tam_i en la struct TreeNode de Set en la clase reeSet_AVL_tami.h.
 he tenido que actualizar la constructora, inserta, roraDer y rotaIzq.
 he puesto el metodo kesimo(int k) en la parte publica para poder llamar a este metodo desde main.
 en kesimo(int k) llamo al metodo recursivo empezando en raiz.
 en kesimo_rec en el caso que existe voy comparando k con tam_i de raiz, y segun AVL descarto la
 mitad y voy a la izquierda o derecha(en este caso actualizo k). por eso el coste es logaritmo, 
 porque descarto la mitad y voy a la izquierda o la derecha(en el caso peor), en el caso mejor k 
 coincide con tam_i de raiz y ya esta.
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
// 
//@ <answer>

bool resuelveCaso() {
   int N;
   cin >> N;
   if (N == 0)
      return false;

   // los valores de la entrada se insertan en el conjunto
   Set<int> cjto;
   int valor;
   for (int i = 0; i < N; ++i) {
      cin >> valor;
      cjto.insert(valor);
   }

   // COMPLETAR
   int M;
   cin >> M;

   int k;
   for (int i = 0; i < M; ++i) {
       cin >> k;
       try {
           cout << cjto.kesimo(k) << "\n";

       }
       // excepcion porque el elemento no existe
       catch (out_of_range const& e) {
           cout << "??\n";
       }
   }

   cout << "---\n";

   return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
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

   while (resuelveCaso());

   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   cin.rdbuf(cinbuf);
#endif
   return 0;
}
