#ifndef REALIZZAZIONI_PESO1_H
#define REALIZZAZIONI_PESO1_H

#include "../grafoMatrice.h"

typedef struct {
    int numeroCammini = 0;
    double mediaLunghezza = 0;
} cammino_pesato;


typedef struct {
    nodoG nodo;
    bool visitato;
} nodo_visita;


template<class T>
class peso_grafo {
public:
    typedef cammino_pesato cammino_pesato;
    //Dato un arco g e due nodi "a" e "b" (i cui pesi degli archi sono 1 o -1) restituire il numero
    //di cammini da "a" a "b" tale che il peso di tutti gli archi del cammino sia 1.
    //Restituire inoltre la media della lunghezza dei cammini trovati
    cammino_pesato cammini1(grafoMat<T, int> &g, typename grafoMat<T, int>::nodo a, typename grafoMat<T, int>::nodo b);
private:
    int returnPosizione(typename grafoMat<int, int>::nodo a, nodo_visita vet[]);
    void visitaPesata(grafoMat<T, int> &g, typename grafoMat<T, int>::nodo a, typename grafoMat<T, int>::nodo b,
                      int &lunghezzaTotale, int &lunghezzaAttuale, int &numeroCammini, nodo_visita visitati[]);
};

template<class T>
cammino_pesato
peso_grafo<T>::cammini1(grafoMat<T, int> &g, typename grafoMat<T, int>::nodo a, typename grafoMat<T, int>::nodo b) {
    cammino_pesato c;
    c.mediaLunghezza = 0;
    c.numeroCammini = 0;
    if (!g.vuoto()) {
        //OPERAZIONI PRELIMINARI ALLA VISITA
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


        int numeroCammini = 0;
        int lunghezzaTotale = 0;
        int lunghezzaAttuale = 0;

        visitaPesata(g, a, b, lunghezzaTotale, lunghezzaAttuale, numeroCammini, visitati);
        if (numeroCammini > 0) {
            c.numeroCammini = numeroCammini;
            c.mediaLunghezza = (double) lunghezzaTotale / numeroCammini;
        }
    }
    return c;
}


template<class T>
void
peso_grafo<T>::visitaPesata(grafoMat<T, int> &g, typename grafoMat<T, int>::nodo a, typename grafoMat<T, int>::nodo b,
                            int &lunghezzaTotale, int &lunghezzaAttuale, int &numeroCammini, nodo_visita visitati[]) {
    List_vector<nodoG> nodi_adiacenti = g.adiacenti(a);
    //IL VETTORE VISITATI VIENE UTILIZZATO PER EVITARE DI ENTRARE IN UN CICLO
    if (!(a == b)) visitati[returnPosizione(a, visitati)].visitato = true;
    if (!nodi_adiacenti.listaVuota()) {
        List_vector<nodoG>::posizione p = nodi_adiacenti.primoLista();
        while (!nodi_adiacenti.fineLista(p)) {
            nodoG v = nodi_adiacenti.leggiLista(p);
            if (!visitati[returnPosizione(v, visitati)].visitato) {
                if (g.leggiPeso(a, v) == 1) {
                    lunghezzaAttuale++;
                    if (v == b) {
                        lunghezzaTotale += lunghezzaAttuale;
                        numeroCammini++;
                    }
                    visitaPesata(g, v, b, lunghezzaTotale, lunghezzaAttuale, numeroCammini, visitati);
                } else {
                    lunghezzaAttuale--;
                }
            }
            p = nodi_adiacenti.succLista(p);
            visitati[returnPosizione(a, visitati)].visitato = false;
        }
    }
    lunghezzaAttuale--;
}


template<class T>
int peso_grafo<T>::returnPosizione(typename grafoMat<int, int>::nodo a, nodo_visita vet[]) {
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


#endif //REALIZZAZIONI_PESO1_H
