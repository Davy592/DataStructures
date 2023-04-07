#ifndef REALIZZAZIONI_ELIMINAMULTIPLO_H
#define REALIZZAZIONI_ELIMINAMULTIPLO_H

#include "../pilav.h"

class eliminaMultiplo {
public:
    void elimina(pilav<int> &, int k);
};

void eliminaMultiplo::elimina(pilav<int> &p, int k) {
    pilav<int> p2;
    while (!p.pilaVuota()) {
        if ((p.leggiPila() % k) != 0)
            p2.inPila(p.leggiPila());
        p.fuoriPila();
    }
    while (!p2.pilaVuota()) {
        p.insPila(p2.leggiPila());
        p2.fuoriPila();
    }
}

#endif //REALIZZAZIONI_ELIMINAMULTIPLO_H
