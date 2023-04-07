#ifndef REALIZZAZIONI_ALBEROBINARIO_H
#define REALIZZAZIONI_ALBEROBINARIO_H

#include <iostream>
#include <ostream>
#include "../List/List_vector.h"
#include <vector>
#include <algorithm>

using namespace std;


template<class T, class N>
class alberoBin {
public:
    //TIPO
    typedef T tipoElem;
    typedef N nodo;

    //OPERATORI
    //virtual void crea()=0; SOSTITUITO DAL COSTRUTTORE
    virtual bool alberoBinVuoto() const = 0;
    virtual nodo radice() const = 0;
    virtual nodo genitore(nodo) const = 0; //padre
    virtual nodo figlioSinistro(nodo) const = 0;
    virtual nodo figlioDestro(nodo) const = 0;
    virtual bool sinistroVuoto(nodo) const = 0;
    virtual bool destroVuoto(nodo) const = 0;
    virtual void cancellaSottoalbero(nodo) = 0;
    virtual tipoElem leggiNodo(nodo) const = 0;
    virtual void scriviNodo(const nodo, tipoElem) = 0;

    virtual void inserisciRadice(tipoElem) = 0;
    virtual void inserisciSinistro(const nodo, tipoElem) = 0;
    virtual void inserisciDestro(const nodo, tipoElem) = 0;

    //FUNZIONI DI SERVIZIO
    void visita(int);

    int foglie_verdi(alberoBin<T, N> &);
    int level_red(alberoBin<T, N> &);

    virtual void inverti() = 0;

    int profondita_nodo(alberoBin<T, N> &, nodo);
    int altezza_nodo(const alberoBin<T, N> &, nodo) const;
    List_vector<T> mediaLivello(alberoBin<T, N> &);
    //SOVRACCARICO STAMPA (usa di default la preVisita)
    template<class T1, class N1>
    friend ostream &operator<<(ostream &, alberoBin<T1, N1> &);

    bool checkSottoalbero(alberoBin<T, N> &b1);

private:
    void stampa(nodo, std::ostream &);
    void preVisita(nodo);
    void postVisita(nodo);
    void visitaSimmetrica(nodo);
    int foglie_verdi(alberoBin<T, N> &, const nodo);
    int level_red(alberoBin<T, N> &, const nodo, int);

    void numNodiInLiv(alberoBin<T, N> &, nodo, int, int &);
    void sommaLivello(alberoBin<T, N> &, nodo, int, T[]);

};


template<class T, class N>
void alberoBin<T, N>::visita(int scelta) {
    if (!alberoBinVuoto()) {
        switch (scelta) {
            case 1:
                preVisita(radice());
                break;
            case 2:
                postVisita(radice());
                break;
            case 3:
                visitaSimmetrica(radice());
                break;
            default:
                throw std::out_of_range("SCELTA NON ESISTENTE");
        }
    } else cout << "ALBERO VUOTO" << endl;

}


template<class T, class N>
void alberoBin<T, N>::preVisita(nodo n) {
    cout << leggiNodo(n) << " ";
    if (!sinistroVuoto(n)) preVisita(figlioSinistro(n));
    if (!destroVuoto(n)) preVisita(figlioDestro(n));
}


template<class T, class N>
void alberoBin<T, N>::postVisita(nodo n) {
    if (!sinistroVuoto(n)) postVisita(figlioSinistro(n));
    if (!destroVuoto(n)) postVisita(figlioDestro(n));
    cout << leggiNodo(n) << " ";
}

template<class T, class N>
void alberoBin<T, N>::visitaSimmetrica(nodo n) {
    if (!sinistroVuoto(n)) visitaSimmetrica(figlioSinistro(n));
    cout << leggiNodo(n) << " ";
    if (!destroVuoto(n)) visitaSimmetrica(figlioDestro(n));
}


//SOVRACCARICO STAMPA (usa di default la preVisita)
template<class T1, class N1>
ostream &operator<<(ostream &os, alberoBin<T1, N1> &T) {
    if (T.alberoBinVuoto())
        os << "ALBERO VUOTO" << endl;
    else
        os << "[ ";
    T.stampa(T.radice(), os);
    os << "] " << endl;
    return os;
}

template<class T, class N>
void alberoBin<T, N>::stampa(nodo n, std::ostream &os) {

    os << leggiNodo(n) << " ";
    if (!sinistroVuoto(n)) stampa(figlioSinistro(n), os);
    if (!destroVuoto(n)) stampa(figlioDestro(n), os);
}

template<class T, class N>
int alberoBin<T, N>::foglie_verdi(alberoBin<T, N> &BT) {
    if (alberoBinVuoto()) return 0;
    else return foglie_verdi(BT, BT.radice());
}


template<class T, class N>
int alberoBin<T, N>::foglie_verdi(alberoBin<T, N> &BT, const alberoBin::nodo n) {
    int sx = 0, dx = 0;
    if (sinistroVuoto(n) && destroVuoto(n)) {
        return (leggiNodo(n) == "verde");
    } else {
        if (!sinistroVuoto(n)) sx = foglie_verdi(BT, BT.figlioSinistro(n));
        if (!destroVuoto(n)) dx = foglie_verdi(BT, BT.figlioDestro(n));
        return (sx + dx);
    }
}


template<class T, class N>
int alberoBin<T, N>::level_red(alberoBin<T, N> &BT) {
    if (alberoBinVuoto()) return 0;
    else return level_red(BT, BT.radice(), 0);
}


template<class T, class N>
int alberoBin<T, N>::level_red(alberoBin<T, N> &BT, const nodo n, int livello) {
    int sx = 0, dx = 0, c = 0;
    if (sinistroVuoto(n) && destroVuoto(n))
        return 0;
    else {
        if ((livello % 2) == 0 && BT.leggiNodo(n) == "rosso") {
            if (!sinistroVuoto(n) && (BT.leggiNodo(BT.figlioSinistro(n)) == "bianco")) c = 1;
            if (!destroVuoto(n) && (BT.leggiNodo(BT.figlioDestro(n)) == "bianco")) c = 1;
        }
        if (!sinistroVuoto(n)) sx = level_red(BT, BT.figlioSinistro(n), (livello + 1));
        if (!destroVuoto(n)) dx = level_red(BT, BT.figlioDestro(n), (livello + 1));
        return (sx + dx + c);
    }
}

template<class T, class N>
int alberoBin<T, N>::profondita_nodo(alberoBin<T, N> &BT, nodo n) {
    if (!alberoBinVuoto()) {
        int c = 0;
        while (n != BT.radice()) {
            c++;
            n = BT.genitore(n);
        }
        return c;
    } else throw std::out_of_range("ALBERO VUOTO");
}

template<class T, class N>
int alberoBin<T, N>::altezza_nodo(const alberoBin<T, N> &BT, nodo n) const {
    if (!alberoBinVuoto()) {
        if (destroVuoto(n) && sinistroVuoto(n))
            return 0;
        else {
            int sx = 0, dx = 0;
            if (!sinistroVuoto(n)) {
                sx = altezza_nodo(BT, BT.figlioSinistro(n));
                sx++;
            }
            if (!destroVuoto(n)) {
                dx = altezza_nodo(BT, BT.figlioDestro(n));
                dx++;
            }
            return max(sx, dx);
        }
    } else throw std::out_of_range("ALBERO VUOTO");
}


template<class T, class N>
void alberoBin<T, N>::sommaLivello(alberoBin<T, N> &BT, nodo n, int liv, T *v) {
    v[liv] += BT.leggiNodo(n);
    if (!sinistroVuoto(n)) sommaLivello(BT, BT.figlioSinistro(n), liv + 1, v);
    if (!destroVuoto(n)) sommaLivello(BT, BT.figlioDestro(n), liv + 1, v);
}

template<class T, class N>
List_vector<T> alberoBin<T, N>::mediaLivello(alberoBin<T, N> &BT) {

    int dim = BT.altezza_nodo(BT, BT.radice()) + 1;
    double v[dim];
    for (int i = 0; i < dim; i++) {
        v[i] = 0;
    }
    BT.sommaLivello(BT, radice(), 0, v);
    List_vector<T> l;

    for (int i = 0; i < (BT.altezza_nodo(BT, BT.radice()) + 1); i++) {
        int c = 0;
        numNodiInLiv(BT, BT.radice(), i, c);
        l.inserisciCoda((double) v[i] / c);
    }
    return l;
}

template<class T, class N>
void alberoBin<T, N>::numNodiInLiv(alberoBin<T, N> &BT, nodo n, int liv, int &counter) {
    if (!sinistroVuoto(n)) numNodiInLiv(BT, BT.figlioSinistro(n), liv, counter);
    if (!destroVuoto(n)) numNodiInLiv(BT, BT.figlioSinistro(n), liv, counter);
    if (BT.profondita_nodo(BT, n) == liv) counter++;

}

#endif //REALIZZAZIONI_ALBEROBINARIO_H
