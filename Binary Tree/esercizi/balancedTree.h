#ifndef REALIZZAZIONI_BALANCEDTREE_H
#define REALIZZAZIONI_BALANCEDTREE_H

#include "../alberoBinario_pt.h"

template<class T>
class balanced_tree {
public:
    /*
     * Bilanciato in altezza
     * TRUE : vuoto oppure h(sottoSinistro)-h(sottoDestro)=1 o 0
     * FALSE: altrimenti
     */
    bool isHeight_balanced(const alberoBinario_pt<T> &B);

    /*
     * TRUE SE TUTTI I NON NODI FOGLIA HANNO ESATTAMENTE DUE FIGLI
     */
    bool complete_nodes(const alberoBinario_pt<T> &B);
private:
    void complete_nodes2(const alberoBinario_pt<T> &B, typename alberoBinario_pt<T>::nodo, bool &);
    void isHeight_balanced2(const alberoBinario_pt<T> &B, typename alberoBinario_pt<T>::nodo, bool &);
};


template<class T>
bool balanced_tree<T>::isHeight_balanced(const alberoBinario_pt<T> &B) {
    bool h_balanced = true;
    if (!B.alberoBinVuoto())
        isHeight_balanced2(B, B.radice(), h_balanced);
    return h_balanced;
}

/*
     * Bilanciato in altezza
     * TRUE : h(sottoSinistro)-h(sottoDestro)=1 o 0
     * FALSE: altrimenti
     */
template<class T>
void balanced_tree<T>::isHeight_balanced2(const alberoBinario_pt<T> &B, typename alberoBinario_pt<T>::nodo n,
                                          bool &h_balanced) {
    if (h_balanced) {
        if (B.sinistroVuoto(n) && B.destroVuoto(n)) {
            return;
        } else {
            int hsx = 0, hdx = 0;
            if (!B.sinistroVuoto(n)) hsx = B.altezza_nodo(B, B.figlioSinistro(n));
            if (!B.destroVuoto(n)) hdx = B.altezza_nodo(B, B.figlioDestro(n));
            if (abs(hsx - hdx) <= 1) {
                if (!B.sinistroVuoto(n)) isHeight_balanced2(B, B.figlioSinistro(n), h_balanced);
                if (!B.destroVuoto(n)) isHeight_balanced2(B, B.figlioDestro(n), h_balanced);
            } else h_balanced = false;
        }
    } else return;

}


template<class T>
bool balanced_tree<T>::complete_nodes(const alberoBinario_pt<T> &B) {
    bool completo = true;
    if (!B.alberoBinVuoto()) {
        complete_nodes2(B, B.radice(), completo);
    } else completo = false;
    return completo;
}


template<class T>
void
balanced_tree<T>::complete_nodes2(const alberoBinario_pt<T> &B, typename alberoBinario_pt<T>::nodo n, bool &completo) {
    if (completo) {
        if (B.sinistroVuoto(n) && B.destroVuoto(n)) {
            return;
        } else {
            if (!B.sinistroVuoto(n) && !B.destroVuoto(n)) {
                complete_nodes2(B, B.figlioSinistro(n), completo);
                complete_nodes2(B, B.figlioDestro(n), completo);
            } else completo = false;
        }
    } else return;
}


#endif //REALIZZAZIONI_BALANCEDTREE_H
