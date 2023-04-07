#ifndef REALIZZAZIONI_ISOBATO_H
#define REALIZZAZIONI_ISOBATO_H

#include "../alberoBinario_array.h"

template<class T>
class isobato {
public:
    bool isIsobato(alberoBinario_array<T> &BT);
private:
    void checkIsobato(alberoBinario_array<T> &BT, typename alberoBinario_array<T>::nodo n, bool &isobato, int altezza);
};

template<class T>
bool isobato<T>::isIsobato(alberoBinario_array<T> &BT) {
    if (!BT.alberoBinVuoto()) {
        bool isobato = true;
        checkIsobato(BT, BT.radice(), isobato, BT.altezza_nodo(BT, BT.radice()));
        return isobato;
    } else return true;
}

template<class T>
void isobato<T>::checkIsobato(alberoBinario_array<T> &BT, typename alberoBinario_array<T>::nodo n, bool &isobato,
                              int altezza) {
    if (isobato) {
        if (BT.sinistroVuoto(n) && BT.destroVuoto(n)) {
            if (BT.profondita_nodo(BT, n) != altezza) isobato = false;
        } else {
            if (!BT.sinistroVuoto(n)) checkIsobato(BT, BT.figlioSinistro(n), isobato, altezza);
            if (!BT.destroVuoto(n)) checkIsobato(BT, BT.figlioDestro(n), isobato, altezza);
        }
    }
}

#endif //REALIZZAZIONI_ISOBATO_H
