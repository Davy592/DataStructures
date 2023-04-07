#ifndef REALIZZAZIONI_HASHTABLEAPERTO_H
#define REALIZZAZIONI_HASHTABLEAPERTO_H

#include "dizionario.h"
#include <string>
#include <stdexcept>
#include <ostream>

using std::string;

template<class T>
class my_hash {
public:
    size_t operator()(const T the_key) const {
        return size_t(the_key);
    }
};


/* a specialization with type string */
template<>
class my_hash<string> {
public:
    size_t operator()(const string the_key) const {
        unsigned long hash_value = 0;
        int length = (int) the_key.length();
        for (int i = 0; i < length; i++)
            hash_value = 5 * hash_value + the_key.at(i);
        return size_t(hash_value);
    }
};

template<class K, class E>
class open_hash_table : public dizionario<K, E> {
public:
    typedef typename dizionario<K, E>::valore valore;
    typedef typename dizionario<K, E>::chiave chiave;
    typedef typename List_vector<mypair<K, E>>::posizione posizione;

    //costruttore default
    open_hash_table();
    //costruttore con dimensione stabilita
    open_hash_table(int);
    //costruttore copia
    open_hash_table(const open_hash_table<K, E> &);
    ~open_hash_table();


    //void creaDizionario(); rimpiazzato dal costruttore
    bool dizionarioVuoto() const;
    int trovaPosizione(const chiave) const;
    void inserisci(mypair<chiave, valore> &);
    void cancella(const chiave);
    valore recupera(const chiave);
    bool ricerca(const chiave) const;

    //accessorie
    int dimensione() const;
    bool contieneValore(const E &) const;
    //restituisce la lista dei valori memorizzati nel dizionario
    List_vector<E> values() const;
    //restituisce la lista delle chiavi memorizzate nel dizionario
    List_vector<K> keys() const;
    void modifica(const chiave &, const valore &, const valore &);
    void modifica(const chiave &, const valore &);

    //sovraccarico

    open_hash_table<K, E> &operator=(const open_hash_table<K, E> &);
    bool operator==(const open_hash_table<K, E> &);

    template<class K1, class E1>
    friend ostream &operator<<(ostream &, const open_hash_table<K1, E1> &);


private:
    int numElementi;
    int divisore;
    List_vector<mypair<K, E>> *tabella;
    my_hash<K> hashm;

};

template<class K, class E>
open_hash_table<K, E>::open_hash_table() {
    numElementi = 0;
    divisore = 10;
    tabella = new List_vector<mypair<K, E>>[divisore];
}

template<class K, class E>
open_hash_table<K, E>::open_hash_table(int dim) {
    numElementi = 0;
    divisore = dim;
    tabella = new List_vector<mypair<K, E>>[divisore];
}

template<class K, class E>
open_hash_table<K, E>::open_hash_table(const open_hash_table<K, E> &mp) {
    numElementi = mp.numElementi;
    divisore = mp.divisore;
    tabella = new List_vector<mypair<K, E>>[divisore];
    for (int i = 0; i < divisore; i++) {
        tabella[i] = mp.tabella[i];
    }
}


template<class K, class E>
open_hash_table<K, E>::~open_hash_table() = default;

template<class K, class E>
bool open_hash_table<K, E>::dizionarioVuoto() const {
    return numElementi == 0;
}

template<class K, class E>
int open_hash_table<K, E>::trovaPosizione(const chiave key) const {
    int i = (int) hashm(key) % divisore;
    return i;
}

template<class K, class E>
void open_hash_table<K, E>::inserisci(mypair<chiave, valore> &coppia) {
    int i = trovaPosizione(coppia.getChiave());
    if (ricerca(coppia.getChiave())) {
        cout << "Chiave " << coppia.getChiave()
             << " gia' esistente, ma e' possibile aggiornarne il valore con l'apposita funzione" << endl;
    } else {
        if (!tabella[i].ricercaElemento(coppia))
            tabella[i].inserisciCoda(coppia);
    }
    numElementi++;
}

template<class K, class E>
void open_hash_table<K, E>::cancella(const chiave key) {
    if (numElementi > 0) {
        if (ricerca(key)) {
            int i = hashm(key) % divisore;
            posizione p = tabella[i].primoLista();
            while (tabella[i].leggiLista(p).getChiave() != key) {
                p = tabella[i].succLista(p);
            }
            tabella[i].cancLista(p);
            numElementi--;
        } else throw std::out_of_range("CHIAVE NON  ESISTENTE");
    } else throw std::out_of_range("MAPPA VUOTA");
}


template<class K, class E>
typename open_hash_table<K, E>::valore open_hash_table<K, E>::recupera(const open_hash_table::chiave key) {
    if (ricerca(key)) {
        valore v;
        int i = hashm(key) % divisore;
        posizione p = tabella[i].primoLista();
        bool trov = false;
        while (!tabella[i].fineLista(p) && !trov) {
            if (tabella[i].leggiLista(p).getChiave() == key) {
                v = tabella[i].leggiLista(p).getValore();
                trov = true;
            } else p = tabella[i].succLista(p);
        }
        return v;
    }
    throw std::out_of_range("CHIAVE NON ESISTENTE");
}

template<class K, class E>
int open_hash_table<K, E>::dimensione() const {
    return numElementi;
}

template<class K, class E>
bool open_hash_table<K, E>::ricerca(const chiave key) const {
    int i = hashm(key) % divisore;
    posizione p = tabella[i].primoLista();
    while (!tabella[i].fineLista(p)) {
        if (tabella[i].leggiLista(p).getChiave() == key) {
            return true;
        } else p = tabella[i].succLista(p);
    }
    return false;
}


template<class K, class E>
bool open_hash_table<K, E>::contieneValore(const E &valore) const {
    for (int i = 0; i < divisore; i++) {
        posizione p = tabella[i].primoLista();
        while (!tabella[i].fineLista(p)) {
            if (tabella[i].leggiLista(p).getValore() == valore) return true;
            else p = tabella[i].succLista(p);
        }
    }
    return false;
}

//restituisce la lista dei valori memorizzati nel dizionario
template<class K, class E>
List_vector<E> open_hash_table<K, E>::values() const {
    List_vector<E> list;
    for (int i = 0; i < divisore; i++) {
        posizione p = tabella[i].primoLista();
        while (!tabella[i].fineLista(p)) {

            list.inserisciCoda(tabella[i].leggiLista(p).getValore());
            p = tabella[i].succLista(p);
        }
    }
    return list;
}

//restituisce la lista delle chiavi memorizzate nel dizionario
template<class K, class E>
List_vector<K> open_hash_table<K, E>::keys() const {
    List_vector<K> list;
    for (int i = 0; i < divisore; i++) {
        if (!tabella[i].listaVuota())
            list.inserisciCoda(tabella[i].leggiLista(tabella[i].primoLista()).getChiave());
    }
    return list;
}

template<class K, class E>
void open_hash_table<K, E>::modifica(const open_hash_table::chiave &key, const open_hash_table::valore &valore,
                                     const open_hash_table::valore &nuovoValore) {
    int i = trovaPosizione(key);
    if (tabella[i].listaVuota()) {
        cout << "Il valore chiave " << key << " non esiste, si prega di effettuare l'inserimento" << endl;
    } else {
        posizione p = tabella[i].primoLista();
        bool trov = false;
        while (!tabella[i].fineLista(p) && !trov) {
            if (tabella[i].leggiLista(p).getValore() != valore) p = tabella[i].succLista(p);
            else trov = true;
        }
        mypair<K, E> newCoppia(key, nuovoValore);
        if (trov) {
            tabella[i].scriviLista(newCoppia, p);
        }
    }
}

template<class K, class E>
void open_hash_table<K, E>::modifica(const open_hash_table::chiave &key, const open_hash_table::valore &nuovoValore) {
    int i = trovaPosizione(key);
    posizione p = tabella[i].primoLista();
    bool trov = false;
    while (!tabella[i].fineLista(p) && !trov) {
        if (tabella[i].leggiLista(p).getChiave() != key) p = tabella[i].succLista(p);
        else trov = true;
    }
    mypair<K, E> newCoppia(key, nuovoValore);
    if (trov) {
        tabella[i].scriviLista(newCoppia, p);
    }
}

template<class K, class E>
open_hash_table<K, E> &open_hash_table<K, E>::operator=(const open_hash_table<K, E> &mp) {
    if (this != &mp) {
        divisore = mp.divisore;
        numElementi = mp.numElementi;
        tabella = new List_vector<mypair<K, E>>[divisore];
        for (int i = 0; i < divisore; i++) {
            tabella[i] = mp.tabella[i];
        }
    }
    return *this;
}

template<class K, class E>
bool open_hash_table<K, E>::operator==(const open_hash_table<K, E> &coppia) {
    if (this->numElementi != coppia.dimensione()) return false;
    else {
        for (int i = 0; i < divisore; i++) {
            List_vector<mypair<K, E>> list1 = tabella[i], list2 = coppia.tabella[i];
            if (!(list1 == list2))
                return false;
        }
    }
    return true;
}

template<class K1, class E1>
ostream &operator<<(ostream &os, const open_hash_table<K1, E1> &mappa) {
    for (int i = 0; i < mappa.divisore; i++) {
        List_vector<mypair<K1, E1>> list = mappa.tabella[i];
        if (!list.listaVuota()) {
            os << "{";
            typename open_hash_table<K1, E1>::posizione position = list.primoLista();
            while (!list.fineLista(position)) {
                mypair<K1, E1> coppia(list.leggiLista(position));
                if (list.primoLista() == position) os << coppia;
                else os << ", " << coppia;
                position = list.succLista(position);
            }
            os << "}" << endl;
        }
    }
    return os;
}


#endif //REALIZZAZIONI_HASHTABLEAPERTO_H
