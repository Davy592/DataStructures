#ifndef REALIZZAZIONI_ALBEROBINARIO_PT_H
#define REALIZZAZIONI_ALBEROBINARIO_PT_H

#include "alberoBinario.h"
#include <stdexcept>

template<class T>
class alberoBinario_pt;

template<class T>
class nodoT {
    friend class alberoBinario_pt<T>;

private:
    T valore;
    nodoT<T> *padre;
    nodoT<T> *figlio_sinistro;
    nodoT<T> *figlio_destro;
};

template<class T>
class alberoBinario_pt : public alberoBin<T, nodoT<T> *> {
public:
    //TIPO
    typedef typename alberoBin<T, nodoT<T> *>::tipoElem tipoElem;
    typedef typename alberoBin<T, nodoT<T> *>::nodo nodo;

    //COSTRUTTORE
    alberoBinario_pt();

    //COSTRUTTORE COPIA
    alberoBinario_pt(alberoBinario_pt &);

    //DISTRUTTORE
    ~alberoBinario_pt();


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
    bool operator==(const alberoBinario_pt<T> &);
    alberoBinario_pt<T> &operator=(const alberoBinario_pt<T> &);

private:
    nodoT<T> *root;
    int numNodi;
    nodoT<T> *copiaNodo(nodoT<T> *, nodoT<T> *);
    void cancellaNodo(nodoT<T> *);
    void cancellaSinistro(nodoT<T> *);
    void cancellaDestro(nodoT<T> *);
    bool confrontaNodi(nodoT<T> *, nodoT<T> *);
    void inverti(nodoT<T> *r);
};


template<class T>
alberoBinario_pt<T>::alberoBinario_pt() {
    root = nullptr;
    numNodi = 0;
}

template<class T>
alberoBinario_pt<T>::alberoBinario_pt(alberoBinario_pt<T> &BT) {
    numNodi = 0;
    root = copiaNodo(BT.root, nullptr);
}


template<class T>
nodoT<T> *alberoBinario_pt<T>::copiaNodo(nodoT<T> *daCopiare, nodoT<T> *padre) {
    if (daCopiare == nullptr)
        return nullptr;
    nodoT<T> *nuovoNodo = new nodoT<T>;
    nuovoNodo->padre = padre;
    nuovoNodo->valore = daCopiare->valore;
    nuovoNodo->figlio_sinistro = copiaNodo(daCopiare->figlio_sinistro, daCopiare);
    nuovoNodo->figlio_destro = copiaNodo(daCopiare->figlio_destro, daCopiare);
    numNodi++;
    return nuovoNodo;
}

template<class T>
void alberoBinario_pt<T>::cancellaNodo(nodoT<T> *daCancellare) {
    if (daCancellare != nullptr) {
        cancellaNodo(daCancellare->figlio_sinistro);
        cancellaNodo(daCancellare->figlio_destro);
        delete daCancellare;
        numNodi--;
    }
}


template<class T>
void alberoBinario_pt<T>::cancellaSinistro(nodoT<T> *daCancellare) {
    if (daCancellare != nullptr) {
        cancellaNodo(daCancellare->figlio_sinistro);
        daCancellare->figlio_sinistro = nullptr;
    }
}

template<class T>
void alberoBinario_pt<T>::cancellaDestro(nodoT<T> *daCancellare) {
    if (daCancellare != nullptr) {
        cancellaNodo(daCancellare->figlio_destro);
        daCancellare->figlio_destro = nullptr;
    }
}

template<class T>
alberoBinario_pt<T>::~alberoBinario_pt() {
    if (!alberoBinVuoto())
        cancellaSottoalbero(root);
    else {
        root = nullptr;
        delete root;
    }
}


template<class T>
bool alberoBinario_pt<T>::alberoBinVuoto() const {
    return (root == nullptr);
}

template<class T>
typename alberoBinario_pt<T>::nodo alberoBinario_pt<T>::radice() const {
    if (root != nullptr)
        return root;
    else throw std::out_of_range("RADICE INESISTENTE");
}

template<class T>
typename alberoBinario_pt<T>::nodo alberoBinario_pt<T>::genitore(nodo n) const {
    if (n != root) {
        return n->padre;
    } else throw std::out_of_range("LA RADICE NON HA UN GENITORE");
}

template<class T>
typename alberoBinario_pt<T>::nodo alberoBinario_pt<T>::figlioSinistro(nodo n) const {
    if (n != nullptr) {
        if (!sinistroVuoto(n))
            return n->figlio_sinistro;
        else throw std::out_of_range("IL NODO NON HA UN FIGLIO SINISTRO");
    } else throw std::out_of_range("NODO NON VALIDO");
}

template<class T>
typename alberoBinario_pt<T>::nodo alberoBinario_pt<T>::figlioDestro(nodo n) const {
    if (n != nullptr) {
        if (!destroVuoto(n))
            return n->figlio_destro;
        else throw std::out_of_range("IL NODO NON HA UN FIGLIO DESTRO");
    } else throw std::out_of_range("NODO NON VALIDO");

}

template<class T>
bool alberoBinario_pt<T>::sinistroVuoto(nodo n) const {
    return (n->figlio_sinistro == nullptr);
}

template<class T>
bool alberoBinario_pt<T>::destroVuoto(nodo n) const {
    return (n->figlio_destro == nullptr);
}

template<class T>
void alberoBinario_pt<T>::cancellaSottoalbero(nodo n) {
    if (n->padre == nullptr) {
        cancellaNodo(n);
        root = nullptr;
    } else {
        if (n->padre->figlio_sinistro == n)
            cancellaSinistro(n->padre);
        else
            cancellaDestro(n->padre);
    }
}

template<class T>
typename alberoBinario_pt<T>::tipoElem alberoBinario_pt<T>::leggiNodo(nodo n) const {
    return n->valore;
}

template<class T>
void alberoBinario_pt<T>::scriviNodo(const nodo n, tipoElem valore) {
    n->valore = valore;
}

template<class T>
void alberoBinario_pt<T>::inserisciRadice(tipoElem valore) {
    if (alberoBinVuoto()) {
        root = new nodoT<T>;
        root->padre = nullptr;
        root->figlio_sinistro = nullptr;
        root->figlio_destro = nullptr;
        root->valore = valore;
        numNodi++;
    } else throw std::out_of_range("L'ALBERO HA GIA' UNA RADICE");
}

template<class T>
void alberoBinario_pt<T>::inserisciSinistro(nodo n, tipoElem valore) {
    if (sinistroVuoto(n)) {
        nodoT<T> *nuovoNodo = new nodoT<T>;
        nuovoNodo->valore = valore;
        nuovoNodo->padre = n;
        nuovoNodo->figlio_sinistro = nullptr;
        nuovoNodo->figlio_destro = nullptr;
        n->figlio_sinistro = nuovoNodo;
        numNodi++;
    } else throw std::out_of_range("ESISTE GIA UN FIGLIO SINISTRO");
}

template<class T>
void alberoBinario_pt<T>::inserisciDestro(nodo n, tipoElem valore) {
    if (destroVuoto(n)) {
        nodoT<T> *nuovoNodo = new nodoT<T>;
        nuovoNodo->valore = valore;
        nuovoNodo->padre = n;
        nuovoNodo->figlio_sinistro = nullptr;
        nuovoNodo->figlio_destro = nullptr;
        n->figlio_destro = nuovoNodo;
        numNodi++;
    } else throw std::out_of_range("ESISTE GIA UN FIGLIO DESTRO");
}


template<class T>
bool alberoBinario_pt<T>::operator==(const alberoBinario_pt<T> &BT) {
    if (numNodi != BT.numNodi) return false;
    {
        return confrontaNodi(root, BT.root);

    }
}

template<class T>
bool alberoBinario_pt<T>::confrontaNodi(nodoT<T> *n1, nodoT<T> *n2) {
    bool uguali = true;
    if (n1->valore == n2->valore) {
        if (n1->figlio_sinistro != nullptr && n2->figlio_sinistro != nullptr) {
            uguali = confrontaNodi(n1->figlio_sinistro, n2->figlio_sinistro);
        } else return uguali;
        if (uguali && n1->figlio_destro != nullptr && n2->figlio_destro != nullptr) {
            uguali = confrontaNodi(n1->figlio_destro, n2->figlio_destro);
        } else return uguali;
    } else uguali = false;
    return uguali;
}

template<class T>
alberoBinario_pt<T> &alberoBinario_pt<T>::operator=(const alberoBinario_pt<T> &BT) {
    if (this != &BT) {
        numNodi = 0;
        root = copiaNodo(BT.root, nullptr);
    }
    return *this;
}

template<class T>
void alberoBinario_pt<T>::inverti() {
    if (!alberoBinVuoto()) {
        inverti(radice());
    }
}

template<class T>
void alberoBinario_pt<T>::inverti(nodoT<T> *r) {
    if (r->figlio_sinistro != nullptr) {
        inverti(r->figlio_sinistro);
    }
    if (r->figlio_destro != nullptr) {
        inverti(r->figlio_destro);
    }
    if (r->figlio_sinistro != nullptr && r->figlio_destro != nullptr) {
        nodoT<T> *tmp = r->figlio_sinistro;
        r->figlio_sinistro = r->figlio_destro;
        r->figlio_destro = tmp;
    }
}

#endif //REALIZZAZIONI_ALBEROBINARIO_PT_H
