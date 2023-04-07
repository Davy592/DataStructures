#ifndef REALIZZAZIONI_ORDERED_LIST_H
#define REALIZZAZIONI_ORDERED_LIST_H

#include "List_vector.h"
#include <iostream>
#include <ostream>

template<class T>
class Ordered_list {
public:
    typedef typename List_vector<T>::tipoelem tipoelem;
    typedef typename List_vector<T>::posizione posizione;
    //METODI
    void insList(const tipoelem &); // inserisce un elemento
    void cancLista(const tipoelem &); // rimuove un elemento
    bool ricerca(const tipoelem &); // cerca un elemento
    void fusione(const Ordered_list<T> &);  // fonde con una lista ordinata

    //Costruttore
    Ordered_list();
    //Distruttore
    ~Ordered_list();

    //override operatori
    template<class T1>
    friend ostream &operator<<(ostream &, const Ordered_list<T1> &);

private:
    List_vector<T> L;
};

template<class T1>
ostream &operator<<(ostream &os, const Ordered_list<T1> &l) {
    os << l.L;
    return os;

}

template<class T>
Ordered_list<T>::Ordered_list() = default;

template<class T>
Ordered_list<T>::~Ordered_list() = default;


template<class T>
void Ordered_list<T>::insList(const tipoelem &e) {
    posizione pos = L.primoLista();
    while (!L.fineLista(pos) && L.leggiLista(pos) < e) {
        pos = L.succLista(pos);
    }
    L.insLista(e, pos);
}

template<class T>
bool Ordered_list<T>::ricerca(const tipoelem &e) {
    posizione pos = L.primoLista();
    bool trov = false;
    while (!L.fineLista(pos) && !trov) {
        if (L.leggiLista(pos) == e) trov = true;
        else pos = L.succLista(pos);
    }
    return trov;
}

template<class T>
void Ordered_list<T>::cancLista(const tipoelem &e) {
    if (ricerca(e)) {
        posizione p = L.primoLista();
        bool continua = true;
        while (continua) {
            if (e == L.leggiLista(p)) {
                L.cancLista(p);
                continua = false;
            } else p = L.succLista(p);
        }
    }
}

template<class T>
void Ordered_list<T>::fusione(const Ordered_list<T> &l) {
    posizione p = l.L.primoLista();
    while (!l.L.fineLista(p)) {
        this->insList(l.L.leggiLista(p));
        p = l.L.succLista(p);
    }
}

#endif //REALIZZAZIONI_ORDERED_LIST_H
