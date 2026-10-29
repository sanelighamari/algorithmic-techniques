
/*@ <authors>
 *
 * E27 Saneli Ghamari
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include "Digrafo.h"

using namespace std;


/*@ <answer>
5.3


me hace falta otro vector a parte de visitado porque si no cuando 
llego a un vertice por la segunda vez(llego a 2 de 1 y también de 
0) detecta un ciclo y sale del bucle aunque no hay ciclo.
así que tengo vector visitados para no repetir mirando vertices,
y el vector apilado para distinguir ciclos, de forma que si algun
vecino del vertice que estooy en su dfs tiene apilado true(estoy 
en su dfs también) significa que hay ciclo y break.
necesito una pila porque se acaba al reves que pongo, FILO.

 el coste: O(V + A) = O(A) + O(V + A)
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


// coste: O(V + A) es constante
// dfs porque no me importa si tardo más o paso del sitio repetido
bool dfs(Digrafo const& g, int v, vector<bool>& visitados, vector<bool>& apilados, 
                                deque<int>& orden) {
    visitados[v] = true;
    apilados[v] = true;

    for (int w : g.ady(v)) {
        if (!visitados[w]) {
            if (dfs(g, w, visitados, apilados, orden)) { // hay ciclo
                return true; // hay ciclo
            }

        }
        else if (apilados[w]) {
            return true; // hay ciclo
        }
    }

    apilados[v] = false;
    orden.push_front(v);

    return false; // sin ciclo
}

// coste: O(V + A)
void resuelveCaso() {
    int V, A, origen, destino, Q;
    cin >> V >> A;

    Digrafo g(V);
    // coste: O(A)
    for (int i = 0; i < A; i++) {
        cin >> origen >> destino;
        origen--;
        destino--;

        g.ponArista(origen, destino);
    }
    
    vector<bool> visitados(V, false);
    vector<bool> apilados(V, false);
    deque<int> orden;
    bool hayCiclo = false;

    // coste: O(V + A)
    // lanzamr el dfs desde cada vertice no visitado asi que 
    // se ve cada vertice solo una vez y el coste es lineal.
    for (int v = 0; v < V; v++) {
        if (!visitados[v]) {
            if (dfs(g, v, visitados, apilados, orden)) {
                hayCiclo = true;
                break; // hay ciclo
            }
        }
    }


    if (hayCiclo) {
        cout << "Imposible\n";
    }
    else {
        for (int v : orden) { // vertices de la pila
            cout << v + 1 << " ";
        }
        cout << "\n";
    }
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
    // entrada/salida rápida
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ajustes para que cin extraiga directamente de un fichero (solamente en local)
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
