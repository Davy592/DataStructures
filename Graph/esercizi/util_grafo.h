#ifndef REALIZZAZIONI_UTIL_GRAFO_H
#define REALIZZAZIONI_UTIL_GRAFO_H

#include "../grafoMatrice.h"

typedef struct {
    nodoG nodo;
    bool visitato;
} nodo_visita;

class util_grafo {
public:
    //Restituisce il numero di nodi raggiungibili da n1 e con la stessa etichetta
    int countSame(grafoMat<int, int> &g, typename grafoMat<int, int>::nodo n1);
    //Restituisce la media dei valori delle etichette dei nodo raggiungibili da n1 con cammini di lunghezza 2
    double meanN2(grafoMat<int, int> &g, typename grafoMat<int, int>::nodo n1);
private:
    int returnPosizione(typename grafoMat<int, int>::nodo a, nodo_visita vet[]);
    void visita2(grafoMat<int, int> &g, typename grafoMat<int, int>::nodo n, int &somma, int &counter, int &lunghezza,
                 nodo_visita visitati[]);

};

int util_grafo::countSame(grafoMat<int, int> &g, typename grafoMat<int, int>::nodo n1) {
    //operazioni preliminari
    nodo_visita n;
    nodoG v;
    List_vector<nodoG> lista_nodi = g.list_nodi();
    List_vector<nodoG> lista_adiacenti;
    nodo_visita visitati[g.numNodi()];
    List_vector<nodoG>::posizione p = lista_nodi.primoLista();
    int counter = 0;
    int i = 0;
    while (i < g.numNodi()) {
        n.nodo = lista_nodi.leggiLista(p);
        n.visitato = false;
        visitati[i] = n;
        p = lista_nodi.succLista(p);
        i++;
    }
    //VISITA
    codav<nodoG> q;
    q.incoda(n1);
    nodoG currentNode;
    while (!q.codaVuota()) {
        currentNode = q.leggiCoda();
        q.fuoriCoda();
        visitati[returnPosizione(currentNode, visitati)].visitato = true;
        lista_adiacenti = g.adiacenti(currentNode);
        p = lista_adiacenti.primoLista();
        while (!lista_adiacenti.fineLista(p)) {
            v = lista_adiacenti.leggiLista(p);
            if (g.leggiEtichetta(n1) == g.leggiEtichetta(v) && !visitati[returnPosizione(v, visitati)].visitato)
                counter++;
            if (!visitati[returnPosizione(v, visitati)].visitato && !q.esiste(v)) {
                q.incoda(v);
            }
            p = lista_adiacenti.succLista(p);
        }
    }
    return counter;
}

#endif //REALIZZAZIONI_UTIL_GRAFO_H

int util_grafo::returnPosizione(typename grafoMat<int, int>::nodo a, nodo_visita vet[]) {
    bool trovato = false;
    int i = 0;
    while (!trovato) {
        nodo_visita n = vet[i];
        if (a == n.nodo) {
            trovato = true;
        } else i++;
    }
    return i;
}


double util_grafo::meanN2(grafoMat<int, int> &g, typename grafoMat<int, int>::nodo n1) {
    int counter = 0;
    if (!g.vuoto()) {
        //OPERAZIONE PRELIMINARE DI VISITA
        nodo_visita n;
        List_vector<nodoG> lista_nodi = g.list_nodi();
        nodo_visita visitati[g.numNodi()];
        List_vector<nodoG>::posizione p = lista_nodi.primoLista();
        int i = 0;
        while (i < g.numNodi()) {
            n.nodo = lista_nodi.leggiLista(p);
            n.visitato = false;
            visitati[i] = n;
            p = lista_nodi.succLista(p);
            i++;
        }


        int somma = 0;
        int lunghezza = 0;
        visita2(g, n1, somma, counter, lunghezza, visitati);
        if (counter > 0) {
            return (double) somma / counter;
        } else {
            return 0;
        }
    } else return 0;
}

void util_grafo::visita2(grafoMat<int, int> &g, typename grafoMat<int, int>::nodo n, int &somma, int &counter,
                         int &lunghezza, nodo_visita visitati[]) {
    if (lunghezza < 2) {
        //VISITO IL GRAFO
        List_vector<nodoG> nodiAdiacenti = g.adiacenti(n);
        visitati[returnPosizione(n, visitati)].visitato = true;
        if (!nodiAdiacenti.listaVuota()) {
            List_vector<nodoG>::posizione p = nodiAdiacenti.primoLista();
            while (!nodiAdiacenti.fineLista(p)) {
                nodoG v = nodiAdiacenti.leggiLista(p);
                if (!visitati[returnPosizione(v, visitati)].visitato) {
                    lunghezza++;
                    visita2(g, v, somma, counter, lunghezza, visitati);
                }
                p = nodiAdiacenti.succLista(p);
            }
        }
    } else if (lunghezza == 2) {
        somma += g.leggiEtichetta(n);
        counter++;
    }
    lunghezza--;
}