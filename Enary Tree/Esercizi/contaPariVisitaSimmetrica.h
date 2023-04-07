#ifndef REALIZZAZIONI_CONTAPARIVISITASIMMETRICA_H
#define REALIZZAZIONI_CONTAPARIVISITASIMMETRICA_H

#include "../AlberoPt.h"

class contaVisita {
public:
    int conta(alberoPt<int> &T);
private:
    void conta(alberoPt<int> &T, alberoPt<int>::nodo, int &, bool);
};


//visita simmetrica per i=1 (prima il primo figlio e poi gli altri) conta il numero
//di nodi che hanno il padre di valore pari
int contaVisita::conta(alberoPt<int> &T) {
    int counter = 0;
    if (!T.alberoVuoto()) {
        bool isPari = (T.leggiNodo(T.radice()) % 2) == 0;
        conta(T, T.radice(), counter, isPari);
    }
    return counter;
}

void contaVisita::conta(alberoPt<int> &T, alberoPt<int>::nodo n, int &counter, bool isPari) {
    alberoPt<int>::nodo c;
    if (T.foglia(n)) {
        if (isPari) counter++;
    } else {
        if (isPari) counter++;
        c = T.primoFiglio(n);
        isPari = (T.leggiNodo(n) % 2) == 0;
        conta(T, c, counter, isPari);
        while (!T.ultimoFratello(c)) {
            c = T.fratelloSuccessivo(c);
            conta(T, c, counter, isPari);
        }
        conta(T, c, counter, isPari);
    }
}


#endif //REALIZZAZIONI_CONTAPARIVISITASIMMETRICA_H
