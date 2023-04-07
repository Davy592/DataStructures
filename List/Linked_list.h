#ifndef REALIZZAZIONI_LINKED_LIST_H
#define REALIZZAZIONI_LINKED_LIST_H

#include "Linear_list.h"
#include "../Dictionary/hashtableAperto.h"
#include <stdexcept>

// necessario al compilatore, perchè Linked_List viene definita successivamente a Nodo_lista
template<class T>
class Linked_list;

template<class T>
class Nodo_lista {
    friend class Linked_list<T>; //in questo modo linked list può accedere alla parte private di Nodo_lista
public:
    typedef T tipoelem;
private:
    tipoelem valore;                  //valore memorizzato
    Nodo_lista<tipoelem> *precedente; //puntatore al nodo precedente
    Nodo_lista<tipoelem> *successivo; //puntatore al nodo successivo
};

template<class T>
class Linked_list
        : public Linear_List<T, Nodo_lista<T> *> { //I tipoelem sono T mentre le posizioni sono puntatori a Nodo_lista
public:
    typedef typename Linear_List<T, Nodo_lista<T> *>::tipoelem tipoelem;
    typedef typename Linear_List<T, Nodo_lista<T> *>::posizione posizione;

    // costruttore base
    Linked_list();
    // costruttore per copia
    Linked_list(const Linked_list<T> &);
    // distruttore
    ~Linked_list();

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

    Linked_list<T> &operator=(const Linked_list<T> &);
    bool operator==(const Linked_list<T> &);

    //FUNZIONI ACCESSORIE
    void inserisciTesta(const tipoelem &);
    void inserisciCoda(const tipoelem &);
    void rimuoviTesta();
    void rimuoviCoda();
    posizione ultimoLista() const;
    int lunghezza() const;
    void scambiaElementi(posizione, posizione);

    //ESERCIZI
    int freq(const Linked_list<T> &, int k);
    void hist(const Linked_list<T> &);
    void remp(Linked_list<T> &);


private:
    Nodo_lista<T> *testa;
    int lunghezzaLista; // Lunghezza lista
};


template<class T>
void Linked_list<T>::creaLista() {
    testa = new Nodo_lista<T>;
    testa->successivo = testa;
    testa->precedente = testa;
    lunghezzaLista = 0;

}

template<class T>
Linked_list<T>::Linked_list() {
    creaLista();
}

template<class T>
Linked_list<T>::Linked_list(const Linked_list<T> &L) {
    lunghezzaLista = L.lunghezzaLista;

    testa = new Nodo_lista<T>;
    testa->successivo = testa;
    testa->precedente = testa;
    posizione p = L.primoLista();
    posizione p1 = this->primoLista();
    while (!L.fineLista(p)) {
        this->insLista(L.leggiLista(p), p1);
        p1 = this->succLista(p1);
        p = L.succLista(p);
    }

}

template<class T>
Linked_list<T>::~Linked_list() {
    posizione tmp, p = ultimoLista();
    while (!fineLista(p)) {
        tmp = p;
        p = p->precedente;
        tmp = nullptr;
        delete tmp;
    }
    testa = nullptr;
    delete testa;
}


template<class T>
bool Linked_list<T>::listaVuota() const {
    return (testa == testa->successivo); // se la sentinella sta puntando a se stessa, allora la lista è vuota
}

template<class T>
typename Linked_list<T>::posizione
Linked_list<T>::primoLista() const {
    return (testa->successivo); //la sentinella punta al primo della lista
}

template<class T>
typename Linked_list<T>::posizione
Linked_list<T>::ultimoLista() const {
    return (testa->precedente);
}

template<class T>
typename Linked_list<T>::posizione
Linked_list<T>::succLista(Linked_list::posizione p) const {
    return p->successivo;
}

template<class T>
typename Linked_list<T>::posizione Linked_list<T>::precLista(Linked_list::posizione p) const {
    if (p != testa->successivo) // PRECONDIZIONE: Non posso restiture il precedente del primo
        return (p->precedente);
    else throw std::out_of_range("POSIZIONE NON VALIDA");
}

template<class T>
bool Linked_list<T>::fineLista(Linked_list<T>::posizione p) const {
    return (p == testa); //se p equivale alla sentinella allora siamo arrivati alla fine della lista
}

template<class T>
typename Linked_list<T>::tipoelem
Linked_list<T>::leggiLista(Linked_list::posizione p) const {
    if (!fineLista(p)) //precondizione
        return (p->valore);
    else throw std::out_of_range("POSIZIONE NON VALIDA");
}

template<class T>
void Linked_list<T>::scriviLista(const Linked_list::tipoelem &e, Linked_list::posizione p) {
    if (!fineLista(p))
        p->valore = e;
    else throw std::out_of_range("POSIZIONE NON VALIDA");
}

template<class T>
void Linked_list<T>::insLista(const Linked_list::tipoelem &e, Linked_list::posizione &p) {
    posizione t = new Nodo_lista<T>;
    t->valore = e;
    t->precedente = p->precedente;
    t->successivo = p;
    p->precedente->successivo = t;
    p->precedente = t;
    lunghezzaLista++;
    p = p->precedente;

}

template<class T>
void Linked_list<T>::cancLista(Linked_list<T>::posizione &p) {
    if (!listaVuota() && !fineLista(p)) {
        posizione tmp = p->successivo;
        p->precedente->successivo = p->successivo;
        p->successivo->precedente = p->precedente;
        delete p;
        p = tmp;
        lunghezzaLista--;
    } else throw std::out_of_range("POSIZIONE NON VALIDA");
}

template<class T>
Linked_list<T> &Linked_list<T>::operator=(const Linked_list<T> &L) {
    if (this != &L) // per evitare l'autoassegnamento
    {
        // deallocare tutta la lista this
        this->~Linked_list();
        // creazione della sentinella per this
        testa = new Nodo_lista<T>;
        testa->successivo = testa;
        testa->precedente = testa;
        posizione pl = L.primoLista();
        posizione p1 = this->primoLista();
        while (!L.fineLista(pl)) {
            this->insLista(L.leggiLista(pl), p1);
            p1 = this->succLista(p1);
            pl = L.succLista(pl);
        }
    }
    return *this;
}

template<class T>
bool Linked_list<T>::operator==(const Linked_list<T> &L) {
    if (L.lunghezzaLista != this->lunghezzaLista)
        return false;
    posizione p, pL;
    p = primoLista();
    pL = L.primoLista();
    while (!fineLista(p)) {
        if (p->valore != pL->valore)
            return false;
        p = p->successivo;
        pL = pL->successivo;
    }
    return true;
}

template<class T>
void Linked_list<T>::inserisciTesta(const tipoelem &e) {
    Nodo_lista<T> *p = new Nodo_lista<T>;
    p->valore = e;
    testa->successivo->precedente = p;
    p->successivo = testa->successivo;
    p->precedente = testa;
    testa->successivo = p;
    lunghezzaLista++;
}

template<class T>
void Linked_list<T>::inserisciCoda(const tipoelem &e) {
    posizione p = new Nodo_lista<T>;
    p->valore = e;
    posizione pu = ultimoLista();
    p->precedente = pu;
    p->successivo = testa;
    pu->successivo = p;
    testa->precedente = p;
    lunghezzaLista++;
}


template<class T>
void Linked_list<T>::rimuoviTesta() {
    posizione p = new Nodo_lista<T>;
    p = testa->successivo;
    testa->successivo = testa->successivo->successivo;
    p = nullptr;
    delete p;
    lunghezzaLista--;
}

template<class T>
void Linked_list<T>::rimuoviCoda() {
    posizione p = new Nodo_lista<T>;
    p = ultimoLista();
    p->precedente->successivo = testa;
    p = nullptr;
    delete p;
    lunghezzaLista--;
}

template<class T>
int Linked_list<T>::lunghezza() const {
    return lunghezzaLista;
};

template<class T>
void Linked_list<T>::scambiaElementi(Linked_list::posizione p1, Linked_list::posizione p2) {

    if (p1 != p2 && (p1 != nullptr && p2 != nullptr)) {
        tipoelem temp = leggiLista(p1);
        scriviLista(leggiLista(p2), p1);
        scriviLista(temp, p2);
    }
}

#endif //REALIZZAZIONI_LINKED_LIST_H
