#ifndef REALIZZAZIONI_ALBEROBINARIO_ARRAY_H
#define REALIZZAZIONI_ALBEROBINARIO_ARRAY_H

#include "alberoBinario.h"
#include <stdexcept>

template<class T>
class alberoBinario_array;


template<class T>
class record {
    friend class alberoBinario_array<T>;

public:
    record &operator=(record<T> &r) {
        this->valore = r.valore;
        this->usato = r.usato;
        return *this;
    }

    bool operator==(record<T> &r) {
        return ((valore == r.valore) && (usato == r.usato));
    }

    bool operator!=(record<T> &r) {
        return !(this->operator==(r));
    }


private:
    T valore;
    bool usato;
};

template<class T>
class alberoBinario_array : public alberoBin<T, int> {
public:
    //TIPO
    typedef typename alberoBin<T, int>::tipoElem tipoElem;
    typedef typename alberoBin<T, int>::nodo nodo;

    //COSTRUTTORE
    alberoBinario_array();

    //COSTRUTTORE CON UN NUMERO DI NODI GIA DICHIARATO
    alberoBinario_array(int);

    //COSTRUTTORE COPIA
    alberoBinario_array(alberoBinario_array &);

    //DISTRUTTORE
    ~alberoBinario_array();


    //OPERATORI
    // void crea(); SOSTITUITO DAL COSTRUTTORE
    bool alberoBinVuoto() const;

    nodo radice() const;

    nodo genitore(nodo) const; //padre
    nodo figlioSinistro(nodo) const;

    nodo figlioDestro(nodo) const;

    bool sinistroVuoto(nodo) const;

    bool destroVuoto(nodo) const;

    void cancellaSottoalbero(nodo);

    tipoElem leggiNodo(nodo) const;

    void scriviNodo(const nodo, tipoElem);

    void inserisciRadice(tipoElem);

    void inserisciSinistro(const nodo, tipoElem);

    void inserisciDestro(const nodo, tipoElem);

    //SERVIZIO

    int getN() {
        return numNodi;
    }

    void inverti();
    //SOVRASCRIZIONE OPERATORI
    bool operator==(const alberoBinario_array<T> &);
    alberoBinario_array<T> &operator=(const alberoBinario_array<T> &);

private:
    record<T> *elementi;
    int lunghezzaArray;
    int numNodi;
    void cambiaDimensione(record<T> *&, int, int);
    void inverti(nodo r);
    void scambiaNodi(nodo r1, nodo r2);

};


template<class T>
alberoBinario_array<T>::alberoBinario_array() {
    elementi = new record<T>[2];
    lunghezzaArray = 2;
    numNodi = 0;
    for (int i = 0; i < lunghezzaArray; i++) {
        elementi[i].usato = false;
    }
}

template<class T>
alberoBinario_array<T>::alberoBinario_array(int dim) {
    elementi = new record<T>[dim];
    lunghezzaArray = dim;
    numNodi = 0;
    for (int i = 0; i < lunghezzaArray; i++) {
        elementi[i].usato = false;
    }
}

template<class T>
alberoBinario_array<T>::alberoBinario_array(alberoBinario_array<T> &BT) {
    this->numNodi = BT.numNodi;
    this->lunghezzaArray = BT.lunghezzaArray;
    this->elementi = new record<T>[lunghezzaArray];
    for (int i = 0; i < lunghezzaArray; i++) {
        elementi[i] = BT.elementi[i];
    }
}


template<class T>
alberoBinario_array<T>::~alberoBinario_array() {
    delete[] elementi;
}


template<class T>
bool alberoBinario_array<T>::alberoBinVuoto() const {
    if (!elementi[0].usato) return true;
    else return (numNodi == 0);
}

template<class T>
typename alberoBinario_array<T>::nodo alberoBinario_array<T>::radice() const {
    if (numNodi != 0)
        return 1;
    else throw std::out_of_range("RADICE INESISTENTE");
}

template<class T>
typename alberoBinario_array<T>::nodo alberoBinario_array<T>::genitore(nodo n) const {
    if (n > 1) {
        //CONTROLLO SE FIGLIO SINISTRO
        if ((n % 2 == 0)) return n / 2;
        else return (n - 1) / 2;
    } else throw std::out_of_range("LA RADICE NON HA UN GENITORE");
}

template<class T>
typename alberoBinario_array<T>::nodo alberoBinario_array<T>::figlioSinistro(nodo n) const {
    if (!sinistroVuoto(n) && n > 0)
        return n * 2;
    else {
        if (n > 0) throw std::out_of_range("IL NODO NON HA UN FIGLIO SINISTRO");
        else throw std::out_of_range("NODO NON ESISTENTE");
    }
}

template<class T>
typename alberoBinario_array<T>::nodo alberoBinario_array<T>::figlioDestro(nodo n) const {
    if (!destroVuoto(n) && n > 0)
        return (n * 2) + 1;
    else {
        if (n > 0) throw std::out_of_range("IL NODO NON HA UN FIGLIO DESTRO");
        else throw std::out_of_range("NODO NON ESISTENTE");
    }
}

template<class T>
bool alberoBinario_array<T>::sinistroVuoto(nodo n) const {
    int pos = (n * 2) - 1;
    if (pos >= lunghezzaArray) {
        return true;
    }
    return !elementi[pos].usato;
}

template<class T>
bool alberoBinario_array<T>::destroVuoto(nodo n) const {
    int pos = (n * 2);
    if (pos >= lunghezzaArray) {
        return true;
    }
    return !elementi[pos].usato;
}

template<class T>
void alberoBinario_array<T>::cancellaSottoalbero(nodo n) {
    numNodi--;
    int pos = n - 1;
    elementi[pos].usato = false;
    if (!sinistroVuoto(n)) cancellaSottoalbero(figlioSinistro(n));
    if (!destroVuoto(n)) cancellaSottoalbero(figlioDestro(n));

}

template<class T>
typename alberoBinario_array<T>::tipoElem alberoBinario_array<T>::leggiNodo(nodo n) const {
    int pos = n - 1;
    return elementi[pos].valore;
}

template<class T>
void alberoBinario_array<T>::scriviNodo(const nodo n, tipoElem valore) {
    int pos = n - 1;
    elementi[pos].valore = valore;
    elementi[pos].usato = true;
}

template<class T>
void alberoBinario_array<T>::inserisciRadice(tipoElem valore) {
    if (alberoBinVuoto()) {
        elementi[0].valore = valore;
        elementi[0].usato = true;
        numNodi++;
    } else throw std::out_of_range("L'ALBERO HA GIA' UNA RADICE");
}

template<class T>
void alberoBinario_array<T>::inserisciSinistro(nodo n, tipoElem valore) {
    if (sinistroVuoto(n)) {
        int pos = (n * 2) - 1;
        if (pos >= lunghezzaArray) {
            cambiaDimensione(elementi, lunghezzaArray, lunghezzaArray * 2);
            lunghezzaArray *= 2;
        }
        elementi[pos].valore = valore;
        elementi[pos].usato = true;
        numNodi++;
    } else throw std::out_of_range("ESISTE GIA UN FIGLIO SINISTRO");
}

template<class T>
void alberoBinario_array<T>::inserisciDestro(nodo n, tipoElem valore) {
    if (destroVuoto(n)) {
        int pos = (n * 2);
        if (pos >= lunghezzaArray) {
            cambiaDimensione(elementi, lunghezzaArray, lunghezzaArray * 2);
            lunghezzaArray *= 2;
        }
        elementi[pos].valore = valore;
        elementi[pos].usato = true;
        numNodi++;
    } else throw std::out_of_range("ESISTE GIA UN FIGLIO DESTRO");
}


template<class T>
void alberoBinario_array<T>::cambiaDimensione(record<T> *&elementi, int vecchiaDimensione, int nuovaDimensione) {
    record<T> *tmp = new record<T>[nuovaDimensione];
    for (int i = 0; i < vecchiaDimensione; i++) {
        tmp[i] = this->elementi[i];
    }
    for (int i = vecchiaDimensione; i < nuovaDimensione; i++) {
        tmp[i].usato = false;
    }
    delete[] elementi;
    elementi = tmp;

}

template<class T>
bool alberoBinario_array<T>::operator==(const alberoBinario_array<T> &BT) {
    if (numNodi != BT.numNodi || lunghezzaArray != BT.lunghezzaArray) return false;
    {
        for (int i = 0; i < lunghezzaArray; i++) {
            if (elementi[i] != BT.elementi[i]) return false;
        }
        return true;
    }
}

template<class T>
alberoBinario_array<T> &alberoBinario_array<T>::operator=(const alberoBinario_array<T> &BT) {
    if (this != &BT) {
        this->numNodi = BT.numNodi;
        this->lunghezzaArray = BT.lunghezzaArray;
        this->elementi = new record<T>[lunghezzaArray];
        for (int i = 0; i < lunghezzaArray; i++) {
            elementi[i] = BT.elementi[i];
        }
    }
    return *this;
}


template<class T>
void alberoBinario_array<T>::inverti() {
    if (!alberoBinVuoto()) {
        inverti(radice());
    }
}

template<class T>
void alberoBinario_array<T>::inverti(alberoBinario_array::nodo r) {
    if (!sinistroVuoto(r)) {
        inverti(figlioSinistro(r));
    }
    if (!destroVuoto(r)) {
        inverti(figlioDestro(r));
    }
    if (!sinistroVuoto(r) && !destroVuoto(r)) {
        scambiaNodi(figlioSinistro(r), figlioDestro(r));
    }
}

template<class T>
void alberoBinario_array<T>::scambiaNodi(alberoBinario_array::nodo r1, alberoBinario_array::nodo r2) {
    // Salva il contenuto dei nodi r1 e r2 in due variabili temporanee
    tipoElem tempr1 = leggiNodo(r1);
    tipoElem tempr2 = leggiNodo(r2);

    // Scrivi il contenuto della variabile temporanea contenente il valore del nodo r1 nel nodo r2
    // e il contenuto della variabile temporanea contenente il valore del nodo r2 nel nodo r1
    scriviNodo(r2, tempr1);
    scriviNodo(r1, tempr2);

    // Se r1 e r2 hanno un figlio sinistro, richiama ricorsivamente la funzione scambiaNodi
    // passando come argomenti il figlio sinistro di r1 e il figlio sinistro di r2
    if (!sinistroVuoto(r1) && !sinistroVuoto(r2)) {
        scambiaNodi(figlioSinistro(r1), figlioSinistro(r2));
    }

    // Se r1 e r2 hanno un figlio destro, richiama ricorsivamente la funzione scambiaNodi
    // passando come argomenti il figlio destro di r1 e il figlio destro di r2
    if (!destroVuoto(r1) && !destroVuoto(r2)) {
        scambiaNodi(figlioDestro(r1), figlioDestro(r2));
    }
}

#endif //REALIZZAZIONI_ALBEROBINARIO_ARRAY_H
