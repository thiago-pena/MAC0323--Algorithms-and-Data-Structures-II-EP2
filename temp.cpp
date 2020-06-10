/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

using namespace std;

int min(int x, int y) {
    if (x < y) return x;
    else return y;
}

bool remocao(string s, string t) {
    // remoção (inserção) de uma letra. Duas palavras são vizinhas se uma é igual à outra com uma
    // de suas letras removidas. Assim, por exemplo, alta e ata são vizinhas. Da mesma forma,
    // casa e casca.
    int minLen = min(s.length(), t.length());
    string maior, menor;
    if (s.length() == minLen) {
        menor = s;
        maior = t;
    } else {
        menor = t;
        maior = s;
    }
    if (maior.length() != 1 + minLen) return false;

    bool vizinhas = true;
    int i = 0;
    int j = 0;
    while (i < minLen && j < minLen + 1 && (i - j < 1)) { // j == i (remover última letra) ou j == i + 1 (removeu alguma letra que não a última)
        if (menor[i] == maior[j])
            i++;
        j++;
    }
    if (j == i || j == i + 1) return true;
    return false;

}

bool trocaLetras(string s, string t) {
    // troca de letras de uma mesma palavra. Duas palavras são vizinhas se uma pode ser obtida a
    // partir da troca de posição de duas letras da outra. Por exemplo, nato e nota são vizinhas,
    // assim como nota e tona.

    if (s.length() != t.length()) return false;
    int i, j, k, contDiferentes = 0;
    for (k = 0; k < s.length(); k++) {
        if (s[k] != t[k]) {
            if (contDiferentes == 0) i = k;
            else if (contDiferentes == 1) j = k;
            if (++contDiferentes > 2) return false;
        }
    }
    if (contDiferentes != 2) return false;
    if (s[i] == t[j] && s[j] == t[i]) return true;
    return false;
}

bool substituicao(string s, string t) {
    // substituição de uma letra. Duas palavras são vizinhas se uma é obtida a partir da outra
    // substituindo uma das letras. Por exemplo, gato e rato são vizinhas, assim como prata e
    // preta
    if (s.length() != t.length()) return false;
    int i, contDiferentes = 0;
    for (i = 0; i < s.length(); i++)
        if (s[i] != t[i])
            if (++contDiferentes > 1) return false;
    if (contDiferentes == 1) return true;
    return false;
}

int main()
{
    // substituição de uma letra. Duas palavras são vizinhas se uma é obtida a partir da outra
    // substituindo uma das letras. Por exemplo, gato e rato são vizinhas, assim como prata e
    // preta

    string s = "prata";
    string t = "preta";

    cout << "Remoção? " << remocao(s, t) << endl;
    cout << "Troca? " << trocaLetras(s, t) << endl;
    cout << "Substituição? " << substituicao(s, t) << endl;
    return 0;
}
