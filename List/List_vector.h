#ifndef REALIZZAZIONI_LIST_VECTOR_H
#define REALIZZAZIONI_LIST_VECTOR_H

#include <iostream>
#include <ostream>
#include <stdexcept>
#include "Linear_list.h"

using namespace std;

template<class T>
class List_vector : public Linear_List<T, int> {
public:
    typedef typename Linear_List<T, int>::tipoelem tipoelem;
    typedef typename Linear_List<T, int>::posizione posizione;

    //costruttore vuoto
    List_vector();
    //costruttore con dimensione elementi
    List_vector(int);
    //costruttore di copia
    List_vector(const List_vector<T> &);
    //distruttore
    ~List_vector();

    //operatori della lista
    void creaLista();
    bool listaVuota() const;
    tipoelem leggiLista(posizione) const;
    void scriviLista(const tipoelem &, posizione);
    posizione primoLista() const;
    bool fineLista(posizione) const;
    posizione succLista(posizione) const;
    posizione precLista(posizione) const;
    void insLista(const tipoelem &, posizione &);
    void cancLista(posizione &);

    //Sovrascrivo operatori

    List_vector<T> &operator=(const List_vector<T> &);
    bool operator==(const List_vector<T> &);


    //FUNZIONI ACCESSORIE
    void inserisciTesta(const tipoelem &);
    void inserisciCoda(const tipoelem &);
    void rimuoviTesta();
    void rimuoviCoda();
    posizione ultimoLista() const;
    int lunghezza() const;
    void scambiaElementi(posizione, posizione);


private:
    int lunghezzaArray;
    int lunghezzaLista;
    tipoelem *elementi;
    void cambiaDimensione(tipoelem *&, int, int);

};

template<class T>
int List_vector<T>::lunghezza() const {
    return lunghezzaLista;
}

template<class T>
typename List_vector<T>::posizione List_vector<T>::ultimoLista() const {
    return lunghezzaLista;
}

//costruttore vuoto
template<class T>
List_vector<T>::List_vector() {
    this->lunghezzaArray = 10;
    this->creaLista();
}

//costruttore con gia un elemento
template<class T>
List_vector<T>::List_vector(int dim) {
    this->lunghezzaArray = dim;
    this->creaLista();
}

//costruttore di copia
//ovviamente non uso primoLista, etc..., perchè la lista ancora non esiste
template<class T>
List_vector<T>::List_vector(const List_vector<T> &L) {
    this->lunghezzaLista = L.lunghezzaLista;
    this->lunghezzaArray = L.lunghezzaArray;
    this->elementi = new tipoelem[lunghezzaArray];
    for (int i = 0; i < lunghezzaLista; i++) {
        this->elementi[i] = L.elementi[i];
    }
}


template<class T>
List_vector<T>::~List_vector() {
    delete[] elementi;
}


//operatori

template<class T>
void List_vector<T>::creaLista() {
    this->lunghezzaLista = 0;
    elementi = new tipoelem[lunghezzaArray];
}

template<class T>
bool List_vector<T>::listaVuota() const {
    return (lunghezzaLista == 0);
}

template<class T>
typename List_vector<T>::tipoelem List_vector<T>::leggiLista(posizione p) const {
    if (p >= 1 && p <= lunghezzaLista) //precondizione -> p=pos(i) con 1<=i<=n
    {
        return elementi[p - 1];
    } else throw std::out_of_range("POSIZIONE NON VALIDA");
}

template<class T>
void List_vector<T>::scriviLista(const tipoelem &e, posizione p) {
    if (p >= 1 && p <= lunghezzaLista) //precondizione -> p=pos(i) con 1<=i<=n
    {
        elementi[p - 1] = e;
    } else throw std::out_of_range("POSIZIONE NON ESISTENTE");
}

template<class T>
typename List_vector<T>::posizione List_vector<T>::primoLista() const {
    return 1;
}

template<class T>
bool List_vector<T>::fineLista(posizione p) const {
    if (p >= 1 && p <= lunghezzaLista + 1) //precondizione -> p=pos(i) con 1<=i<=n+1
    {
        return (p == lunghezzaLista + 1);
    } else {
        throw std::out_of_range("POSIZIONE NON VALIDA");
    }
}

template<class T>
typename List_vector<T>::posizione List_vector<T>::succLista(posizione p) const {
    if (p >= 1 && p <= lunghezzaLista) //precondizione -> p=pos(i) con 1<=i<=n
    {
        return p + 1;
    } else throw std::out_of_range("POSIZIONE NON VALIDA3");
}

template<class T>
typename List_vector<T>::posizione List_vector<T>::precLista(posizione p) const {
    if (p >= 2 && p <= lunghezzaLista) //precondizione -> p=pos(i) con 2<=i<=n
    {
        return p - 1;
    } else throw std::out_of_range("POSIZIONE NON VALIDA");
}

template<class T>
void List_vector<T>::insLista(const tipoelem &e, posizione &p) {
    if (p >= 1 && p <= lunghezzaLista + 1) {
        if (lunghezzaLista == lunghezzaArray) {
            cambiaDimensione(elementi, lunghezzaArray, lunghezzaArray * 2);
            lunghezzaArray *= 2;
        }
        for (int i = lunghezzaLista; i >= p; i--) {
            elementi[i] = elementi[i - 1];
        }
        elementi[p - 1] = e;
        lunghezzaLista++;
    } else throw std::out_of_range("POSIZIONE NON VALIDA");

}


template<class T>
void List_vector<T>::cancLista(posizione &p) {
    if (p >= 1 && p <= lunghezzaLista) {
        if (!listaVuota()) {
            for (int i = p - 1; i < lunghezzaLista - 1; i++) {
                elementi[i] = elementi[i + 1];
            }
            lunghezzaLista--;
        }
    } else throw std::out_of_range("POSIZIONE NON VALIDA");
}


template<class T>
void List_vector<T>::cambiaDimensione(tipoelem *&elementi, int vecchiaDimensione, int nuovaDimensione) {
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
void List_vector<T>::inserisciTesta(const List_vector::tipoelem &e) {
    posizione p = primoLista();
    insLista(e, p);
}

template<class T>
void List_vector<T>::inserisciCoda(const List_vector::tipoelem &e) {
    posizione p = lunghezzaLista + 1;
    insLista(e, p);
}

template<class T>
void List_vector<T>::rimuoviTesta() {
    posizione p = 1;
    cancLista(p);
}

template<class T>
void List_vector<T>::rimuoviCoda() {
    cancLista(lunghezzaLista);
}


template<class T>
bool List_vector<T>::operator==(const List_vector<T> &L) {
    if (this->lunghezzaLista != L.lunghezzaLista) {
        return false;
    } else {
        for (int i = 0; i < lunghezzaLista; i++) {
            if (!(this->elementi[i] != L.elementi[i]))
                return false;
        }
        return true;
    }
}

template<class T>
List_vector<T> &List_vector<T>::operator=(const List_vector<T> &L) {
    if (this != &L) {
        this->lunghezzaLista = L.lunghezzaLista;
        this->lunghezzaArray = L.lunghezzaArray;
        delete[] elementi;
        elementi = new tipoelem[lunghezzaArray];
        for (int i = 0; i < lunghezzaLista; i++) {
            elementi[i] = L.elementi[i];
        }
    }
    return *this;
}

template<class T>
void List_vector<T>::scambiaElementi(posizione p1, posizione p2) {
    tipoelem tmp = elementi[p1 - 1];
    elementi[p1 - 1] = elementi[p2 - 1];
    elementi[p2 - 1] = tmp;
}

#endif //REALIZZAZIONI_LIST_VECTOR_H
