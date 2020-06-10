#ifndef GRAFO_HPP
#define GRAFO_HPP
using namespace std;

#define INITIAL_SIZE 4

/*
    ./ep2 nome_arquivo k
        -> modo pré-definido
        -> inserir na ST apenas as palavras necessárias
        -> não incluir números
    ./ep2 texto.txt 10
*/
class node {
    public:
        typedef node *link;
        link NEWnode(int w, link next);
        int w;
        node *next;
};

typedef node *link;
link node::NEWnode(int w, link next) {
    link a = new node;
    a->w = w;
    a->next = next;
    return a;
}

class Grafo {
    public:
        Grafo(int k); // cria um grafo com as palavras com pelo menos k letras de um dicionário
        int vertices();
        int arestas();
        int arcos(); // remover
    private:
        // typedef node *link;
        int V;
        int A; // arestas
        int E; // arcos
        int size; // tamanho do vetor de adjacências
        link *adj;
        void insertArc(int v, int w);
        void insertEdge(int v, int w);
};


Grafo::Grafo(int k): V(0), A(0), E(0), size(INITIAL_SIZE), adj(new link[INITIAL_SIZE])
{

}

int Grafo::vertices() {
    return V;
}

int Grafo::arestas() {
    return E;
}

int Grafo::arcos() {
    return A;
}

void Grafo::insertArc(int v, int w) {
    for (link a = adj[v]; a != nullptr; a = a->next)
       if (a->w == w) return;
    adj[v] = node::NEWnode(w, adj[v]);
    A++;
}

void Grafo::insertEdge(int v, int w) {
    insertArc(v, w);
    insertArc(w, v);
    E++;
}

#endif
