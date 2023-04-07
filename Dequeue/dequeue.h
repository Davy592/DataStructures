#ifndef REALIZZAZIONI_DEQUEUE_H
#define REALIZZAZIONI_DEQUEUE_H

#include <ostream>
#include <stdexcept>

using namespace std;

template<class T>
class dequeue;

template<class T>
class Nodo_dequeue {
    friend class dequeue<T>;

public:
    typedef T tipoelem;
    tipoelem getValore() const;

    Nodo_dequeue<T> *getSuccessivo() const;

    Nodo_dequeue<T> *getPrecedente() const;

private:
    tipoelem valore;
    Nodo_dequeue<T> *successivo;
    Nodo_dequeue<T> *precedente;
};

template<class T>
typename Nodo_dequeue<T>::tipoelem Nodo_dequeue<T>::getValore() const {
    return valore;
}

template<class T>
Nodo_dequeue<T> *Nodo_dequeue<T>::getSuccessivo() const {
    return successivo;
}

template<class T>
Nodo_dequeue<T> *Nodo_dequeue<T>::getPrecedente() const {
    return precedente;
}


template<class T>
class dequeue {
public:
    typedef T tipoelem;

    dequeue();

    dequeue(const dequeue<T> &);

    ~dequeue();

    bool dequeueVuota() const;

    tipoelem leggiTesta() const;

    tipoelem leggiCoda() const;

    void fuoriTesta();

    void fuoriCoda();

    void insTesta(const tipoelem &);

    void insCoda(const tipoelem &);

// SOVRACCARICO
    dequeue<T> &operator=(const dequeue<T> &);
    bool operator==(const dequeue<T> &);

    template<class T1>
    friend ostream &operator<<(ostream &, const dequeue<T1> &);

//ausiliari
    int lunghezza();

private:
    Nodo_dequeue<T> *testa;
    Nodo_dequeue<T> *coda;
    int lunghezzaLista;
};


template<class T>
int dequeue<T>::lunghezza() {
    return lunghezzaLista;
}

template<class T>
dequeue<T>::dequeue() {
    testa = nullptr;
    coda = nullptr;
    lunghezzaLista = 0;
}

template<class T>
dequeue<T>::dequeue(const dequeue<T> &d) {
    testa = nullptr;
    coda = nullptr;
    lunghezzaLista = 0;
    if (!d.dequeueVuota()) {
        Nodo_dequeue<T> *nodoCopiato;
        nodoCopiato = d.testa;
        while (nodoCopiato != nullptr) {
            insCoda(nodoCopiato->valore);
            nodoCopiato = nodoCopiato->successivo;
        }
        coda = nodoCopiato;
    }
}

template<class T>
dequeue<T>::~dequeue() {
    while (!dequeueVuota()) {
        fuoriTesta();
    }
}

template<class T>
bool dequeue<T>::dequeueVuota() const {
    return lunghezzaLista == 0;
}

template<class T>
typename dequeue<T>::tipoelem dequeue<T>::leggiTesta() const {
    if (testa != nullptr)
        return testa->valore;
    else throw std::out_of_range("DEQUEUE VUOTA");
}

template<class T>
typename dequeue<T>::tipoelem dequeue<T>::leggiCoda() const {
    if (coda != nullptr)
        return coda->valore;
    else throw std::out_of_range("DEQUEUE VUOTA");
}

template<class T>
void dequeue<T>::fuoriTesta() {
    if (lunghezzaLista >= 1) {
        Nodo_dequeue<T> *tmp = testa;
        testa = testa->successivo;
        delete tmp;
        if (testa == nullptr) coda = nullptr;
        lunghezzaLista--;
    } else throw std::out_of_range("DEQUEUE VUOTA");
}

template<class T>
void dequeue<T>::fuoriCoda() {
    if (coda != nullptr) {
        Nodo_dequeue<T> *tmp = coda;
        coda->precedente->successivo = nullptr;
        coda = coda->precedente;
        delete tmp;
        if (coda == nullptr) coda = nullptr;
        lunghezzaLista--;
    } else throw std::out_of_range("DEQUEUE VUOTA");

}


template<class T>
void dequeue<T>::insTesta(const tipoelem &e) {
    Nodo_dequeue<T> *n = new Nodo_dequeue<T>;
    n->valore = e;
    n->precedente = nullptr;
    if (dequeueVuota()) {
        testa = n;
        coda = n;
    } else {
        n->successivo = testa;
        testa->precedente = n;
        testa = n;
        if (coda == nullptr) coda = testa;
    }
    lunghezzaLista++;
}

template<class T>
void dequeue<T>::insCoda(const tipoelem &e) {
    Nodo_dequeue<T> *n = new Nodo_dequeue<T>;
    n->valore = e;
    n->successivo = nullptr;
    if (dequeueVuota()) {
        testa = n;
        coda = n;
    } else {
        n->precedente = coda;
        coda->successivo = n;
        coda = n;
    }
    lunghezzaLista++;
}

template<class T>
dequeue<T> &dequeue<T>::operator=(const dequeue<T> &d) {
    if (this != &d) {
        this->~dequeue();
        testa = nullptr;
        coda = nullptr;
        lunghezzaLista = 0;
        if (!d.dequeueVuota()) {
            Nodo_dequeue<T> *nodoCopiato;
            nodoCopiato = d.testa;
            while (nodoCopiato != nullptr) {
                insCoda(nodoCopiato->valore);
                nodoCopiato = nodoCopiato->successivo;
            }
            coda = nodoCopiato;
        }
    }
    return *this;
}

template<class T>
bool dequeue<T>::operator==(const dequeue<T> &D) {
    if (lunghezzaLista != D.lunghezzaLista) return false;
    else {
        Nodo_dequeue<T> *tmp1 = D.testa, *tmp2 = testa;
        while (tmp1 != nullptr) {
            if (tmp1->valore != tmp2->valore) return false;
            else {
                tmp1 = tmp1->successivo;
                tmp2 = tmp2->successivo;
            }
        }
        return true;
    }
}

template<class T1>
ostream &operator<<(ostream &os, const dequeue<T1> &dq) {
    Nodo_dequeue<T1> *tmp = dq.testa;
    os << "[";
    {
        while (tmp != nullptr) {
            if (tmp == dq.testa) {
                os << tmp->getValore();
            } else os << "," << tmp->getValore();
            tmp = tmp->getSuccessivo();
        }
    }
    os << "]" << endl;
    return os;
}


#endif //REALIZZAZIONI_DEQUEUE_H
