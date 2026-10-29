
/*@ <authors>
 *
 * E27 Saneli Ghamari
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include "ConjuntosDisjuntos.h"

using namespace std;


/*@ <answer>
6.1

en manchas negras no modificaba el mapa(era const), por eso usar el 
codigo del ejercicio anterior sube mucho el coste y me dará time limit.

ConjuntosDisjuntos esta diseñada para agrupar elementos y mantener el 
tamaño de esos grupos de forma dinamica y en tiempo casi constante, 
gracias a la unión por tamaño y compresión de caminos.

la idea:
voy guardando cada casilla empezando de 0 como:
0 1 2
3 4 5
entonces para cada casilla el numero que le corresponde es f * C + c.


 el coste: O(F * C + N)
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>




// coste: O(F * C + N)
void resuelveCaso() {
    // arriba, abajo, izq, der y 4 diagonales
    const int df[] = { -1, -1, -1,  0, 0,  1, 1, 1 };
    const int dc[] = { -1,  0,  1, -1, 1, -1, 0, 1 };

    int F, C, N, f, c;
    cin >> F >> C;

    ConjuntosDisjuntos cd(F * C);
    int maxTam = 0;
    
    vector<string> mapa(F);
    // leer el mapa entero
    // coste: O(F)
    for (int i = 0; i < F; i++) {
        cin >> mapa[i];
    }

    // procesar
    // coste: O(F * C)
    for (int i = 0; i < F; i++) {
        for (int j = 0; j < C; j++) {
            if (mapa[i][j] == '#') { // es mancha
                maxTam = max(maxTam, 1); // si es una mancha de tam 1
                // 8 vecinos
                // coste: O(8)
                for (int d = 0; d < 8; d++) {
                    int fvecino = i + df[d];
                    int cvecino = j + dc[d];
                    // si el vecino está dentro del mapa y si es mancha
                    if (fvecino >= 0 && fvecino < F && cvecino >= 0 && cvecino < C 
                        && mapa[fvecino][cvecino] == '#') {

                        cd.unir(i * C + j, fvecino * C + cvecino);
                        maxTam = max(maxTam, cd.cardinal(i * C + j));
                    }
                }
            }
        }
    }

    // tam inicial
    cout << maxTam << " ";

    // coste: O(N)
    cin >> N;
    for (int k = 0; k < N; k++) {
        cin >> f >> c;
        f--;
        c--;
        mapa[f][c] = '#';
        maxTam = max(maxTam, 1); // asignarle tam 1

        // 8 vecinos
        for (int d = 0; d < 8; d++) {
            int fvecino = f + df[d];
            int cvecino = c + dc[d];

            if (fvecino >= 0 && fvecino < F && cvecino >= 0 && cvecino < C
                && mapa[fvecino][cvecino] == '#') {

                cd.unir(f * C + c, fvecino * C + cvecino);
                maxTam = max(maxTam, cd.cardinal(f * C + c));
            }
        }
        cout << maxTam << " ";
    }
    cout << "\n";
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
