#ifndef REALIZZAZIONI_SET_H
#define REALIZZAZIONI_SET_H

#include <ostream>
#include "../Dictionary/hashtableChiuso.h"

using namespace std;

template<class T>
class set;

template<class T>
class nodo {
    friend class set<T>;

    template<class T1>
    friend ostream &operator<<(ostream &, const set<T1> &);

public:
    nodo() = default;

private:
    T e;
    nodo<T> *successivo;
    nodo<T> *precedente;
};

template<class T>
class set {
public:
    typedef T tipoelem;

    //costruttore (creaInsieme)
    set();

    //costruttore copia
    set(const set &);


    //distruttore
    ~set();

    bool insiemeVuoto() const;
    bool appartiene(const tipoelem &) const;
    void inserisci(const tipoelem &);
    void cancella(const tipoelem &);
    set<T> unione(set<T> &);
    set<T> intersezione(set<T> &);
    set<T> differenza(set<T> &);
    bool sottinsieme(set<T> &);

    //sovraccarico
    template<class T1>
    friend ostream &operator<<(ostream &, const set<T1> &);

    bool operator==(const set &);

    set &operator=(const set &);

    //funzioni accessorie
    nodo<T> *ultimo() const;

private:
    nodo<T> *h;                //L'insieme non ha un inizio, ma in programmazione serve
    int lunghezzaSet;

};


template<class T>
set<T>::set() {
    h = nullptr;
    lunghezzaSet = 0;
}

template<class T>
set<T>::set(const set<T> &set2) {
    h = nullptr;
    lunghezzaSet = set2.lunghezzaSet;
    if (set2.insiemeVuoto() == false) {
        nodo<T> *nodo_assegnato;
        nodo_assegnato = set2.h;

        // copio tutti i nodi dell'insieme
        while (nodo_assegnato != nullptr) {
            // creo il nodo da inserie
            nodo<T> *nodo_inserito;
            nodo_inserito = new nodo<T>;

            // assegno i valori al nodo
            nodo_inserito->e = nodo_assegnato->e;
            nodo_inserito->successivo = nullptr;

            // inserisco il nodo nella lista
            if (h == nullptr) {
                h = nodo_inserito;
            } else {
                // inserisco in fondo il nodo
                nodo<T> *nodo_confronto;
                nodo_confronto = h;

                while (nodo_confronto->successivo != nullptr) {
                    nodo_confronto = nodo_confronto->successivo;
                }
                nodo_confronto->successivo = nodo_inserito;
            }
            nodo_assegnato = nodo_assegnato->successivo;
        }
    }
}


template<class T>
set<T>::~set() {
    if (h != nullptr) {
        nodo<T> *tmp = h;
        while (h != nullptr) {
            tmp = h;
            h = h->successivo;
            delete tmp;
        }
    }
}


template<class T>
void set<T>::inserisci(const tipoelem &v) {
    if (!appartiene(v)) {
        nodo<T> *tmp = new nodo<T>;
        tmp->e = v;
        tmp->precedente = nullptr;
        tmp->successivo = h;
        h = tmp;
        lunghezzaSet++;
    }
}

template<class T>
bool set<T>::appartiene(const tipoelem &e) const {
    nodo<T> *tmp = h;
    bool trov = false;
    while (tmp != nullptr && !trov) {
        if (tmp->e == e) {
            trov = true;
        } else {
            tmp = tmp->successivo;
        }
    }
    return trov;
}

template<class T>
void set<T>::cancella(const tipoelem &v) {
    if (appartiene(v)) {
        nodo<T> *tmp = h;
        while (tmp->e != v) {
            tmp = tmp->successivo;
        }
        if (tmp == h) h = tmp->successivo;
        else tmp->precedente->successivo = tmp->successivo;
        delete tmp;
        lunghezzaSet--;
    }
}

template<class T>
bool set<T>::insiemeVuoto() const {
    return (lunghezzaSet == 0);
}


template<class T>
set<T> set<T>::unione(set<T> &b) {
    set<T> insiemeUnione;
    if (insiemeVuoto() == false || b.insiemeVuoto() == false) {
        nodo<T> *tmp;
        tmp = h;
        while (tmp != nullptr) {
            insiemeUnione.inserisci(tmp->e);
            tmp = tmp->successivo;
        }

        nodo<T> *tmp2;
        tmp2 = b.h;
        while (tmp2 != nullptr) {
            if (!insiemeUnione.appartiene(tmp2->e)) {
                insiemeUnione.inserisci(tmp2->e);
            }
            tmp2 = tmp2->successivo;
        }
    }
    return insiemeUnione;
}

template<class T>
set<T> set<T>::intersezione(set<T> &b) {
    set<T> insiemeIntersezione;

    // verifico che almeno uno dei due insiemi non sia vuoto
    if (insiemeVuoto() == false || b.insiemeVuoto() == false) {
        // leggo i valori dal primo insieme
        nodo<T> *nodo_a;
        nodo_a = h;

        while (nodo_a != nullptr) {
            // inserisco solo gli elementi in comune con b
            if (b.appartiene(nodo_a->e) == true) {
                insiemeIntersezione.inserisci(nodo_a->e);
            }
            nodo_a = nodo_a->successivo;
        }
    }
    return insiemeIntersezione;
}

template<class T>
set<T> set<T>::differenza(set<T> &b) {
    set<T> insieme_differenza;

    // verifico che almeno uno dei due insiemi non sia vuoto
    if (insiemeVuoto() == false || b.insiemeVuoto() == false) {
        // leggo i valori dal primo insieme
        nodo<T> *nodo_a;
        nodo_a = h;

        while (nodo_a != nullptr) {
            // inserisco solo gli elementi che appartengono ad 'a' ma non a 'b'
            if (b.appartiene(nodo_a->e) == false) {
                insieme_differenza.inserisci(nodo_a->e);
            }
            nodo_a = nodo_a->successivo;
        }
    }
    return insieme_differenza;
}


template<class T>
nodo<T> *set<T>::ultimo() const {
    nodo<T> *tmp = h;
    while (tmp->successivo != nullptr) {
        tmp = tmp->successivo;
    }
    return tmp;
}


template<class T1>
ostream &operator<<(ostream &os, const set<T1> &s) {
    nodo<T1> *tmp = s.h;
    os << "{";
    while (tmp != nullptr) {
        if (tmp == s.h) os << tmp->e;
        else os << ", " << tmp->e;
        tmp = tmp->successivo;
    }
    os << "}" << endl;
    return os;
}

template<class T>
bool set<T>::operator==(const set &s) {
    if (lunghezzaSet != s.lunghezzaSet) return false;
    else {
        nodo<T> *tmp1 = h, *tmp2 = s.h;
        while (tmp1 != nullptr && tmp2 != nullptr) {
            if (tmp1->e != tmp2->e) return false;
            tmp2 = tmp2->successivo;
            tmp1 = tmp1->successivo;
        }
    }
    return true;
}


template<class T>
set<T> &set<T>::operator=(const set<T> &e) {
    if (this != &e) {
        this->~set();
        h = nullptr;
        lunghezzaSet = e.lunghezzaSet;
        if (e.insieme_vuoto() == false) {
            nodo<T> *nodo_assegnato;
            nodo_assegnato = e.h;

            // copio tutti i nodi dell'insieme
            while (nodo_assegnato != nullptr) {
                // creo il nodo da inserie
                nodo<T> *nodo_inserito;
                nodo_inserito = new nodo<T>;

                // assegno i valori al nodo
                nodo_inserito->valore_nodo = nodo_assegnato->valore_nodo;
                nodo_inserito->successivo = nullptr;

                // inserisco il nodo nella lista
                if (h == nullptr) {
                    h = nodo_inserito;
                } else {
                    // inserisco in fondo il nodo
                    nodo<T> *nodo_confronto;
                    nodo_confronto = h;

                    while (nodo_confronto->successivo != nullptr) {
                        nodo_confronto = nodo_confronto->successivo;
                    }
                    nodo_confronto->successivo = nodo_inserito;
                }
                nodo_assegnato = nodo_assegnato->successivo;
            }
        }
    }
    return *this;
}

template<class T>
bool set<T>::sottinsieme(set<T> &S2) {
    hash_table<T, T> mappa;
    //riempio la mappa con gli elementi di S2
    nodo<T> *tmp = S2.h;
    while (tmp != nullptr) {
        mypair<T, T> coppia(tmp->e, tmp->e);
        mappa.inserisci(coppia);
        tmp = tmp->successivo;
    }

    //ORA CONTROLO
    tmp = this->h;
    while (tmp != nullptr) {
        if (!mappa.contieneValore(tmp->e)) return false;
        else tmp = tmp->successivo;
    }
    return true;
}


#endif //REALIZZAZIONI_SET_H
