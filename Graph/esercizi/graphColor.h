#ifndef REALIZZAZIONI_GRAPHCOLOR_H
#define REALIZZAZIONI_GRAPHCOLOR_H

#include "../grafoMatrice.h"

using namespace std;

class graphColor {
public:
    typedef typename grafoMat<string, int>::listaNodi listaNodi;
    typedef typename grafoMat<string, int>::posizioneListaNodi posizioneListaNodi;
    typedef typename grafoMat<string, int>::nodo nodo;

    bool sameColorPath(nodo, nodo);
    bool uniformColorPath(nodo, nodo);
    void insNodo(nodo &);
    void scriviEtichetta(nodo &, string);
    void insArco(nodo &, nodo &, int);

private:
    grafoMat<string, int> G;
};

bool graphColor::sameColorPath(nodo n1, nodo n2) {
    if (G.esisteNodo(n1) && G.esisteNodo(n2)) {
        //PASSAGGI PRELIMINARI
        string color = G.leggiEtichetta(n1);
        nodo cur;
        listaNodi ln;
        posizioneListaNodi p;
        nodo v;
        bool visitato[G.numNodi()];
        for (int i = 0; i < G.numNodi(); i++) {
            visitato[i] = false;
        }
        //ALGORITMO DI BFS
        codav<nodo> q;
        q.incoda(n1);
        while (!q.codaVuota()) {
            cur = q.leggiCoda();
            q.fuoriCoda();
            if (!visitato[cur.getId()]) {
                visitato[cur.getId()] = true;
                ln = G.adiacenti(cur);
                p = ln.primoLista();
                while (!ln.fineLista(p)) {
                    v = ln.leggiLista(p);
                    if (!visitato[v.getId()] && !q.esiste(v) && G.leggiEtichetta(v) == color) {
                        q.incoda(v);
                    }
                    p = ln.succLista(p);
                }
            }
        }
        return visitato[n2.getId()];
    } else throw out_of_range("Nel grafo non esiste almeno uno dei due nodi");
}

bool graphColor::uniformColorPath(nodo n1, nodo n2) {
    if (G.esisteNodo(n1) && G.esisteNodo(n2)) {
        //PASSAGGI PRELIMINARI
        string color;
        nodo cur;
        listaNodi ln;
        posizioneListaNodi p;
        nodo v;
        bool visitato[G.numNodi()];
        for (int i = 0; i < G.numNodi(); i++) {
            visitato[i] = false;
        }
        //ALGORITMO DI BFS
        codav<nodo> q;
        q.incoda(n1);
        while (!q.codaVuota()) {
            cur = q.leggiCoda();
            color = G.leggiEtichetta(cur);
            q.fuoriCoda();
            if (!visitato[cur.getId()]) {
                visitato[cur.getId()] = true;
                ln = G.adiacenti(cur);
                p = ln.primoLista();
                while (!ln.fineLista(p)) {
                    v = ln.leggiLista(p);
                    if (!visitato[v.getId()] && !q.esiste(v) && G.leggiEtichetta(v) != color) {
                        q.incoda(v);
                    }
                    p = ln.succLista(p);
                }
            }
        }
        return visitato[n2.getId()];
    } else throw out_of_range("Nel grafo non esiste almeno uno dei due nodi");
}

void graphColor::insNodo(nodo &n) {
    G.insNodo(n);
}

void graphColor::scriviEtichetta(nodo &n, string s) {
    G.scriviEtichetta(n, s);
}

void graphColor::insArco(nodo &n, nodo &m, int s) {
    G.insArco(n, m, s);
}

#endif //REALIZZAZIONI_GRAPHCOLOR_H
