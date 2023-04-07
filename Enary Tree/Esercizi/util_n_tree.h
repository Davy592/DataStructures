#ifndef REALIZZAZIONI_UTIL_N_TREE_H
#define REALIZZAZIONI_UTIL_N_TREE_H

#include "../AlberoPt.h"

template<class T>
class util_n_tree {
public:
    typedef typename alberoPt<T>::nodo nodo;
    util_n_tree() = default;
    ~util_n_tree() = default;
    int n_leaf(alberoPt<T> &);
    int n_level(alberoPt<T> &, int k);

private:
    void n_leaf(alberoPt<T> &, nodo, int &);
    void n_level(alberoPt<T> &, nodo, int &, int, int);
};


template<class T>
int util_n_tree<T>::n_leaf(alberoPt<T> &A) {
    if (A.alberoVuoto()) return 0;
    else {
        int c = 0;
        n_leaf(A, A.radice(), c);
        return c;
    }
}

template<class T>
void util_n_tree<T>::n_leaf(alberoPt<T> &A, nodo n, int &c) {
    if (A.foglia(n)) c++;
    if (!A.ultimoFratello(n)) {
        n_leaf(A, A.fratelloSuccessivo(n), c);
    }
    if (!A.foglia(n)) {
        n_leaf(A, A.primoFiglio(n), c);
    }
}


template<class T>
int util_n_tree<T>::n_level(alberoPt<T> &A, int k) {
    if (A.alberoVuoto() && k <= A.profonditaAlbero()) return 0;
    else {
        int c = 0;
        n_level(A, A.radice(), c, k, 0);
        return c;
    }
}


template<class T>
void util_n_tree<T>::n_level(alberoPt<T> &A, nodo n, int &c, int liv, int nowLiv) {

    if (nowLiv == liv) c++;
    if (!A.ultimoFratello(n)) {
        n_level(A, A.fratelloSuccessivo(n), c, liv, nowLiv);
    }
    if (!A.foglia(n)) {
        n_level(A, A.primoFiglio(n), c, liv, nowLiv + 1);
    }
}

#endif //REALIZZAZIONI_UTIL_N_TREE_H
