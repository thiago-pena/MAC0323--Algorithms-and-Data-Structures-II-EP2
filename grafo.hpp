#ifndef GRAFO_HPP
#define GRAFO_HPP
#include "fila.hpp"
using namespace std;

/*
    ./ep2 nome_arquivo k
        -> modo pré-definido
        -> inserir na ST apenas as palavras necessárias
        -> não incluir números
    ./ep2 texto.txt 10
*/

class Grafo {
    public:
        Grafo(int V);
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
        void bfs(); // tornar private
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


Grafo::Grafo(int V): V(V), A(0), E(0), adj(new node * [V])
{
    for (int i = 0; i < V; i++) adj[i] = nullptr;
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
    return false;
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
bool Grafo::dfsCycle2(int x, int y) {
    // encontra o caminho mínimo de x para y
    if (x < 0 || x > V || y < 0 || y >  V || x == y) return false;
    int *distArr = new int[V];
    int *pred = new int[V];
    bfsVertex(x, distArr, pred);

    int dist_xy = distArr[y];
    if (dist_xy == -1) return false; // se não tem caminho -> retorna FALSE

    // reutilizar o vetor pred para evitar andar pelo caminho encontrado
        // Cria um novo vetor, inicializa como -1, refaz o caminho de b para a
    int *pred2 = new int[V];
    for (int i = 0; i < V; i++) pred2[i] = -1;
    int limite = 0;
    for (int i = y; pred[i] != i; i = pred[i])
    {
        pred2[i] = pred[i];
    }

    pred2[x] = x;
// delete pred;
    // tentar encontrar um novo caminho de a para b que não seja o primeiro caminho
    // bool *marked = new bool[V];
    for (int v = 0; v < V; v++) {
        // marked[v] = false;
        distArr[v] = -1;
    }

    // cout << "------------------------" << endl;
    // cout << "Teste pred2" << endl;
    // for (int i = 0; i < V; i++) cout << "\ti:" << i << ", pred: " << pred2[i] << endl;

    bfsVertex2(x, distArr, pred2);
    return distArr[y] != -1;
}

// Não reinicializa o vetor pred, para poder ignorar um caminho na dfs
// Encontra as distâncias partindo de x sem passar pelo menor caminho em pred
void Grafo::bfsVertex2(int v, int *dists, int *pred) {
    // Fila<int> fila = new Fila<int>(V);
    Fila<int> fila = Fila<int>(V);
    for (int i = 0; i < V; i++) {
        dists[i] = -1;
        // pred[i] = -1;
    }

    fila.insere(v);
    dists[v] = 0;
    // pred[v] = v;
    while (!fila.vazia()) {
        int u = fila.remove();
        for (node *a = adj[u]; a != nullptr; a = a->next) { // poderia usar int i sem problema pois teria escopo apenas no for
            int w = a->w;
            if (dists[w] == -1 && pred[w] != u) {;
                fila.insere(w);
                // cout << "\t\t\tu: " << u << ", w: " << w << endl;
                // cout << "\t\t\tpu: " << pred[u] << ", pw: " << pred[w] << endl;
                dists[w] = 1 + dists[u];
                pred[w] = u;
            }
        }
    }
    // Como destruir a fila? @@@
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
    int *distArr = new int[V];
    int *pred = new int[V];
    bfsVertex(v, distArr, pred);
    int ans = distArr[w];
    // delete [] distArr;
    // delete pred;
    return ans;
}


void Grafo::bfsVertex(int v, int *dists, int *pred) {
    // Fila<int> fila = new Fila<int>(V);
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
        for (node *a = adj[u]; a != nullptr; a = a->next) { // poderia usar int i sem problema pois teria escopo apenas no for
            int w = a->w;
            if (dists[w] == -1) {;
                fila.insere(w);
                dists[w] = 1 + dists[u];
                pred[w] = u;
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
