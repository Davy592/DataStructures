#ifndef REALIZZAZIONI_GRAPHCOUNTING_H
#define REALIZZAZIONI_GRAPHCOUNTING_H

#include <vector>
#include "../grafoMatrice.h"

class graphCounting {
public:
    int countSame(grafoMat<int, int> &, grafoMat<int, int>::nodo);
    double meanN2(grafoMat<int, int> &, grafoMat<int, int>::nodo);

private:
    void meanN2(grafoMat<int, int> &, grafoMat<int, int>::nodo, bool [], int dist, vector<int> &);
};

int graphCounting::countSame(grafoMat<int, int> &G, grafoMat<int, int>::nodo n) {
    if (!G.vuoto() && G.esisteNodo(n)) {
        //PASSAGGI PRELIMINARI
        int ret = 0;
        grafoMat<int, int>::listaNodi ln;
        grafoMat<int, int>::posizioneListaNodi p;
        grafoMat<int, int>::nodo v;
        int visitato[G.numNodi()];
        fill(visitato, visitato + G.numNodi(), false);
        //ALGORITMO DI BFS
        codav<grafoMat<int, int>::nodo> q;
        q.incoda(n);
        while (!q.codaVuota()) {
            v = q.leggiCoda();
            q.fuoriCoda();
            if (!visitato[v.getId()]) {
                visitato[v.getId()] = true;
                if (G.leggiEtichetta(v) == G.leggiEtichetta(n) && v.getId() != n.getId()) ret++;
            }
            ln = G.adiacenti(v);
            p = ln.primoLista();
            while (!ln.fineLista(p)) {
                v = ln.leggiLista(p);
                if (!visitato[v.getId()] && !q.esiste(v)) {
                    q.incoda(v);
                }
                p = ln.succLista(p);
            }
        }
        return ret;
    } else throw out_of_range("GRAFO VUOTO O NODO DI PARTENZA NON PRESENTE");
}

void
graphCounting::meanN2(grafoMat<int, int> &G, grafoMat<int, int>::nodo n, bool visitato[], int dist, vector<int> &vet) {
    if (dist == 2) {
        vet.push_back(G.leggiEtichetta(n));
        return;
    }
    grafoMat<int, int>::listaNodi nodiAdiacenti = G.adiacenti(n);
    visitato[n.getId()] = true;
    if (!nodiAdiacenti.listaVuota()) {
        grafoMat<int, int>::posizioneListaNodi p = nodiAdiacenti.primoLista();
        while (!nodiAdiacenti.fineLista(p)) {
            grafoMat<int, int>::nodo v = nodiAdiacenti.leggiLista(p);
            if (!visitato[v.getId()]) meanN2(G, v, visitato, dist + 1, vet);
            p = nodiAdiacenti.succLista(p);
        }
    }
}

double graphCounting::meanN2(grafoMat<int, int> &G, grafoMat<int, int>::nodo n) {
    if (!G.vuoto() && G.esisteNodo(n)) {
        double sum = 0;
        vector<int> vet;
        bool visitato[G.numNodi()];
        fill(visitato, visitato + G.numNodi(), false);
        meanN2(G, n, visitato, 0, vet);
        for (int i = 0; i < vet.size(); i++) {
            sum += vet[i];
        }
        return sum / vet.size();
    } else throw out_of_range("GRAFO VUOTO O NODO DI PARTENZA NON PRESENTE");
}

#endif //REALIZZAZIONI_GRAPHCOUNTING_H
