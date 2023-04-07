#ifndef REALIZZAZIONI_CODAP_H
#define REALIZZAZIONI_CODAP_H

#include <stdexcept>
#include <ostream>

using namespace std;

template<class T>
class codap;

template<class T>
class Nodo_coda {

private:
    friend class codap<T>;

public:
    typedef T tipoelem;

    tipoelem getValore() const;

    Nodo_coda<T> *getSuccessivo() const;

    void setValore(tipoelem valore);

    void setSuccessivo(Nodo_coda<T> *successivo);

private:
    tipoelem valore;
    Nodo_coda<T> *successivo;
};


template<class T>
typename Nodo_coda<T>::tipoelem Nodo_coda<T>::getValore() const {
    return valore;
}

template<class T>
Nodo_coda<T> *Nodo_coda<T>::getSuccessivo() const {
    return successivo;
}

template<class T>
void Nodo_coda<T>::setValore(tipoelem valore) {
    Nodo_coda::valore = valore;
}

template<class T>
void Nodo_coda<T>::setSuccessivo(Nodo_coda<T> *successivo) {
    Nodo_coda::successivo = successivo;
}


template<class T>
class codap {
public:
    typedef T tipoelem;

    codap();

    //costruttore per copia (rimpiazza il creaCoda)
    codap(const codap<T> &);

    //distruttore
    ~codap();

    bool codavuota() const;

    tipoelem leggiCoda() const;

    void fuoriCoda();

    void incoda(const tipoelem &);

    //funzioni aggiuntive
    int lunghezza() const;
    bool esiste(const tipoelem &);

    codap<T> &operator=(const codap<T> &);

    bool operator==(const codap<T> &);

    template<class T1>
    friend ostream &operator<<(ostream &, const codap<T1> &);

private:
    Nodo_coda<T> *testa;
    Nodo_coda<T> *coda;
    int lunghezzaLista;

};

template<class T>
codap<T>::codap() {
    testa = nullptr;
    coda = nullptr;
    lunghezzaLista = 0;
}

template<class T>
codap<T>::codap(const codap<T> &c) {
    testa = nullptr;
    coda = nullptr;
    lunghezzaLista = c.lunghezzaLista;
    if (!c.codavuota()) {
        Nodo_coda<T> *nodoCopiato;
        nodoCopiato = c.testa;
        while (nodoCopiato != nullptr) {
            incoda(nodoCopiato->valore);
            nodoCopiato = nodoCopiato->successivo;
        }
    }
}

template<class T>
codap<T>::~codap() {
    while (!codavuota()) {
        fuoriCoda();
    }
}

template<class T>
bool codap<T>::codavuota() const {
    return testa == nullptr;
}

template<class T>
typename codap<T>::tipoelem codap<T>::leggiCoda() const {
    if (testa != nullptr) {
        return testa->valore;
    } else throw std::out_of_range("CODA VUOTA");
}

template<class T>
void codap<T>::fuoriCoda() {
    if (lunghezzaLista >= 1) {
        Nodo_coda<T> *tmp = testa;
        testa = testa->successivo;
        delete tmp;
        if (testa == nullptr) coda = nullptr;
        lunghezzaLista--;
    } else throw std::out_of_range("CODA VUOTA");
}

template<class T>
bool codap<T>::esiste(const tipoelem &e) {
    if (!codavuota()) {
        Nodo_coda<T> *tmp = testa;
        bool trov = false;
        while (tmp != nullptr && !trov) {
            if (tmp->valore == e) trov = true;
            else tmp = tmp->successivo;
        }
        return trov;
    } else return false;
}

template<class T>
void codap<T>::incoda(const tipoelem &e) {
    Nodo_coda<T> *n = new Nodo_coda<T>;
    n->valore = e;
    n->successivo = nullptr;
    if (codavuota()) {
        testa = n;
        coda = n;
    } else {
        coda->successivo = n;
        coda = n;
    }
    lunghezzaLista++;
}

//funzioni aggiuntive
template<class T>
int codap<T>::lunghezza() const {
    return lunghezzaLista;
}

template<class T>
codap<T> &codap<T>::operator=(const codap<T> &c) {
    if (this != &c) {
        this->~codap();
        testa = nullptr;
        coda = nullptr;
        lunghezzaLista = c.lunghezzaLista;
        if (!c.codavuota()) {
            Nodo_coda<T> *nodoCopiato;
            nodoCopiato = c.testa;
            while (nodoCopiato != nullptr) {
                incoda(nodoCopiato->valore);
                nodoCopiato = nodoCopiato->successivo;
            }
        }
    }
    return *this;
}

template<class T>
bool codap<T>::operator==(const codap<T> &c) {
    if (lunghezzaLista != c.lunghezzaLista) return false;
    else {
        Nodo_coda<T> *tmp1 = testa, *tmp2 = coda;
        while (tmp1 != nullptr) {
            if (tmp1->valore != tmp2->valore) return false;
        }
        return true;

    }
}

template<class T1>
ostream &operator<<(ostream &os, const codap<T1> &c) {
    Nodo_coda<T1> *tmp = c.testa;
    os << "[";
    {
        while (tmp != nullptr) {
            if (tmp == c.testa) {
                os << tmp->getValore();
            } else os << "," << tmp->getValore();
            tmp = tmp->getSuccessivo();
        }
    }
    os << "]" << endl;
    return os;
}


#endif //REALIZZAZIONI_CODAP_H
