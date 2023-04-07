#ifndef REALIZZAZIONI_ALBEROPT_H
#define REALIZZAZIONI_ALBEROPT_H

#include "Albero.h"
#include <stdexcept>
#include <iostream>

template<class T>
class alberoPt;


template<class T>
class nodoT {
    friend class alberoPt<T>;

public:
    nodoT() {
        padre = nullptr;
        primofiglio = nullptr;
        fratello = nullptr;
    }

private:
    T valore;
    nodoT *padre;
    nodoT *primofiglio;
    nodoT *fratello;
};


template<class T>
class alberoPt : public Albero<T, nodoT<T> *> {
public:
    typedef typename Albero<T, nodoT<T> *>::tipoElem tipoElem;
    typedef typename Albero<T, nodoT<T> *>::nodo nodo;

    //costruttore
    alberoPt();

    //costruttore di copia
    alberoPt(alberoPt<T> &);

    //distruttore
    ~alberoPt();

    //void creaAlbero(); SOSTITUITO DAL COSTRUTTORE
    bool alberoVuoto() const;

    void inserisciRadice(tipoElem);

    nodo radice() const;

    nodo padre(nodo) const;

    bool foglia(nodo) const;

    nodo primoFiglio(nodo) const;

    bool ultimoFratello(nodo) const;

    nodo fratelloSuccessivo(nodo) const;

    void insFirstSubTree(nodo, Albero<tipoElem, nodoT<T> *> &);

    void insSubTree(nodo, Albero<tipoElem, nodoT<T> *> &);

    void cancSottoAlbero(nodo);

    void scriviNodo(nodo, tipoElem);

    tipoElem leggiNodo(nodo) const;

    int numeroNodi() const {
        return this->numNodi;
    }


    //FUNZIONI DI SERVIZIO
    void inserisciPrimoFiglio(nodo, tipoElem);
    void sommaLivello(nodo n, int liv, tipoElem *v);

    void stampaAlbero() const;

private:
    nodoT<T> *root;
    int numNodi;
    void inserisci(nodo, tipoElem);
    void copia(nodo, nodo);

    void stampa(nodo) const;

};


template<class T>
alberoPt<T>::~alberoPt() {
    if (numNodi > 0) cancSottoAlbero(root);
}

template<class T>
alberoPt<T>::alberoPt() {
    numNodi = 0;
    root = nullptr;
}

template<class T>
alberoPt<T>::alberoPt(alberoPt<T> &a) {
    root = nullptr;
    root = new nodoT<T>();
    numNodi = 0;
    scriviNodo(root, a.leggiNodo(a.radice()));
    if (!a.foglia(a.radice())) copia(root, a.primoFiglio(a.radice()));
    numNodi++;

}

template<class T>
void alberoPt<T>::copia(nodo n, nodo daCopiare) {
    if (daCopiare != nullptr) {
        if (daCopiare->fratello != nullptr)
            copia(n, daCopiare->fratello);
        inserisciPrimoFiglio(n, daCopiare->valore);
        if (daCopiare->primofiglio != nullptr)
            copia(primoFiglio(n), daCopiare->primofiglio);

    }
}


template<class T>
void alberoPt<T>::inserisciPrimoFiglio(nodo n, tipoElem e) {
    nodo l = new nodoT<T>();
    l->fratello = n->primofiglio;
    n->primofiglio = l;
    l->padre = n;
    l->valore = e;
    numNodi++;
}


template<class T>
bool alberoPt<T>::alberoVuoto() const {
    return (root == nullptr);
};

template<class T>
void alberoPt<T>::inserisciRadice(tipoElem e) {
    if (alberoVuoto()) {
        root = new nodoT<T>;
        root->valore = e;
        root->fratello = nullptr;
        root->padre = nullptr;
        root->primofiglio = nullptr;
        numNodi++;
    }

}

template<class T>
typename alberoPt<T>::nodo alberoPt<T>::radice() const {
    return root;
}

template<class T>
typename alberoPt<T>::nodo alberoPt<T>::padre(nodo n) const {
    if (n->padre != nullptr) {
        return n->padre;
    } else throw std::out_of_range("LA RADICE NON HA PADRE");
}

template<class T>
bool alberoPt<T>::foglia(nodo n) const {
    return (n->primofiglio == nullptr);
}

template<class T>
typename alberoPt<T>::nodo alberoPt<T>::primoFiglio(nodo n) const {
    if (n->primofiglio != nullptr) {
        return n->primofiglio;
    } else throw std::out_of_range("IL NODO E' UNA FOGLIA");
}

template<class T>
bool alberoPt<T>::ultimoFratello(nodo n) const {
    return (n->fratello == nullptr);
}

template<class T>
typename alberoPt<T>::nodo alberoPt<T>::fratelloSuccessivo(nodo n) const {
    if (n->fratello != nullptr) {
        return n->fratello;
    } else throw std::out_of_range("IL NODO NON HA FRATELLI SUCCESSIVI");
}

template<class T>
void alberoPt<T>::insFirstSubTree(nodo n, Albero<tipoElem, nodoT<T> *> &a) {
    if (!alberoVuoto() && !a.alberoVuoto()) {
        //nodo r1 = a.radice();
        nodoT<T> *r1 = new nodoT<T>();
        scriviNodo(r1, a.leggiNodo(a.radice()));
        if (!a.foglia(a.radice())) copia(r1, a.primoFiglio(a.radice()));
        r1->padre = n;
        r1->fratello = n->primofiglio;
        n->primofiglio = r1;
        numNodi++;
    } else throw std::out_of_range("UNO DEI DUE ALBERI E' VUOTO, OPERAZIONE IMPOSSIBILE");
}


template<class T>
void alberoPt<T>::insSubTree(nodo n, Albero<tipoElem, nodoT<T> *> &a) {
    if (!alberoVuoto() && !a.alberoVuoto()) {
        if (n != root) {
            // nodo r1 = a.radice();
            nodoT<T> *r1 = new nodoT<T>();
            scriviNodo(r1, a.leggiNodo(a.radice()));
            if (!a.foglia(a.radice())) copia(r1, a.primoFiglio(a.radice()));
            r1->fratello = n->fratello;
            r1->padre = n->padre;
            n->fratello = r1;
            numNodi++;
        } else throw std::out_of_range("LA RADICE NON PUO AVERE FRATELLI");
    } else throw std::out_of_range("UNO DEI DUE ALBERI E' VUOTO, OPERAZIONE IMPOSSIBILE");
}

template<class T>
void alberoPt<T>::cancSottoAlbero(nodo n) {
    if (root != nullptr) {
        while (n->primofiglio != nullptr) {
            cancSottoAlbero(n->primofiglio);
        }
        if (n != root) {
            if (n->fratello == nullptr) n->padre->primofiglio->fratello = nullptr;
            if (n->padre->primofiglio == n) n->padre->primofiglio = n->fratello;
        }
        delete n;
        numNodi--;
    }
}


template<class T>
void alberoPt<T>::scriviNodo(nodo n, tipoElem e) {
    n->valore = e;
}

template<class T>
typename alberoPt<T>::tipoElem alberoPt<T>::leggiNodo(nodo n) const {
    return n->valore;
}


template<class T>
void alberoPt<T>::stampaAlbero() const {
    if (root != nullptr) {
        std::cout << "[";
        stampa(root);
        std::cout << "]" << std::endl;
    } else std::cout << "ALBERO VUOTO";
}

template<class T>
void alberoPt<T>::stampa(nodo n) const {
    if (n != nullptr) std::cout << n->valore << " ";
    if (n->fratello != nullptr) {
        stampa(n->fratello);
    }
    if (n->primofiglio != nullptr) {
        stampa(n->primofiglio);
    }
}

template<class T>
void alberoPt<T>::sommaLivello(nodo n, int liv, tipoElem *v) {
    if (n != nullptr) v[liv] += leggiNodo(n);
    if (n->fratello != nullptr) sommaLivello(n->fratello, liv, v);
    if (n->primofiglio != nullptr) sommaLivello(n->primofiglio, liv + 1, v);
}

#endif //REALIZZAZIONI_ALBEROPT_H
