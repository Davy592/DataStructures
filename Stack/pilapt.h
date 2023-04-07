#ifndef REALIZZAZIONI_PILAPT_H
#define REALIZZAZIONI_PILAPT_H

#include <ostream>
#include <stdexcept>
#include <iostream>

using namespace std;

template<class T>
class pilapt;

template<class T>
class cella {
    friend class pilapt<T>;

public:
    typedef T tipoelem;
    tipoelem getValore() const;

    cella<tipoelem> *getSuccessivo() const;

private:
    tipoelem valore;
    cella<tipoelem> *successivo;
};

template<class T>
typename cella<T>::tipoelem cella<T>::getValore() const {
    return valore;
}

template<class T>
cella<T> *cella<T>::getSuccessivo() const {
    return successivo;
}


/////////////////////////////////////////////////////////////////////////////

template<class T>
class pilapt {
public:
    typedef T tipoelem;
    //costruttore
    pilapt();
    //costruttore copia
    pilapt(const pilapt<T> &);
    //distruttore
    ~pilapt();

    //operatori
    void creaPila();
    bool pilaVuota() const;
    tipoelem leggiPila() const;
    void fuoriPila();
    void insPila(const tipoelem &);
    void inPila(const tipoelem &);


    //funzioni accessorie e sovrascrizione operatori
    template<class T1>
    friend ostream &operator<<(ostream &, const pilapt<T1> &);

    pilapt<T> &operator=(const pilapt<T> &);

    bool operator==(const pilapt<T> &);

    int lunghezza();

    bool esiste(const tipoelem &e) {
        cella<T> *tmp = this->testa;
        while (tmp != nullptr) {
            if (tmp->getValore() == e) return true;
            else tmp = tmp->getSuccessivo();
        }
        return false;
    }

private:
    cella<T> *testa;

};


template<class T>
int pilapt<T>::lunghezza() {
    cella<T> *tmp = testa;
    int i = 0;
    while (tmp != nullptr) {
        tmp = tmp->successivo;
        i++;
    }
    return i;
}

template<class T>
pilapt<T>::pilapt() {
    creaPila();
}


template<class T>
pilapt<T>::pilapt(const pilapt<T> &pl) {
    //testa=pl.testa;
    pilapt<T> tmp;
    testa = nullptr;
    // verifico che la pila copiata non e' vuota
    if (!pl.pilaVuota()) {
        cella<T> *nodo_letto = pl.testa;

        while (nodo_letto != nullptr) {
            tmp.insPila(nodo_letto->valore);
            nodo_letto = nodo_letto->successivo;
        }
        nodo_letto = tmp.testa;
        while (nodo_letto != nullptr) {
            this->insPila(nodo_letto->valore);
            nodo_letto = nodo_letto->successivo;
        }
    }
}

template<class T>
pilapt<T>::~pilapt() {
    while (!pilaVuota()) {
        fuoriPila();
    }
}

template<class T>
void pilapt<T>::creaPila() {
    testa = nullptr;
}

template<class T>
bool pilapt<T>::pilaVuota() const {
    return (testa == nullptr);
}


template<class T>
typename pilapt<T>::tipoelem pilapt<T>::leggiPila() const {
    if (testa != nullptr) {
        return testa->valore;
    } else throw std::out_of_range("PILA VUOTA");
}


template<class T>
void pilapt<T>::fuoriPila() {
    if (testa != nullptr) {
        cella<T> *tmp = testa; //memorizzo la vecchia testa per poterla poi eliminare
        testa = testa->successivo;
        tmp = nullptr;
        delete tmp;

    } else throw std::out_of_range("PILA VUOTA");
}

template<class T>
void pilapt<T>::insPila(const pilapt<T>::tipoelem &e) {
    cella<T> *t = new cella<T>;
    t->valore = e;
    t->successivo = testa;
    testa = t;
};

template<class T>
void pilapt<T>::inPila(const pilapt<T>::tipoelem &el) {
    bool trov = false;
    cella<T> *tmp = testa;
    while (tmp != nullptr && !trov) {
        if (tmp->valore == el) trov = true;
        else tmp = tmp->successivo;
    }
    if (!trov) this->insPila(el);
    tmp = nullptr;
    delete tmp;

}


template<class T>
ostream &operator<<(ostream &os, const pilapt<T> &pl) {
    os << "[";
    cella<T> *tmp = pl.testa;
    while (tmp != nullptr) {
        if (tmp != pl.testa) os << "," << tmp->getValore();
        else os << tmp->getValore();
        tmp = tmp->getSuccessivo();
    }
    os << "]" << endl;
    tmp = nullptr;
    delete tmp;
    return os;
}

template<class T>
pilapt<T> &pilapt<T>::operator=(const pilapt<T> &pl) {
    if (this != &pl) {
        pilapt<T> tmp;
        testa = nullptr;
        // verifico che la pila copiata non e' vuota
        if (!pl.pilaVuota()) {
            cella<T> *nodo_letto = pl.testa;

            while (nodo_letto != nullptr) {
                tmp.insPila(nodo_letto->valore);
                nodo_letto = nodo_letto->successivo;
            }
            nodo_letto = tmp.testa;
            this->~pilapt();
            while (nodo_letto != nullptr) {
                this->insPila(nodo_letto->valore);
                nodo_letto = nodo_letto->successivo;
            }


        }
    }
    return *this;
}

template<class T>
bool pilapt<T>::operator==(const pilapt<T> &pl) {

    cella<T> *tmp1 = new cella<T>;
    tmp1 = testa;

    cella<T> *tmp2 = new cella<T>;
    tmp2 = pl.testa;
    while (tmp1 != nullptr && tmp2 != nullptr) {
        if (tmp1->valore != tmp2->valore) {
            tmp1 = nullptr;
            tmp2 = nullptr;
            delete tmp1, tmp2;
            return false;
        } else {
            tmp1 = tmp1->successivo;
            tmp2 = tmp2->successivo;
        }
    }
    if (tmp1 == tmp2) {
        tmp1 = nullptr;
        tmp2 = nullptr;
        delete tmp1, tmp2;
        return true;
    } else {
        tmp1 = nullptr;
        tmp2 = nullptr;
        delete tmp1, tmp2;
        return false;
    }

}


#endif //REALIZZAZIONI_PILAPT_H
