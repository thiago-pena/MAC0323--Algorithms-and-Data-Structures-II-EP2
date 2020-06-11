#ifndef FILA_HPP
#define FILA_HPP
using namespace std;

// Supõe-se que temos 0 <= ini <= fim <= N.
template <class Item>
class Fila {
    public:
        Fila(int tam);
        ~Fila();
        void insere(Item item);
        Item remove();
        bool vazia();

    private:
        Item *F;
        int ini;
        int fim;
};

template <class Item>
Fila<Item>::Fila(int tam): F(new Item[tam]), ini(0), fim(0) {};

template <class Item>
Fila<Item>::~Fila()
{
  if (F != nullptr)
    delete [] F;
}

template <class Item>
void Fila<Item>::insere(Item item) {
    F[fim++] = item;
}

template <class Item>
bool Fila<Item>::vazia() {
    return ini == fim;
}

template <class Item>
Item Fila<Item>::remove() {
    return F[ini++];
}

#endif
