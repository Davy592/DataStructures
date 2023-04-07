#ifndef REALIZZAZIONI_PILAV_H
#define REALIZZAZIONI_PILAV_H

#include <ostream>
#include <stdexcept>
#include <iostream>

using namespace std;

template<class T>
class pilav {
public:
    typedef T tipoelem;
    //costruttore
    pilav();
    //costruttore con dimensione vettore
    pilav(int);
    //costruttore copia
    pilav(const pilav<T> &);
    //distruttore
    ~pilav();

    //operatori
    void creaPila();
    bool pilaVuota() const;
    tipoelem leggiPila() const;
    void fuoriPila();
    void insPila(const tipoelem &);
    void inPila(const tipoelem &);


    //funzioni accessorie e sovrascrizione operatori
    template<class T1>
    friend ostream &operator<<(ostream &, const pilav<T1> &);

    pilav<T> &operator=(const pilav<T> &);

    bool operator==(const pilav<T> &);

    int lunghezza();

    bool esiste(const tipoelem &e) {
        int i = 0;
        while (i < testa) {
            if (elementi[i] == e) return true;
            else i++;
        }
        return false;
    }

private:
    tipoelem *elementi;
    int lunghezzaArray;
    int testa;
    void cambiaDimensione(tipoelem *&, int, int);

};


template<class T>
int pilav<T>::lunghezza() {
    return testa;
}

template<class T>
pilav<T>::pilav() {
    this->lunghezzaArray = 10;
    this->creaPila();
}

template<class T>
pilav<T>::pilav(int dim) {
    this->lunghezzaArray = dim;
    this->creaPila();
}


template<class T>
pilav<T>::pilav(const pilav<T> &pl) {
    this->lunghezzaArray = pl.lunghezzaArray;
    this->testa = pl.testa;
    elementi = new tipoelem[lunghezzaArray];
    for (int i = 0; i < testa; i++) {
        this->elementi[i] = pl.elementi[i];
    }
}

template<class T>
pilav<T>::~pilav() {
    delete[] elementi;
}

template<class T>
void pilav<T>::creaPila() {
    elementi = new tipoelem[lunghezzaArray];
    testa = 0;
}

template<class T>
bool pilav<T>::pilaVuota() const {
    return (testa == 0);
}


template<class T>
typename pilav<T>::tipoelem pilav<T>::leggiPila() const {
    if (testa >= 1) {
        return elementi[testa - 1];
    } else throw std::out_of_range("PILA VUOTA");
}


template<class T>
void pilav<T>::fuoriPila() {
    if (testa > 0) {
        testa--;
    } else throw std::out_of_range("PILA VUOTA");
}

template<class T>
void pilav<T>::insPila(const pilav::tipoelem &e) {
    if (testa == lunghezzaArray) {
        cambiaDimensione(elementi, lunghezzaArray, lunghezzaArray * 2);
        lunghezzaArray *= 2;
    }
    elementi[testa] = e;
    testa++;
}

template<class T>
void pilav<T>::inPila(const pilav::tipoelem &el) {
    bool trov = false;
    int i = 0;
    while (i < testa && !trov) {
        if (elementi[i] == el) trov = true;
        else i++;
    }
    if (!trov) this->insPila(el);

}

template<class T>
void pilav<T>::cambiaDimensione(pilav::tipoelem *&el, int vecchiaDimensione, int nuovaDimensione) {
    int numero;
    (vecchiaDimensione < nuovaDimensione) ? numero = vecchiaDimensione : numero = nuovaDimensione;
    tipoelem *tmp = new tipoelem[nuovaDimensione];
    for (int i = 0; i < numero; i++) {
        tmp[i] = this->elementi[i];
    }
    delete[] elementi;
    elementi = tmp;
}

template<class T>
ostream &operator<<(ostream &os, const pilav<T> &pl) {
    os << "[";
    for (int i = pl.testa - 1; i >= 0; i--) {
        if (i != 0) os << pl.elementi[i] << ", ";
        else os << pl.elementi[i];
    }
    os << "]" << endl;
    return os;
}

template<class T>
pilav<T> &pilav<T>::operator=(const pilav<T> &pl) {
    if (this != &pl) {
        this->lunghezzaArray = pl.lunghezzaArray;
        this->testa = pl.testa;
        delete[] elementi;
        elementi = new tipoelem[lunghezzaArray];
        for (int i = 0; i < testa; i++) {
            elementi[i] = pl.elementi[i];
        }
    }
    return *this;
}

template<class T>
bool pilav<T>::operator==(const pilav<T> &pl) {
    if (this->testa != pl.testa) {
        return false;
    } else {
        for (int i = 0; i < testa; i++) {
            if (this->elementi[i] != pl.elementi[i])
                return false;
        }
        return true;
    }
}

#endif //REALIZZAZIONI_PILAV_H
