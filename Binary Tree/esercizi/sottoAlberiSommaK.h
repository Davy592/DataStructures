#ifndef REALIZZAZIONI_SOTTOALBERISOMMAK_H
#define REALIZZAZIONI_SOTTOALBERISOMMAK_H

#include "../alberoBinario_pt.h"

class checkAlbero {
public:
    int contaSottoalberi(const alberoBinario_pt<int> &, int);
private:
    int visitaSottoAlberi(const alberoBinario_pt<int> &, int, alberoBinario_pt<int>::nodo);
    int sommaSottoAlbero(const alberoBinario_pt<int> &, int, alberoBinario_pt<int>::nodo);

};

#endif //REALIZZAZIONI_SOTTOALBERISOMMAK_H

int checkAlbero::contaSottoalberi(const alberoBinario_pt<int> &B, int k) {
    int count = 0;
    if (!B.alberoBinVuoto()) {
        count = visitaSottoAlberi(B, k, B.radice());
    }
    return count;
}

int checkAlbero::visitaSottoAlberi(const alberoBinario_pt<int> &B, int k, alberoBinario_pt<int>::nodo n) {
    static int count = 0;
    int somma = sommaSottoAlbero(B, k, n);
    if (somma == k) count++;
    if (!B.sinistroVuoto(n)) {
        visitaSottoAlberi(B, k, B.figlioSinistro(n));
    }
    if (!B.destroVuoto(n)) {
        visitaSottoAlberi(B, k, B.figlioDestro(n));
    }
    return count;
}

int checkAlbero::sommaSottoAlbero(const alberoBinario_pt<int> &B, int k, alberoBinario_pt<int>::nodo n) {
    if (B.destroVuoto(n) && B.sinistroVuoto(n))
        return B.leggiNodo(n);
    else {
        int sx = 0, dx = 0;
        if (!B.sinistroVuoto(n)) sx = sommaSottoAlbero(B, k, B.figlioSinistro(n));
        if (!B.destroVuoto(n)) dx = sommaSottoAlbero(B, k, B.figlioDestro(n));
        return (B.leggiNodo(n) + sx + dx);
    }
}

