#ifndef REALIZZAZIONI_UTIL_BIN_TREE_H
#define REALIZZAZIONI_UTIL_BIN_TREE_H

#include "../alberoBinario_pt.h"

class util_bin_tree {
public:
    //restituisce il numero di nodi al livello k il cui valore è divisibile per 3
    int d3(alberoBinario_pt<int> &, int);

    //restituisce il numero di nodi il cui valore è pari
    int lp(alberoBinario_pt<int> &);

    //numero di foglie il cui padre è multiplo di 5
    int l2p(alberoBinario_pt<int> &);

    //numero foglie con valore pari
    int even_leafs(alberoBinario_pt<int> &);

    //Modifica albero secondo il criterio
    void modifica(alberoBinario_pt<int> &);

    //Numero foglie il cui genitore è pari
    int leafs_with_even_parent(alberoBinario_pt<int> &);

    // Numero nodi al livello K con valore dispari
    int odd(alberoBinario_pt<int> &, int);

    //A ogni foglia aggiunge un figlio (sinistro in questo caso) il cui valore è la somma dei nodi presenti nel cammino che partono dalla radice e arrivano a quella foglia
    void aggiungiSommaFoglia(alberoBinario_pt<int> &);

private:
    int d3(alberoBinario_pt<int> &, alberoBinario_pt<int>::nodo, int, int);
    int lp(alberoBinario_pt<int> &, alberoBinario_pt<int>::nodo);
    int l2p(alberoBinario_pt<int> &, alberoBinario_pt<int>::nodo);
    int even_leafs(alberoBinario_pt<int> &, alberoBinario_pt<int>::nodo);
    void modifica(alberoBinario_pt<int> &, alberoBinario_pt<int>::nodo);
    int leafs_with_even_parent(alberoBinario_pt<int> &, alberoBinario_pt<int>::nodo);
    int odd(alberoBinario_pt<int> &, alberoBinario_pt<int>::nodo, int, int);
    void aggiungiSommaFoglia(alberoBinario_pt<int> &, alberoBinario_pt<int>::nodo);
};

int util_bin_tree::d3(alberoBinario_pt<int> &A, typename alberoBinario_pt<int>::nodo n, int liv, int k) {
    if (liv == k) return A.leggiNodo(n) % 3 == 0;
    if (A.sinistroVuoto(n) && A.destroVuoto(n)) return 0;
    int mul3 = 0;
    if (!A.sinistroVuoto(n)) mul3 += d3(A, A.figlioSinistro(n), liv + 1, k);
    if (!A.destroVuoto(n)) mul3 += d3(A, A.figlioDestro(n), liv + 1, k);
    return mul3;
}

int util_bin_tree::d3(alberoBinario_pt<int> &A, int k) {
    if (!A.alberoBinVuoto()) return d3(A, A.radice(), 0, k);
    else throw std::out_of_range("Albero vuoto");
}

int util_bin_tree::lp(alberoBinario_pt<int> &A, typename alberoBinario_pt<int>::nodo n) {
    if (A.sinistroVuoto(n) && A.destroVuoto(n)) return A.leggiNodo(n) % 2 == 0;
    int fp = 0;
    if (!A.sinistroVuoto(n)) fp += lp(A, A.figlioSinistro(n));
    if (!A.destroVuoto(n)) fp += lp(A, A.figlioDestro(n));
    return fp;
}

int util_bin_tree::lp(alberoBinario_pt<int> &A) {
    if (!A.alberoBinVuoto()) return lp(A, A.radice());
    else throw std::out_of_range("Albero vuoto");
}

int util_bin_tree::l2p(alberoBinario_pt<int> &A, typename alberoBinario_pt<int>::nodo n) {
    if (A.sinistroVuoto(n) && A.destroVuoto(n)) return A.leggiNodo(A.genitore(n)) % 5 == 0;
    int fp = 0;
    if (!A.sinistroVuoto(n)) fp += l2p(A, A.figlioSinistro(n));
    if (!A.destroVuoto(n)) fp += l2p(A, A.figlioDestro(n));
    return fp;
}

int util_bin_tree::l2p(alberoBinario_pt<int> &A) {
    if (!A.alberoBinVuoto()) return l2p(A, A.radice());
    else throw std::out_of_range("Albero vuoto");
}

int util_bin_tree::even_leafs(alberoBinario_pt<int> &A, typename alberoBinario_pt<int>::nodo n) {
    if (A.sinistroVuoto(n) && A.destroVuoto(n)) return A.leggiNodo(n) % 2 == 0;
    int fp = 0;
    if (!A.sinistroVuoto(n)) fp += even_leafs(A, A.figlioSinistro(n));
    if (!A.destroVuoto(n)) fp += even_leafs(A, A.figlioDestro(n));
    return fp;
}

int util_bin_tree::even_leafs(alberoBinario_pt<int> &A) {
    if (!A.alberoBinVuoto()) return even_leafs(A, A.radice());
    else throw std::out_of_range("Albero vuoto");
}

void util_bin_tree::modifica(alberoBinario_pt<int> &T) {
    if (!T.alberoBinVuoto()) modifica(T, T.radice());
    else throw std::out_of_range("Albero vuoto");
}

void util_bin_tree::modifica(alberoBinario_pt<int> &T, alberoBinario_pt<int>::nodo n) {
    if (T.sinistroVuoto(n) && T.destroVuoto(n)) {
        return;
    } else {
        int counter = lp(T, n);
        T.scriviNodo(n, counter);
        if (!T.sinistroVuoto(n)) modifica(T, T.figlioSinistro(n));
        if (!T.destroVuoto(n)) modifica(T, T.figlioSinistro(n));
    }
}

int util_bin_tree::leafs_with_even_parent(alberoBinario_pt<int> &A, typename alberoBinario_pt<int>::nodo n) {
    if (A.sinistroVuoto(n) && A.destroVuoto(n)) return A.leggiNodo(A.genitore(n)) % 2 == 0;
    int fp = 0;
    if (!A.sinistroVuoto(n)) fp += leafs_with_even_parent(A, A.figlioSinistro(n));
    if (!A.destroVuoto(n)) fp += leafs_with_even_parent(A, A.figlioDestro(n));
    return fp;
}

int util_bin_tree::leafs_with_even_parent(alberoBinario_pt<int> &A) {
    if (!A.alberoBinVuoto()) return leafs_with_even_parent(A, A.radice());
    else throw std::out_of_range("Albero vuoto");
}

int util_bin_tree::odd(alberoBinario_pt<int> &A, typename alberoBinario_pt<int>::nodo n, int liv, int k) {
    if (liv == k) return A.leggiNodo(n) % 2 == 1;
    if (A.sinistroVuoto(n) && A.destroVuoto(n)) return 0;
    int dis = 0;
    if (!A.sinistroVuoto(n)) dis += odd(A, A.figlioSinistro(n), liv + 1, k);
    if (!A.destroVuoto(n)) dis += odd(A, A.figlioDestro(n), liv + 1, k);
    return dis;
}

int util_bin_tree::odd(alberoBinario_pt<int> &A, int k) {
    if (!A.alberoBinVuoto()) return odd(A, A.radice(), 0, k);
    else throw std::out_of_range("Albero vuoto");
}

void util_bin_tree::aggiungiSommaFoglia(alberoBinario_pt<int> &T) {
    if (!T.alberoBinVuoto()) {
        aggiungiSommaFoglia(T, T.radice());
    }
}

void util_bin_tree::aggiungiSommaFoglia(alberoBinario_pt<int> &T, alberoBinario_pt<int>::nodo n) {
    if (!T.sinistroVuoto(n) && !T.destroVuoto(n)) {
        if (!T.sinistroVuoto(n)) aggiungiSommaFoglia(T, T.figlioSinistro(n));
        if (!T.destroVuoto(n)) aggiungiSommaFoglia(T, T.figlioDestro(n));
    } else {
        int somma = T.leggiNodo(n);
        alberoBinario_pt<int>::nodo padre = T.genitore(n);
        while (padre != T.radice()) {
            somma += T.leggiNodo(padre);
            padre = T.genitore(padre);
        }
        somma += T.leggiNodo(padre);
        T.inserisciSinistro(n, somma);
    }
}

#endif //REALIZZAZIONI_UTIL_BIN_TREE_H