#ifndef REALIZZAZIONI_ALBERO_H
#define REALIZZAZIONI_ALBERO_H

#include <vector>
#include <algorithm>

using namespace std;

template<class I, class N>
class Albero {
public:
    typedef I tipoElem;
    typedef N nodo;

    //virtual void creaAlbero () = 0; SOSTITUITO DAL COSTRUTTORE
    virtual bool alberoVuoto() const = 0;
    virtual void inserisciRadice(tipoElem) = 0;
    virtual nodo radice() const = 0;
    virtual nodo padre(nodo) const = 0;
    virtual bool foglia(nodo) const = 0;
    virtual nodo primoFiglio(nodo) const = 0;
    virtual bool ultimoFratello(nodo) const = 0;
    virtual nodo fratelloSuccessivo(nodo) const = 0;
    virtual void insFirstSubTree(nodo, Albero<I, N> &) = 0;
    virtual void insSubTree(nodo, Albero<I, N> &) = 0;
    virtual void cancSottoAlbero(nodo) = 0;
    virtual int numeroNodi() const = 0;
    virtual void scriviNodo(nodo, tipoElem) = 0;
    virtual tipoElem leggiNodo(nodo) const = 0;
    int profonditaAlbero();
    int larghezza();


private:
    int profondita(nodo);
    void larghezza(nodo, vector<int> &, int);

};

template<class I, class N>
int Albero<I, N>::profonditaAlbero() {
    if (alberoVuoto())
        return 0;
    else {
        return profondita(radice());
    }
}

template<class I, class N>
int Albero<I, N>::profondita(Albero::nodo n) {
    if (foglia(n)) return 0;
    int m = 1;
    int c;
    nodo k = primoFiglio(n);
    while (!ultimoFratello(k)) {
        c = profondita(k);
        if (c > m) {
            m = c;
        }
        k = fratelloSuccessivo(k);
    }
    c = profondita(k);
    if (c > m) {
        m = c;
    }
    return (m + 1);
}


template<class I, class N>
int Albero<I, N>::larghezza() {
    if (!alberoVuoto()) {
        vector<int> vet;
        larghezza(radice(), vet, 0);
        return *max_element(vet.begin(), vet.end());
    } else return 0;
}


template<class I, class N>
void Albero<I, N>::larghezza(Albero::nodo n, vector<int> &v, int liv) {
    if (liv >= v.size()) v.push_back(0);
    while (!ultimoFratello(n)) {
        v[liv]++;
        if (!foglia(n)) {
            larghezza(primoFiglio(n), v, liv + 1);
        }
        n = fratelloSuccessivo(n);
    }
    v[liv]++;
    if (!foglia(n)) {
        larghezza(primoFiglio(n), v, liv + 1);
    }
}


#endif //REALIZZAZIONI_ALBERO_H
