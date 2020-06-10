#include <iostream>
#include "grafo.hpp"

int main() {

    int k = 3;
    cout << "Criando um grafo" << endl;
    Grafo *G = new Grafo(k);

    cout << "V: " << G->vertices() << endl;
    cout << "A: " << G->arcos() << endl;
    cout << "E: " << G->arestas() << endl;

    return 0;
}
