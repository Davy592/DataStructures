#ifndef REALIZZAZIONI_SUMTREE_H
#define REALIZZAZIONI_SUMTREE_H

#include "../alberoBinario_pt.h"


class sumTree {
public:
    bool isSumTree(alberoBinario_pt<int> &);

private:
    int isSumTree2(alberoBinario_pt<int> &, typename alberoBinario_pt<int>::nodo n, bool &);
};


bool sumTree::isSumTree(alberoBinario_pt<int> &bt) {
    bool sumTree = true;
    if (!bt.alberoBinVuoto()) {
        int x = isSumTree2(bt, bt.radice(), sumTree);
    } else sumTree = false;
    return sumTree;
}


int sumTree::isSumTree2(alberoBinario_pt<int> &bt, typename alberoBinario_pt<int>::nodo n, bool &sumTree) {
    if (sumTree) {
        if (bt.sinistroVuoto(n) && bt.destroVuoto(n)) {
            return bt.leggiNodo(n);
        } else {
            int sx = 0, dx = 0;
            if (!bt.sinistroVuoto(n)) sx = isSumTree2(bt, bt.figlioSinistro(n), sumTree);
            if (!bt.destroVuoto(n)) dx = isSumTree2(bt, bt.figlioDestro(n), sumTree);
            if (bt.leggiNodo(n) == sx + dx) {
                return (bt.leggiNodo(n) * 2);
            } else sumTree = false;
        }
    } else return 0;
}

#endif //REALIZZAZIONI_SUMTREE_H
