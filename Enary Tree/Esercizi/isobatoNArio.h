#ifndef REALIZZAZIONI_ISOBATONARIO_H
#define REALIZZAZIONI_ISOBATONARIO_H

#include "../AlberoPt.h"

template<class T>
class isobatoN {
public:
    bool isIsobato(alberoPt<T> &tree);
private:
    void checkIsobato(alberoPt<T> &B, typename alberoPt<T>::nodo n, bool &isobato, int altezza, int currentH);
};

template<class T>
bool isobatoN<T>::isIsobato(alberoPt<T> &tree) {
    if (!tree.alberoVuoto()) {
        bool isobato = true;
        checkIsobato(tree, tree.radice(), isobato, tree.profonditaAlbero() - 1, 0);
        return isobato;
    } else return true;
}

template<class T>
void isobatoN<T>::checkIsobato(alberoPt<T> &B, typename alberoPt<T>::nodo n, bool &isobato, int altezza, int currentH) {
    if (isobato) {
        if (B.foglia(n)) {
            if (currentH != altezza) isobato = false;
        } else {
            if (!B.ultimoFratello(n)) {
                checkIsobato(B, B.fratelloSuccessivo(n), isobato, altezza, currentH);
            }
            if (!B.foglia(n)) {
                checkIsobato(B, B.primoFiglio(n), isobato, altezza, currentH + 1);

            }
        }
    }
}

#endif //REALIZZAZIONI_ISOBATONARIO_H
