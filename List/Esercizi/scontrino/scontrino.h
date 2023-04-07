#ifndef REALIZZAZIONI_SCONTRINO_H
#define REALIZZAZIONI_SCONTRINO_H

#include "prodotto.h"
#include "../../List_vector.h"
#include <stdexcept>

class scontrino {
public:
    scontrino() = default;
    ~scontrino() = default;
    void aggiungi(prodotto v);
    void rimuovi(prodotto v);
    double totale();
    prodotto costoso();
    void stampa();
private:
    List_vector<prodotto> S;
};


void scontrino::aggiungi(prodotto v) {
    S.inserisciTesta(v);
}

void scontrino::stampa() {
    cout << S;
}

void scontrino::rimuovi(prodotto v) {
    List_vector<prodotto>::posizione p = S.primoLista();
    bool trov = false;
    while (!trov && !S.fineLista(p)) {
        if (S.leggiLista(p) == v) {
            trov = true;
            S.cancLista(p);
        } else p = S.succLista(p);
    }
}

double scontrino::totale() {
    double totale = 0;
    List_vector<prodotto>::posizione p = S.primoLista();
    while (!S.fineLista(p)) {
        totale += S.leggiLista(p).getPrezzo();
        p = S.succLista(p);
    }
    return totale;
}

prodotto scontrino::costoso() {
    if (!S.listaVuota()) {
        List_vector<prodotto>::posizione p = S.primoLista();
        prodotto v = S.leggiLista(p);
        p = S.succLista(p);
        while (!S.fineLista(p)) {
            if (S.leggiLista(p).getPrezzo() > v.getPrezzo()) {
                v = S.leggiLista(p);
            }
            p = S.succLista(p);
        }
        return v;

    } else out_of_range("SCONTRINO VUOTO");
}

#endif //REALIZZAZIONI_SCONTRINO_H
