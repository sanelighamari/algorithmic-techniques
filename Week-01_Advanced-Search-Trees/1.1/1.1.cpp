
/*@ <authors>
 *
 * E27 Saneli Ghamari
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "bintree.h"
using namespace std;


/*@ <answer>
1.1
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 quiero un arbol que:
 altura de hijo izq - altura hijo dr <= 1 && 
 valor de hijo izq < valor raiz && valor hijo dr > valor raiz
 para asegurarme que en el hijo izquierdo no hay algun hijo derecho mayor que la raiz
 guardo el valor min y max y si pasa de este ya sale false.
 luego al final comparo con el nodo actual y paso el valor(struct)
 para poder comparar con los demas otra vez luego.
 el coste: lineal O(n) porque tengo que mirar todos los elementos.
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

template <typename T>
struct Info {
    bool avl;
    int altura;
    T min;
    T max;
};


template <typename T>
Info<T> es_avl_aux(const BinTree<T>& tree) {
    if (tree.empty()) {
        return { true, 0, T(), T() };
        // lo importante es true, el resto da igual
    }

    auto izq = es_avl_aux(tree.left());
    auto der = es_avl_aux(tree.right());

    // condiciones:
    
    // es avl
    bool ok = izq.avl && der.avl && (abs(izq.altura - der.altura) <= 1);
    // si en la izquierda ya no hay mas, miro la condicion de no haber pasado de max
    if (!tree.left().empty() && izq.max >= tree.root()) {
        ok = false;
    }
    // si el derecho ya no hay más la condicion de no haber pasado de min
    if (!tree.right().empty() && der.min <= tree.root()) {
        ok = false;
    }

    // calcular para el nodo actual y pasarlo
    int alt = max(izq.altura, der.altura) + 1;
    T valor_min = tree.left().empty() ? tree.root() : izq.min; // raiz o lo que me dice el hijo
    T valor_max = tree.right().empty() ? tree.root() : der.max;

    return { ok, alt, valor_min, valor_max };
}

template <class T>
bool es_avl(const BinTree<T>& tree) {
    return es_avl_aux(tree).avl;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    string tipo;

    if (!(cin >> tipo)) {
        return false;
    }

    if (tipo == "N") {
        BinTree<int> tree;
        tree = read_tree<int>(cin);
        bool sol = es_avl(tree);
        cout << (sol ? "SI\n" : "NO\n");
    }
    else if (tipo == "P") {
        BinTree<string> tree;
        tree = read_tree<string>(cin);
        bool sol = es_avl(tree);
        cout << (sol ? "SI\n" : "NO\n");
    }

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
