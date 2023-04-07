#ifndef REALIZZAZIONI_LIONESE_H
#define REALIZZAZIONI_LIONESE_H

#include "../alberoBinario_array.h"

template<class T>
class lionese {
public:
    bool isLionese(alberoBinario_array<T> &BT);
private:
    void checkLionese(alberoBinario_array<T> &BT, typename alberoBinario_array<T>::nodo n, bool &isLionese);

};

template<class T>
bool lionese<T>::isLionese(alberoBinario_array<T> &BT) {
    if (!BT.alberoBinVuoto()) {
        bool lionese = true;
        checkLionese(BT, BT.radice(), lionese);
        return lionese;
    }
    return false;
}

template<class T>
void lionese<T>::checkLionese(alberoBinario_array<T> &BT, typename alberoBinario_array<T>::nodo n, bool &isLionese) {
    if (!BT.sinistroVuoto(n) && !BT.destroVuoto(n)) {
        // IL VALORE DELLA RADICE NON E' IMPORTANTE
        if (BT.radice() != n) {
            if (!BT.sinistroVuoto(n)) {
                if (BT.leggiNodo(BT.figlioSinistro(n)) % 2 != 1) isLionese = false;
                else
                    checkLionese(BT, BT.figlioSinistro(n), isLionese);
            }
            if (isLionese && !BT.destroVuoto(n)) {
                if (BT.leggiNodo(BT.figlioDestro(n)) % 2 != 0) isLionese = false;
                else
                    checkLionese(BT, BT.figlioDestro(n), isLionese);
            }
        }
    }
}

#endif //REALIZZAZIONI_LIONESE_H
