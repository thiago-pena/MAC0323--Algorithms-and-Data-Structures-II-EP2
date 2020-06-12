#ifndef GRAFO_HPP
#define GRAFO_HPP
#include "fila.hpp"
using namespace std;

#define INITIAL_SIZE 7

/*
    ./ep2 nome_arquivo k
        -> modo pré-definido
        -> inserir na ST apenas as palavras necessárias
        -> não incluir números
    ./ep2 texto.txt 10
*/

class Grafo {
    public:
        Grafo(int k); // cria um grafo com as palavras com pelo menos k letras de um dicionário
        int vertices();
        int arestas();
        int arcos(); // remover
        void show();
        bool insertEdge(int v, int w);
        double avgDegree();
        double avgDegree2();
        bool conexo();
        int componentes();
        int tamCompVertex(int v);
        double tamMedioComp();
        int tamMaxComp();
        int tamMinComp();
        int dist(int v, int w);
        bool dfsCycle(int v);
        void bfs(); // tornar private
    private:
        struct node {
            int w;
            node *next;
        };
        int V;
        int A; // arestas
        int E; // arcos
        int size; // tamanho do vetor de adjacências
        node **adj;
        bool insertArc(int v, int w);
        int * degree();
        void dfsR(int v, bool *marked);
        void bfsVertex(int v, int *dist);
        bool dfsRcycle(int u, bool *marked, int *pred);
};


Grafo::Grafo(int k): V(INITIAL_SIZE), A(0), E(0), size(INITIAL_SIZE), adj(new node * [INITIAL_SIZE])
{

}

void Grafo::show() {
    for (int v = 0; v < V; v++) {
        cout << v << ":";
    for (node *a = adj[v]; a != nullptr; a = a->next)
        cout << " " << a->w;
    cout << endl;
    }
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

// Insere o arco v-w, se ainda não existir.
// Retorna true se o arco foi criado e false caso contrário.
bool Grafo::insertArc(int v, int w) {
    for (node *a = adj[v]; a != nullptr; a = a->next)
       if (a->w == w) return false;
    node *novo = new node;
    novo->w = w;
    novo->next = adj[v];
    adj[v] = novo;
    A++;
    return true;
}

// Insere a aresta v-w, caso ainda não exista
// Retorna true se a aresta foi criada e false caso contrário.
bool Grafo::insertEdge(int v, int w) {
    if (insertArc(v, w)) {
        insertArc(w, v);
        E++;
        return true;
    }
}

// Retorna um vetor com o grau de cada vértice
int * Grafo::degree() {
    int *deg = new int[V];
    for (int v = 0; v < V; v++) {
        int count = 0;
        for (node *a = adj[v]; a != nullptr; a = a->next) {
            count++;
        }
        deg[v] = count;
    }
    return deg;
}

// Retorna o grau médio dos vértices de um grafo
double Grafo::avgDegree() {
    int count = 0;
    for (int v = 0; v < V; v++) {
        for (node *a = adj[v]; a != nullptr; a = a->next) {
            count++;
        }
    }
    return (double) count/V;
}

// Retorna o grau médio dos vértices de um grafo
double Grafo::avgDegree2() {
    return (double) 2*E/V;
}

/* Retorna o número de componentes do grafo */
int Grafo::componentes() {
    int comp = 0;
    bool *marked = new bool[V];
    for (int v = 0; v < V; v++)
        marked[v] = false;
    for (int v = 0; v < V; v++)
        if (!marked[v]) {
            comp++;
            dfsR(v, marked);
        }
    delete [] marked;
    return comp;
}

void Grafo::dfsR(int v, bool *marked) {
    marked[v] = true;
    for (node *a = adj[v]; a != nullptr; a = a->next) {
        int w = a->w;
        if (!marked[w])
            dfsR(w, marked);
    }
}


/* Retorna verdadeiro caso o vértice v esteja em algum ciclo,
falso caso contrário */
bool Grafo::dfsCycle(int v) {
    bool *marked = new bool[V];
    int *pred = new int[V];
    bool temCiclo;

    for (int v = 0; v < V; v++) {
        marked[v] = false;
        pred[v] = -1;
    }
    pred[v] = v;
    temCiclo = dfsRcycle(v, marked, pred);
    delete [] marked;
    delete [] pred;
    return temCiclo;
}

bool Grafo::dfsRcycle(int u, bool *marked, int *pred) {
    marked[u] = true;
    for (node *a = adj[u]; a != nullptr; a = a->next) {
        int w = a->w;
        if (!marked[w]) {
            pred[w] = u;
            if(dfsRcycle(w, marked, pred)) return true;
        }
        else if (pred[w] == w && pred[w] != u) // Chegou no primeiro vértice e não é o caminho de volta
            return true;
    }
    return false;
}

/* Retorna verdadeiro caso o vértice a e o v esteja em algum ciclo,
falso caso contrário */
/* Retorna verdadeiro caso exista um ciclo que contenha os vértices x e y,
falso caso contrário */
bool Grafo::dfsCycle2(int x, int y) {
    bool *marked = new bool[V];
    int *pred = new int[V];
    bool temCiclo;

    // calcula o caminho mínimo (BFS)
        // se não há caminho -> FALSE


    // usa DFS para tentar encontrar um novo caminho diferente

    for (int x = 0; x < V; x++) {
        marked[x] = false;
        pred[x] = -1;
    }
    pred[x] = x;
    temCiclo = dfsRcycle(x, marked, pred);
    delete [] marked;
    delete [] pred;
    return temCiclo;
}

bool Grafo::dfsRcycle2(int u, bool *marked, int *pred) {
    marked[u] = true;
    for (node *a = adj[u]; a != nullptr; a = a->next) {
        int w = a->w;
        if (!marked[w]) {
            pred[w] = u;
            if(dfsRcycle(w, marked, pred)) return true;
        }
        else if (pred[w] == w && pred[w] != u) // Chegou no primeiro vértice e não é o caminho de volta
            return true;
    }
    return false;
}

/* Retorna se o grafo é ou não conexo */
bool Grafo::conexo() {
    int comp = componentes();
    return comp == 1;
}

/* Retorna o tamanho da componente conexa onde está o vértice
ou -1 caso ele não se encontre no grafo */
int Grafo::tamCompVertex(int v) {
    if (v < 0 || v >= V) return -1;
    int tamComp = 0;
    bool *marked = new bool[V];
    for (int v = 0; v < V; v++)
        marked[v] = false;
    if (!marked[v])
        dfsR(v, marked);
    for (int i = 0; i < V; i++)
        if (marked[i]) tamComp++;
    delete [] marked;
    return tamComp;
}

/* Retorna o tamanho médio das componentes */
double Grafo::tamMedioComp() {
    // return (double) 1.0*V/(1.0*componentes());
    return (double) V/componentes();
}

// Retorna o tamanho da maior componente do grafo;
int Grafo::tamMaxComp() {
    int ans = 0;
    for (int v = 0; v < V; v++) {
        int tam = tamCompVertex(v);
        if (tam > ans) ans = tam;
    }
    return ans;
}

// Retorna o tamanho da menor componente do grafo;
int Grafo::tamMinComp() {
    int ans = V;
    for (int v = 0; v < V; v++) {
        int tam = tamCompVertex(v);
        if (tam < ans) ans = tam;
    }
    return ans;
}

/* Retorna a menor distância entre os vértices v e w ou -1
caso os vértices sejam desconexos ou não estejam no grafo */
int Grafo::dist(int v, int w) {
    if (v < 0 || v > V || w < 0 || w >  V) return -1;
    int *distArr = new int(V);
    bfsVertex(v, distArr);
    int distancia = distArr[w];
    delete [] distArr;
    return distancia;
}


void Grafo::bfsVertex(int v, int *dist) {
    int d = 0;
    // Fila<int> fila = new Fila<int>(V);
    Fila<int> fila = Fila<int>(V);
    for (int i = 0; i < V; i++) dist[i] = -1;

    fila.insere(v);
    dist[v] = d;
    while (!fila.vazia()) {
        int u = fila.remove();
        d++;
        for (node *a = adj[u]; a != nullptr; a = a->next) { // poderia usar int i sem problema pois teria escopo apenas no for
            int w = a->w;
            if (dist[w] == -1) {
                fila.insere(w);
                dist[w] = d;
            }
        }
    }
    // Como destruir a fila? @@@
}

void Grafo::bfs() {
    bool *marked = new bool[V];
    int d = 0;

    // for (int i = 0; i < V; i++) dist[i] = -1;

    // Fila<int> fila = new Fila<int>(V);
    Fila<int> fila = Fila<int>(V);
    for (int i = 0; i < V; i++) marked[i] = false;

    for (int i = 0; i < V; i++)
        if (!marked[i]) {
            fila.insere(i);
            marked[i] = true; // marca ao inserir na fila para que cada v entre exatamente uma vez na fila
            while (!fila.vazia()) {
                int u = fila.remove();
                d++;
                for (node *a = adj[u]; a != nullptr; a = a->next) { // poderia usar int i sem problema pois teria escopo apenas no for
                    int w = a->w;
                    if (!marked[w]) {
                        fila.insere(w);
                        marked[w] = true;
                    }
                }
            }
        }
    delete [] marked;
    // Como destruir a fila? @@@
    return;
}

#endif
