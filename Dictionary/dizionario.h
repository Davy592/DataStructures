#ifndef REALIZZAZIONI_DIZIONARIO_H
#define REALIZZAZIONI_DIZIONARIO_H

#include <ostream>
#include "../List/List_vector.h"
#include <string>

using namespace std;

//K = chiave, E = elemento
template<class K, class E>
class mypair {

public:
    typedef K chiave;
    typedef E valore;

    mypair() {};

    mypair(const mypair<K, E> &coppia) {
        k = coppia.k;
        e = coppia.e;
    }

    mypair(K chiave, E valore) {
        this->k = chiave;
        this->e = valore;
    }

    K getChiave() const {
        return k;
    }

    E getValore() const {
        return e;
    }

    void setChiave(const chiave k) {
        this->k = k;
    }

    void setValore(const valore e) {
        this->e = e;
    }

    bool operator==(const mypair<K, E> &);

    template<class K1, class E1>
    mypair<K, E> &operator=(mypair<K, E> &coppia_copiata) {
        if (this != &coppia_copiata) {
            k = coppia_copiata.k;
            e = coppia_copiata.e;
        }
        return *this;
    }


    template<class K1, class E1>
    friend ostream &operator<<(ostream &, mypair<K1, E1> &);

private:
    chiave k;
    valore e;
};

template<class K, class E>
bool mypair<K, E>::operator==(const mypair<K, E> &coppia) {
    return ((coppia.getValore() == this->getValore()) && (coppia.getChiave() == this->getChiave()));
}


template<class K, class E>
ostream &operator<<(ostream &os, mypair<K, E> &coppia) {
    os << "<Chiave:" << coppia.getChiave() << ", Valore:" << coppia.getValore() << "> ";
    return os;
}


template<class K, class E>
class dizionario {
public:
    typedef K chiave;
    typedef E valore;

    // virtual void creaDizionario()=0;  Rimpiazzato dal costruttore
    virtual bool dizionarioVuoto() const = 0;

    virtual int trovaPosizione(const K) const = 0;

    virtual void inserisci(mypair<K, E> &) = 0;

    virtual void cancella(const K) = 0;

    virtual bool ricerca(const K) const = 0;

    //ACCESSORIE
    virtual bool contieneValore(const E &) const = 0;
    virtual int dimensione() const = 0;
    //restituisce la lista dei valori memorizzati nel dizionario
    virtual List_vector<E> values() const = 0;
    //restituisce la lista delle chiavi memorizzate nel dizionario
    virtual List_vector<K> keys() const = 0;
};

#endif //REALIZZAZIONI_DIZIONARIO_H
