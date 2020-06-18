#include <iostream>
#include <climits>
#include "grafo.hpp"
using namespace std;

#define PRINT_TO_PAJEK false
#define PRINT_EP2 true
#define LIMITE 100

int main(int argc, char *argv[]) {

    string nome_arquivo = argv[1];
    int k = atoi(argv[2]);
    //string nome_arquivo = "exemplos.txt";
    // int k = 2;

    Grafo *G = new Grafo(k, nome_arquivo);

    if (PRINT_EP2) {
        cout << "Número de vértices: " << G->vertices() << endl;
        cout << "Número de arestas: " << G->arestas() << endl << endl;

        cout << "Número de componentes conexas: " << G->componentes() << endl;
        cout << "O grafo é conexo? " << G->conexo() << endl;
        cout << "Tamanho da menor componente conexa: " << G->tamMenorComp() << endl;
        cout << "Tamanho da maior componente conexa: " << G->tamMaiorComp() << endl;
        cout << "Tamanho médio das componentes conexas: " << G->tamMedioComp() << endl;
        cout << "Grau médio dos vértices: " << G->avgDegree() << endl << endl;

        cout << "Tamanho da componente conexa de uma palavra (casos maiores que 1)" << endl;
        int cnt = 0;
        for (int i = 0; i < G->vertices() && cnt < LIMITE; i++) {
            string s = G->getChave(i);
            int tam = G->tamComp(s);
            if (tam > 1) {
                cout << "\t" << s << ": " << tam << endl;
                cnt++;
            }
        }
        cout << endl;
        cout << "Distância entre palavras que estão na mesma componente conexa" << endl;
        cnt = 0;
        for (int i = 0; i < G->vertices() - 1 ; i++) {
            for (int j = i; j < G->vertices() && cnt < LIMITE; j++) {
                string s = G->getChave(i);
                string t = G->getChave(j);
                int d = G->dist(s, t);
                if (d > 0) {
                    cout << "\tdist(" << s << ", " << t << "): " << G->dist(s, t) << endl;
                    cnt++;
                }
            }
        }
        cout << endl;
        cout << "Palavras que estão em um ciclo" << endl;
        cnt = 0;
        for (int i = 0; i < G->vertices() && cnt < LIMITE; i++) {
            string s = G->getChave(i);
            if (G->emCiclo(s)) {
                cout << "\t" << s << endl;
                cnt++;
            }

        }
        cout << endl;
        cout << "Duplas de palavras que estão em um ciclo" << endl;
        cnt = 0;
        for (int i = 0; i < G->vertices() - 1; i++) {
            for (int j = i; j < G->vertices() && cnt < LIMITE; j++) {
                string s = G->getChave(i);
                string t = G->getChave(j);
                if (G->emCiclo(s, t)) {
                    cout << "\t" << s << ", " << t << endl;
                    cnt++;
                }
            }
        }
        cout << endl;
    }


    if (PRINT_TO_PAJEK) G->exportPajek();

    delete G;

}
