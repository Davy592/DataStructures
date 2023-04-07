#ifndef REALIZZAZIONI_PARIDISPARI_H
#define REALIZZAZIONI_PARIDISPARI_H

#include "../alberoBinario_array.h"

template<class T>
class pariDispari {
public:
    bool isPariDispari(alberoBinario_array<T> &BT);
private:
    void checkIsPariDispari(alberoBinario_array<T> &BT, typename alberoBinario_array<T>::nodo n, int livello,
                            bool &pariDispari);
};

template<class T>
bool pariDispari<T>::isPariDispari(alberoBinario_array<T> &BT) {
    if (!BT.alberoBinVuoto()) {
        bool pariDispari = true;
        checkIsPariDispari(BT, BT.radice(), 0, pariDispari);
        return pariDispari;
    } else return false;
}

template<class T>
void
pariDispari<T>::checkIsPariDispari(alberoBinario_array<T> &BT, typename alberoBinario_array<T>::nodo n, int livello,
                                   bool &pariDispari) {
    if (pariDispari) {
        if (BT.leggiNodo(n) % 2 == 0) {
            if (livello % 2 != 0) pariDispari = false;
        } else {
            if (livello % 2 == 0) pariDispari = false;
        }
        if (pariDispari) {
            if (!BT.sinistroVuoto(n)) checkIsPariDispari(BT, BT.figlioSinistro(n), livello + 1, pariDispari);
            if (!BT.destroVuoto(n)) checkIsPariDispari(BT, BT.figlioDestro(n), livello + 1, pariDispari);

        }
    }

}

#endif //REALIZZAZIONI_PARIDISPARI_H
