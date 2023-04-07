#ifndef REALIZZAZIONI_MODIFICAALBERO_H
#define REALIZZAZIONI_MODIFICAALBERO_H

#include "../AlberoPt.h"

class modifcaAlbero {
public:
    void modifica(alberoPt<int> &T);
private:
    int modifica(alberoPt<int> &T, alberoPt<int>::nodo n);
};


void modifcaAlbero::modifica(alberoPt<int> &T) {
    if (!T.alberoVuoto())
        modifica(T, T.radice());
}

//ogni nodo assume come valore la somma del suo sottoalbero
int modifcaAlbero::modifica(alberoPt<int> &T, nodoT<int> *n) {
    if (T.foglia(n))
        return T.leggiNodo(n);
    else {
        int somma = 0;
        alberoPt<int>::nodo c;
        c = T.primoFiglio(n);
        somma += modifica(T, c);
        while (!T.ultimoFratello(c)) {
            c = T.fratelloSuccessivo(c);
            somma = +modifica(T, T.fratelloSuccessivo(c));
        }
        somma += modifica(T, T.fratelloSuccessivo(c));
        T.scriviNodo(n, somma);
        return somma;
    }
}

#endif //REALIZZAZIONI_MODIFICAALBERO_H
