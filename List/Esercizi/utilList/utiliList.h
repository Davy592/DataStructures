#ifndef REALIZZAZIONI_UTILILIST_H
#define REALIZZAZIONI_UTILILIST_H

#include "../../List_vector.h"
#include "../../../Dictionary/hashtableAperto.h"
#include <vector>

class utiliList {
public:
    //restituisce quanti multi di k ci sono in L
    int freq(List_vector<int> &L, int k);
    //stampa quante volte un elemento è presente in una lista
    void hist(List_vector<int> &L);
    //rimuove dalla lista tutti gli elementi il cui successivo è un numero dispari
    void remp(List_vector<int> &L);
    //rimuove dalla lista gli elementi il cui valore è multiplo della posizione in cui si trovano
    List_vector<int> &rempMul(List_vector<int> &L);
};


int utiliList::freq(List_vector<int> &L, int k) {
    if (!L.listaVuota() && k != 0) {
        List_vector<int>::posizione p = L.primoLista();
        int counter = 0;
        while (!L.fineLista(p)) {
            if ((L.leggiLista(p) % k) == 0) counter++;
            p = L.succLista(p);
        }
        return counter;
    } else return 0;
}

void utiliList::remp(List_vector<int> &L) {
    if (!L.listaVuota()) {
        List_vector<int>::posizione p = L.primoLista();
        while (!L.fineLista(p)) {
            //DEVO CONTARE ANCHE QUANDO LA LISTA VIENE MODIFICATA O CANCELLO SOLO UNA VOLTA?
            if (!L.fineLista(L.succLista(p)) && (L.leggiLista(L.succLista(p)) % 2) == 1) {
                L.cancLista(p);
                if (p != L.primoLista()) p = L.precLista(p);
            } else p = L.succLista(p);
        }
    }
}

void utiliList::hist(List_vector<int> &L) {
    open_hash_table<int, int> contatore;
    List_vector<int>::posizione p1 = L.primoLista();
    List_vector<int>::posizione p2;
    while (!L.fineLista(p1)) {
        if (!contatore.ricerca(L.leggiLista(p1))) {
            mypair<int, int> coppia(L.leggiLista(p1), (L.leggiLista(p1)));
            contatore.inserisci(coppia);
            p2 = L.primoLista();
            int counter = 0;
            while (!L.fineLista(p2)) {
                if (L.leggiLista(p1) == L.leggiLista(p2)) counter++;
                p2 = L.succLista(p2);
            }
            cout << L.leggiLista(p1) << " e ' presente " << counter << " volte nella lista" << endl;
        }
        p1 = L.succLista(p1);
    }
}


List_vector<int> &utiliList::rempMul(List_vector<int> &L) {
    int i = 1;
    List_vector<int>::posizione p = L.primoLista();
    while (!L.fineLista(p)) {
        //DEVO CONTARE ANCHE QUANDO LA LISTA VIENE MODIFICATA O CANCELLO SOLO UNA VOLTA?
        if ((L.leggiLista(p) % i) == 0) L.cancLista(p);
        if (!L.fineLista(p)) p = L.succLista(p);
    }
    return L;
}

#endif //REALIZZAZIONI_UTILILIST_H
