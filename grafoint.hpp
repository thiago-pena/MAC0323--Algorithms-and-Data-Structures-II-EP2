#ifndef GRAFOINT_HPP
#define GRAFOINT_HPP
#include "fila.hpp"
using namespace std;

class GrafoInt {
    public:
        GrafoInt(int V);
        ~GrafoInt();
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
        bool dfsCycle2(int x, int y);
        void bfs();
        void pajekPrintEdges();
    private:
        struct node {
            int w;
            node *next;
        };
        int V;
        int A; // arestas
        int E; // arcos
        node **adj;
        bool insertArc(int v, int w);
        int * degree();
        void dfsR(int v, bool *marked);
        void bfsVertex(int v, int *dist, int *pred);
        bool dfsRcycle(int u, bool *marked, int *pred);
        void bfsVertex2(int v, int *dists, int *pred);
};


GrafoInt::GrafoInt(int V): V(V), A(0), E(0), adj(new node * [V])
{
    for (int i = 0; i < V; i++) adj[i] = nullptr;
}

GrafoInt::~GrafoInt() {
    for (int v = 0; v < V; v++)
        while (adj[v] != nullptr) {
            node *aux = adj[v]->next;
            delete adj[v];
            adj[v] = aux;
        }
   delete [] adj;
}

void GrafoInt::show() {
    for (int v = 0; v < V; v++) {
        cout << v << ":";
    for (node *a = adj[v]; a != nullptr; a = a->next)
        cout << " " << a->w;
    cout << endl;
    }
}

int GrafoInt::vertices() {
    return V;
}

int GrafoInt::arestas() {
    return E;
}

int GrafoInt::arcos() {
    return A;
}

// Insere o arco v-w, se ainda não existir.
// Retorna true se o arco foi criado e false caso contrário.
bool GrafoInt::insertArc(int v, int w) {
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
bool GrafoInt::insertEdge(int v, int w) {
    if (insertArc(v, w)) {
        insertArc(w, v);
        E++;
        return true;
    }
    return false;
}

// Retorna um vetor com o grau de cada vértice
int * GrafoInt::degree() {
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
double GrafoInt::avgDegree() {
    int count = 0;
    for (int v = 0; v < V; v++) {
        for (node *a = adj[v]; a != nullptr; a = a->next) {
            count++;
        }
    }
    return (double) count/V;
}

// Retorna o grau médio dos vértices de um grafo
double GrafoInt::avgDegree2() {
    return (double) 2*E/V;
}

/* Retorna o número de componentes do grafo */
int GrafoInt::componentes() {
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

void GrafoInt::dfsR(int v, bool *marked) {
    marked[v] = true;
    for (node *a = adj[v]; a != nullptr; a = a->next) {
        int w = a->w;
        if (!marked[w])
            dfsR(w, marked);
    }
}


/* Retorna verdadeiro caso o vértice v esteja em algum ciclo,
falso caso contrário */
bool GrafoInt::dfsCycle(int v) {
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

bool GrafoInt::dfsRcycle(int u, bool *marked, int *pred) {
    marked[u] = true;
    for (node *a = adj[u]; a != nullptr; a = a->next) {
        int w = a->w;
        if (!marked[w]) {
            pred[w] = u;
            if(dfsRcycle(w, marked, pred)) return true;
        }
        else if (pred[w] == w && pred[u] != w) { // chegou no vértice inicial e não é o caminho de volta
            return true;
        }

    }
    return false;
}


/* Retorna verdadeiro caso o vértice v esteja em algum ciclo,
falso caso contrário */
// Supõe-se um ciclo simples
// x != y
bool GrafoInt::dfsCycle2(int x, int y) {
    // encontra o caminho mínimo de x para y
    if (x < 0 || x > V || y < 0 || y >  V || x == y) return false;
    int *distArr = new int[V];
    int *pred = new int[V];
    bfsVertex(x, distArr, pred);

    int dist_xy = distArr[y];
    if (dist_xy == -1) {
        delete [] distArr;
        delete [] pred;
        return false; // se não tem caminho -> retorna FALSE
    }

    // reutilizar o vetor pred para evitar andar pelo caminho encontrado
        // Cria um novo vetor, inicializa como -1, refaz o caminho de b para a
    int *pred2 = new int[V];
    for (int i = 0; i < V; i++) pred2[i] = -1;
    for (int i = y; pred[i] != i; i = pred[i])
        pred2[i] = pred[i];
    pred2[x] = x;

    for (int v = 0; v < V; v++)
        distArr[v] = -1;
        bfsVertex2(x, distArr, pred2);

    bool ans = distArr[y] != -1;
    delete [] distArr;
    delete [] pred;
    delete [] pred2;
    return ans;
}

// Não reinicializa o vetor pred, para poder ignorar um caminho na dfs
// Encontra as distâncias partindo de x sem passar pelo menor caminho em pred
void GrafoInt::bfsVertex2(int v, int *dists, int *pred) {
    Fila<int> fila = Fila<int>(V);
    for (int i = 0; i < V; i++) {
        dists[i] = -1;
    }

    fila.insere(v);
    dists[v] = 0;
    while (!fila.vazia()) {
        int u = fila.remove();
        for (node *a = adj[u]; a != nullptr; a = a->next) {
            int w = a->w;
            if (dists[w] == -1 && pred[w] != u) {;
                fila.insere(w);
                dists[w] = 1 + dists[u];
                pred[w] = u;
            }
        }
    }
}

/* Retorna se o grafo é ou não conexo */
bool GrafoInt::conexo() {
    int comp = componentes();
    return comp == 1;
}

/* Retorna o tamanho da componente conexa onde está o vértice
ou -1 caso ele não se encontre no grafo */
int GrafoInt::tamCompVertex(int v) {
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
double GrafoInt::tamMedioComp() {
    return (double) V/componentes();
}

// Retorna o tamanho da maior componente do grafo;
int GrafoInt::tamMaxComp() {
    int ans = 0;
    for (int v = 0; v < V; v++) {
        int tam = tamCompVertex(v);
        if (tam > ans) ans = tam;
    }
    return ans;
}

// Retorna o tamanho da menor componente do grafo;
int GrafoInt::tamMinComp() {
    int ans = V;
    for (int v = 0; v < V; v++) {
        int tam = tamCompVertex(v);
        if (tam < ans) ans = tam;
    }
    return ans;
}

/* Retorna a menor distância entre os vértices v e w ou -1
caso os vértices sejam desconexos ou não estejam no grafo */
int GrafoInt::dist(int v, int w) {
    if (v < 0 || v > V || w < 0 || w >  V) return -1;
    int *distArr = new int[V];
    int *pred = new int[V];
    bfsVertex(v, distArr, pred);
    int ans = distArr[w];
    delete [] distArr;
    delete [] pred;
    return ans;
}


void GrafoInt::bfsVertex(int v, int *dists, int *pred) {
    Fila<int> fila = Fila<int>(V);
    for (int i = 0; i < V; i++) {
        dists[i] = -1;
        pred[i] = -1;
    }

    fila.insere(v);
    dists[v] = 0;
    pred[v] = v;
    while (!fila.vazia()) {
        int u = fila.remove();
        for (node *a = adj[u]; a != nullptr; a = a->next) {
            int w = a->w;
            if (dists[w] == -1) {;
                fila.insere(w);
                dists[w] = 1 + dists[u];
                pred[w] = u;
            }
        }
    }
}



void GrafoInt::bfs() {
    bool *marked = new bool[V];
    int d = 0;
    Fila<int> fila = Fila<int>(V);
    for (int i = 0; i < V; i++) marked[i] = false;

    for (int i = 0; i < V; i++)
        if (!marked[i]) {
            fila.insere(i);
            marked[i] = true;
            while (!fila.vazia()) {
                int u = fila.remove();
                d++;
                for (node *a = adj[u]; a != nullptr; a = a->next) {
                    int w = a->w;
                    if (!marked[w]) {
                        fila.insere(w);
                        marked[w] = true;
                    }
                }
            }
        }
    delete [] marked;
}

void GrafoInt::pajekPrintEdges() {
    for (int v = 0; v < V; v++) {
        if (adj[v] == nullptr) continue;
        for (node *a = adj[v]; a != nullptr; a = a->next) {
            int w = a->w;
            if (v < w) // Imprime cada aresta uma só vez.
                cout << v + 1 << " " << w + 1 << endl;
        }
    }
}

#endif
