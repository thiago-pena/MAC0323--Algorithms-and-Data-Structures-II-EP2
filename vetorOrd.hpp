#ifndef VETORORD_HPP
#define VETORORD_HPP
#include <string>
#include <fstream>
#include <regex>
#include <iostream>
using namespace std;

template <class Chave, class Item>
class vetorOrd {
    private:
        struct par {
            Chave chave;
            Item valor;
        };
        par *st;
        int size; // Tamanho do vetor
        int n; // número de elementos na Tabela de Símbolos
        Item nullItem;
        Chave nullKey;
        bool isEmpty();
        void resize();
    public:
        vetorOrd(int k, string nome_arquivo, Item nullItem, Chave nullKey);
        ~vetorOrd();
        bool contains(Chave chave);
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        void remove (Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
        int nElem();
        void print();
        Chave getChave(int i);
};

template <class Chave, class Item>
vetorOrd<Chave, Item>::vetorOrd(int k, string nome_arquivo, Item nullItem, Chave nullKey): st(new par[2]), size(2), n(0), nullItem(nullItem), nullKey(nullKey)
{
    regex e {"[_[:punct:]]"};
    ifstream f;
    f.open(nome_arquivo);

    if (f.fail()) {
        cout << "ERRO: arquivo " << nome_arquivo << " não pode ser aberto.\n";
        exit(EXIT_FAILURE);
    }

    string p;
    while (f >> p) {
        p = regex_replace(p, e, "");
        if (p == "" || p.length() < (unsigned) k || isdigit(p[0])) continue;
        for (int i = 0; (unsigned) i < p.length(); i++)
            p[i] = tolower(p[i]);

        int count = devolve(p);

        if (count == nullItem)
            insere(p, 1);
        else
            insere(p, ++count);
    }

    f.close();
}

template <class Chave, class Item>
vetorOrd<Chave, Item>::~vetorOrd() {
    delete [] st;
}

template <class Chave, class Item>
bool vetorOrd<Chave, Item>::isEmpty() {
    return n == 0;
}

template <class Chave, class Item>
void vetorOrd<Chave, Item>::insere(Chave chave, Item valor) {
    int r = rank(chave);
    if (r < n && st[r].chave == chave) { // já existe
        st[r].valor = valor;
    }
    else { // chave é nova
        if (n == size) resize();
        for (int i = n; i > r; i--) {
            st[i].chave = st[i - 1].chave;
            st[i].valor =  st[i - 1].valor;
        }
        st[r].chave = chave;
        st[r].valor = valor;
        n++;
    }
}

template <class Chave, class Item>
Item vetorOrd<Chave, Item>::devolve(Chave chave) {
    if (n == 0) return nullItem;
    int r = rank(chave);
    if (r < n && st[r].chave == chave)
        return st[r].valor;
    return nullItem;
}

template <class Chave, class Item>
int vetorOrd<Chave, Item>::rank(Chave chave) {
    int ini = 0, fim = n - 1;
    while (ini <= fim) {
        int meio = ini + (fim - ini)/2;
        if (chave < st[meio].chave)
            fim = meio - 1;
        else if (chave > st[meio].chave)
            ini = meio + 1;
        else
            return meio;
    }
    return ini;
}

template <class Chave, class Item>
Chave vetorOrd<Chave, Item>::seleciona(int k) {
    if (k < 0 || k >= n) return nullKey;
    return st[k].chave;
}

template <class Chave, class Item>
bool vetorOrd<Chave, Item>::contains(Chave chave) {
    int r = rank(chave);
    if (r < n && st[r].chave == chave)
        return true;
    return false;
}

template <class Chave, class Item>
void vetorOrd<Chave, Item>::resize() {
    par *novoVetor = new par[2*size];
    for (int i = 0; i < n; i++) {
        novoVetor[i].chave = st[i].chave;
        novoVetor[i].valor = st[i].valor;
    }
    par *aux = st;
    st = novoVetor;
    delete [] aux;
    size *= 2;
}

template <class Chave, class Item>
void vetorOrd<Chave, Item>::remove(Chave chave) {
    int i = rank(chave);
    if (chave != st[i].chave) return; // chave não pertence à ST
    while (i < n - 1) {
        st[i] = st[i + 1];
        i++;
    }
    n--;
}

template <class Chave, class Item>
int vetorOrd<Chave, Item>::nElem() {
    return n;
}

template <class Chave, class Item>
void vetorOrd<Chave, Item>::print() {
    for (int i = 0; i < n; i++)
        cout << "(" << i << ") " << st[i].chave << endl;
}

template <class Chave, class Item>
Chave vetorOrd<Chave, Item>::getChave(int i) {
    if (n == 0 || i < 0 || i >= n) return nullKey;
    return st[i].chave;
}

#endif
