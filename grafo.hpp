#include <iostream>
#include "grafoint.hpp"
#include "vetorOrd.hpp"
#include "aux.hpp"
using namespace std;

#define NULLITEM -1
#define NULLKEY "NULL"

class Grafo{
    private:
        int k;
        vetorOrd<string,int> *st; // Tabela de símbolos
        GrafoInt *G; // Grafo de inteiros

    public:
    /* Inicializa um grafo com parâmetro k */
    Grafo(int k, string nome_arquivo): k(k)  {
        st = new vetorOrd<string, int>(k, nome_arquivo, NULLITEM, NULLKEY);
        G = new GrafoInt(st->nElem());

        // Insere todas as palavras presentes na tabela de símbolos
        for (int i = 0; i < st->nElem(); i++) {
            string s = st->getChave(i);
            insere(s);
        }
    }

    ~Grafo() {
        delete st;
        delete G;
    }

    int insere(string s) {
        /* Insere a palavra e retorna o número de arestas adicionados ao grafo,
        retorna -1 se a palavra já está no grafo ou tem tamanho menor que k*/
        int count = 0;
        int u = st->rank(s);

        for (int w = 0; w < st->nElem(); w++) {
            string t = st->getChave(w);
            if (u == w) continue; // ignora a comparação de uma palavra com ela mesma
            if (remocao(s, t) || trocaLetras(s, t) || substituicao(s, t)) {
                if(G->insertEdge(u, w))
                    count++;
            }
        }
        return count;
    }
    void print() { // imprime as palavras
        st->print();
    }
    void showGraph() { // imprime os vértices do grafo e os seus vizinhos
        G->show();
    }

    int vertices(){
        /* Retorna o número de vértices do grafo*/
        return G->vertices();
    }

    int arestas(){
        /* Retorna o número de arestas do grafo*/
        return G->arestas();
    }

    int componentes(){
        /* Retorna o número de componentes do grafo */
        return G->componentes();
    }

    bool conexo(){
        /* Retorna se o grafo é ou não conexo */
        return G->conexo();
    }

    int tamComp(string palavra){
        /* Retorna o tamanho da componente conexa onde está a palavra
        ou -1 caso ela não se encontre no grafo */
        int v = st->rank(palavra);
        return G->tamCompVertex(v);
    }

    int tamMenorComp(){
        return G->tamMinComp();
    }

    int tamMaiorComp(){
        return G->tamMaxComp();
    }

    double tamMedioComp(){
        return G->tamMedioComp();
    }

    double avgDegree(){
        return G->avgDegree2();
    }


    int dist(string a, string b){
        /* Retorna a menor distância entre as palavras a e b ou -1
        caso elas estejam desconexas ou não estejam no grafo */
        int u = st->rank(a);
        int v = st->rank(b);
        if (st->getChave(u) != a || st->getChave(v) != b)
            return -1;
        return G->dist(u, v);
    }

    bool emCiclo(string a){
        /* Retorna verdadeiro caso a palavra esteja em algum ciclo,
        falso caso contrário */
        int u = st->rank(a);
        if (st->getChave(u) != a)
            return false;
        return G->dfsCycle(u);
    }

    bool emCiclo(string a, string b){
        /* Retorna verdadeiro caso exista um ciclo que contenha ambas as palavras,
        falso caso contrário */
        int u = st->rank(a);
        int v = st->rank(b);
        if (st->getChave(u) != a || st->getChave(v) != b)
            return false;
        return G->dfsCycle2(u, v);
    }

    void exportPajek() {
        cout << "*vertices " << vertices() << endl;
        for (int i = 0; i < vertices(); i++)
            cout << i + 1 << " " << st->getChave(i) << endl;
        cout << "*edges" << endl;
        G->pajekPrintEdges();
    }

    string getChave(int v) {
        return st->getChave(v);
    }

};
