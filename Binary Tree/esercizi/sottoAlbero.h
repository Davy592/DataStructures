#ifndef REALIZZAZIONI_SOTTOALBERO_H
#define REALIZZAZIONI_SOTTOALBERO_H

#include "../alberoBinario_array.h"

template<class T>
class subTree {
public:
    bool isSubTree(alberoBinario_array<T> &BT, alberoBinario_array<T> &subBT);
private:
    void
    checkSubTree(alberoBinario_array<T> &BT, alberoBinario_array<T> &subBT, typename alberoBinario_array<T>::nodo n,
                 typename alberoBinario_array<T>::nodo subR, bool &isSubTree);
};

template<class T>
bool subTree<T>::isSubTree(alberoBinario_array<T> &BT, alberoBinario_array<T> &subBT) {
    if (!BT.alberoBinVuoto() && !subBT.alberoBinVuoto()) {
        bool subTree = true;
        checkSubTree(BT, subBT, BT.radice(), subBT.radice(), subTree);
        return subTree;
    } else return false;
}

template<class T>
void subTree<T>::checkSubTree(alberoBinario_array<T> &BT, alberoBinario_array<T> &subBT,
                              typename alberoBinario_array<T>::nodo n, typename alberoBinario_array<T>::nodo subR,
                              bool &isSubTree) {
    if (isSubTree) {
        if (BT.leggiNodo(n) != subBT.leggiNodo(subR)) {
            isSubTree = false;

            // SE il nodo di BT è radice richiamo sui suoi figli
            if (n == BT.radice()) {
                isSubTree = true;
                if (!BT.sinistroVuoto(n)) checkSubTree(BT, subBT, BT.figlioSinistro(n), subBT.radice(), isSubTree);
                if (!isSubTree && !BT.destroVuoto(n)) {
                    isSubTree = true;
                    checkSubTree(BT, subBT, BT.figlioDestro(n), subBT.radice(), isSubTree);
                }
            }
        } else {
            if (!BT.sinistroVuoto(n) && !subBT.sinistroVuoto(subR))
                checkSubTree(BT, subBT, BT.figlioSinistro(n), subBT.figlioSinistro(subR), isSubTree);
            if (!BT.destroVuoto(n) && !subBT.destroVuoto(subR) && isSubTree)
                checkSubTree(BT, subBT, BT.figlioDestro(n), subBT.figlioDestro(subR), isSubTree);
        }
    } else {
        //Richiamo sui figli del nodo
        isSubTree = true;
        if (!BT.sinistroVuoto(n)) checkSubTree(BT, subBT, BT.figlioSinistro(n), subBT.radice(), isSubTree);
        if (!isSubTree && !BT.destroVuoto(n)) {
            isSubTree = true;
            checkSubTree(BT, subBT, BT.figlioDestro(n), subBT.radice(), isSubTree);
        }
    }
}

#endif //REALIZZAZIONI_SOTTOALBERO_H
