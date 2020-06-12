#include <iostream>
#include "grafo.hpp"

int main() {

    // int k = 3;
    cout << "Criando um grafo" << endl;
    Grafo *G = new Grafo(15);

    cout << "V: " << G->vertices() << endl;
    cout << "A: " << G->arcos() << endl;
    cout << "E: " << G->arestas() << endl << endl;

    int cnt = 0;
    cnt += G->insertEdge(0, 1);
    cnt += G->insertEdge(3, 1);
    cnt += G->insertEdge(0, 3);
    cnt += G->insertEdge(0, 2);
    cnt += G->insertEdge(4, 5);

    cnt += G->insertEdge(2, 7);
    cnt += G->insertEdge(7, 8);
    cnt += G->insertEdge(7, 9);
    cnt += G->insertEdge(1, 10);
    cnt += G->insertEdge(5, 11);
    cnt += G->insertEdge(5, 12);
    cnt += G->insertEdge(6, 13);
    G->show();

    cout << endl;
    cout << "V: " << G->vertices() << endl;
    cout << "A: " << G->arcos() << endl;
    cout << "E: " << G->arestas() << endl << endl;
    cout << "Contagem: " << cnt << endl;

    cout << "Grau médio dos vértices: " << G->avgDegree() << endl;
    cout << "Grau médio dos vértices 2: " << G->avgDegree2() << endl;

    cout << "Número de componentes conexas: " << G->componentes() << endl;

    cout << "O grafo é conexo? ";
    if (G->conexo()) cout << "Sim.";
    else cout << "Não.";
    cout << endl;

    cout << "Tamanho das componentes conexas" << endl;
    for (int i = 0; i < G->vertices(); i++) {
        cout << "\tTamanho da componente conexa de " << i << ": " << G->tamCompVertex(i) << endl;
    }

    cout << "Tamanho médio das componentes conexas: " << G->tamMedioComp() << endl;
    cout << endl;
    cout << "Tamanho da maior componente conexa: " << G->tamMaxComp() << endl;
    cout << "Tamanho da menor componente conexa: " << G->tamMinComp() << endl;



    cout << "dadas duas palavras a e b do dicionário, existe um caminho que liga a a b?" << endl;
    // cout << "\tDistância de " << 1 << " a " << 2 << ": " << G->dist(1, 2) << endl;
    for (int i = 0; i < G->vertices(); i++) {
        for (int j = 0; j < G->vertices(); j++) {
            if (i < j) {
                cout << "\tDistância de " << i << " a " << j << ": " << G->dist(i, j) << endl;
            }
        }
    }

    cout << "Tem ciclo passando pelo vértice?" << endl;
    // cout << "\tTem ciclo começando em " << 10 << ": " << G->dfsCycle(10) << endl;
    cout << "Tem ciclo passando pelo vértice?" << endl;
    for (int i = 0; i < G->vertices(); i++) {
        cout << "\tTem ciclo começando em " << i << ": " << G->dfsCycle(i) << endl;
    }

    cout << endl;
    cout << "Tem ciclo passando pelos vértices?" << endl;
    for (int i = 0; i < G->vertices(); i++) {
        for (int j = 0; j < G->vertices(); j++) {
            cout << "\tTem ciclo passando em " << i << " e " << j << ": " << G->dfsCycle2(i, j) << endl;
        }
    }

    delete G;

    return 0;
}
