#ifndef REALIZZAZIONI_CODAV_H
#define REALIZZAZIONI_CODAV_H

#include <stdexcept>
#include <ostream>

using namespace std;

template<class T>
class codav {
public:
    typedef T tipoelem;

    //Costruttore (rimpiazza il creaCoda)
    codav();

    //Costruttore con numero elementi definito(rimpiazza il creaCoda)
    codav(int);

    //costruttore per copia (rimpiazza il creaCoda)
    codav(const codav<T> &);

    //distruttore
    ~codav();

    bool codaVuota() const;

    tipoelem leggiCoda() const;

    void fuoriCoda();

    void incoda(const tipoelem &);

    //funzioni aggiuntive
    int lunghezza() const;
    bool esiste(const tipoelem &);

    codav<T> &operator=(const codav<T> &);

    bool operator==(const codav<T> &);


    template<class T1>
    friend ostream &operator<<(ostream &, const codav<T1> &);

private:
    int lunghezzaArray;
    int testa; //prelevo da testa
    int coda; //inserisco da coda
    tipoelem *elementi;

    void cambiaDimensione(tipoelem *&, int, int);
};


template<class T>
codav<T>::codav() {
    lunghezzaArray = 10;
    elementi = new tipoelem[lunghezzaArray];
    testa = 0;
    coda = 0;
}

template<class T>
codav<T>::codav(int dim) {
    lunghezzaArray = dim;
    elementi = new tipoelem[lunghezzaArray];
    testa = 0;
    coda = 0;
}

template<class T>
codav<T>::codav(const codav<T> &c) {
    lunghezzaArray = c.lunghezzaArray;
    testa = c.testa;
    coda = c.coda;
    elementi = new tipoelem[lunghezzaArray];
    for (int i = testa; i < coda; i++) {
        elementi[(testa + i) % lunghezzaArray] = c.elementi[(testa + i) % lunghezzaArray];
    }
}

template<class T>
codav<T>::~codav() {

    delete[] elementi;
}

template<class T>
int codav<T>::lunghezza() const {
    return coda;
}

template<class T>
bool codav<T>::codaVuota() const {
    return coda == 0;
}

template<class T>
typename codav<T>::tipoelem codav<T>::leggiCoda() const {
    if (coda > 0) {
        return elementi[testa];
    } else throw std::out_of_range("LA CODA E' VUOTA");
}

template<class T>
void codav<T>::fuoriCoda() {
    if (coda > 0) {
        testa = (testa + 1) % lunghezzaArray;
        coda--;
    } else throw std::out_of_range("LA CODA E' VUOTA");
}

template<class T>
void codav<T>::incoda(const tipoelem &e) {
    if (coda == lunghezzaArray) {
        cambiaDimensione(elementi, lunghezzaArray, lunghezzaArray * 2);
        lunghezzaArray *= 2;
    }
    elementi[(testa + coda) % lunghezzaArray] = e;
    coda++;
}

template<class T>
void codav<T>::cambiaDimensione(tipoelem *&e, int vecchiaDimensione, int nuovaDimensione) {
    int numero;
    (vecchiaDimensione < nuovaDimensione) ? numero = vecchiaDimensione : numero = nuovaDimensione;
    //numero=min(vecchiaDimensione, nuovaDimensione);
    tipoelem *tmp = new tipoelem[nuovaDimensione];
    for (int i = 0; i < numero; i++) {
        tmp[(testa + i) % lunghezzaArray] = elementi[(testa + i) % lunghezzaArray];
    }
    delete[] elementi;
    elementi = tmp;
    testa = 0;
}


template<class T1>
ostream &operator<<(ostream &os, const codav<T1> &c) {
    int letti = 0;
    int i = (c.testa) % c.lunghezzaArray;
    os << "[";
    while (letti < c.coda) {
        if (i == (c.testa % c.lunghezzaArray)) {
            os << c.elementi[i];
        } else os << "," << c.elementi[i];
        letti++;
        i++;
    }
    os << "]" << endl;
    return os;
}

template<class T>
bool codav<T>::operator==(const codav<T> &c) {
    if (coda != c.coda) return false;
    for (int i = 0; i < coda; i++) {
        if (elementi[i] != c.elementi[i]) return false;
    }
    return true;
}


template<class T>
codav<T> &codav<T>::operator=(const codav<T> &c) {
    if (this != &c) {
        this->~coda();
        lunghezzaArray = c.lunghezzaArray;
        testa = c.testa;
        coda = c.coda;
        elementi = new tipoelem[lunghezzaArray];
        for (int i = testa; i < coda; i++) {
            elementi[(testa + i) % lunghezzaArray] = c.elementi[(testa + i) % lunghezzaArray];
        }
    }
    return *this;
}


template<class T>
bool codav<T>::esiste(const tipoelem &e) {
    if (!codaVuota()) {
        int i = testa;
        int trov = false;
        while (i < coda && !trov) {
            if (elementi[(testa + i) % lunghezzaArray] == e) trov = true;
            else i++;
        }
        return trov;
    } else return false;
}


#endif //REALIZZAZIONI_CODAV_H
