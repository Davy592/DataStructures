#ifndef REALIZZAZIONI_GRAPH_PATH_H
#define REALIZZAZIONI_GRAPH_PATH_H

#include "../grafoMatrice.h"

class graph_path {
public:
    typedef typename grafoMat<int, int>::listaNodi listaNodi;
    typedef typename grafoMat<int, int>::posizioneListaNodi posizioneListaNodi;
    typedef typename grafoMat<int, int>::nodo nodo;

    bool sumPath(int, nodo, nodo);
    void insNodo(nodo &);
    void scriviEtichetta(nodo &, int);
    void insArco(nodo &, nodo &, int);

private:
    grafoMat<int, int> G;
    bool sumPath(int, nodo, nodo, int, bool[]);

};

bool graph_path::sumPath(int sum, nodo a, nodo b, int cursum, bool visitato[]) {
    if (a.getId() == b.getId())
        if (cursum < sum) return true;
        else return false;
    listaNodi nodiAdiacenti = G.adiacenti(a);
    bool ret = false;
    visitato[a.getId()] = true;
    if (!nodiAdiacenti.listaVuota()) {
        posizioneListaNodi p = nodiAdiacenti.primoLista();
        while (!nodiAdiacenti.fineLista(p)) {
            nodo v = nodiAdiacenti.leggiLista(p);
            if (!visitato[v.getId()]) {
                ret += sumPath(sum, v, b, cursum + G.leggiEtichetta(a), visitato);
                visitato[v.getId()] = false;
            }
            p = nodiAdiacenti.succLista(p);
        }
    }
    return ret;
}


bool graph_path::sumPath(int sum, nodo a, nodo b) {
    if (G.esisteNodo(a) && G.esisteNodo(b)) {
        bool visitato[G.numNodi()];
        fill(visitato, visitato + G.numNodi(), false);
        return sumPath(sum, a, b, 0, visitato);
    } else throw out_of_range("ALMENO UNO DEI NODI DI PARTENZA O DI ARRIVO NON APPARTIENE AL GRAFO");
}

void graph_path::insNodo(nodo &n) {
    G.insNodo(n);
}

void graph_path::scriviEtichetta(nodo &n, int s) {
    G.scriviEtichetta(n, s);
}

void graph_path::insArco(nodo &n, nodo &m, int s) {
    G.insArco(n, m, s);
}

#endif //REALIZZAZIONI_GRAPH_PATH_H
