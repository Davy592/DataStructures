#ifndef REALIZZAZIONI_HASHTABLECHIUSO_H
#define REALIZZAZIONI_HASHTABLECHIUSO_H

#include "dizionario.h"
#include "../List/List_vector.h"
#include <string>
#include <stdexcept>

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
class hash_table : public dizionario<K, E> {
public:
    typedef typename dizionario<K, E>::valore valore;
    typedef typename dizionario<K, E>::chiave chiave;

    //costruttore default
    hash_table();
    //costruttore con dimensione stabilita
    hash_table(int);
    //costruttore copia
    hash_table(const hash_table &);
    ~hash_table();


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
    void modifica(const chiave &, const valore &);


    //sovraccarico

    hash_table<K, E> &operator=(const hash_table<K, E> &);
    bool operator==(const hash_table<K, E> &);
    template<class K1, class E1>
    friend ostream &operator<<(ostream &, const hash_table<K1, E1> &);

private:
    void cambiaDimensione();
    mypair<chiave, valore> **tabella;
    int numElementi;
    int divisore;


    my_hash<K> hashm;
};


template<class K, class E>
hash_table<K, E>::hash_table() {
    divisore = 20;
    numElementi = 0;
    tabella = new mypair<chiave, valore> *[divisore];
    for (int i = 0; i < divisore; i++) {
        tabella[i] = nullptr;
    }
}

template<class K, class E>
hash_table<K, E>::hash_table(const hash_table<K, E> &mp) {
    divisore = mp.divisore;
    numElementi = mp.numElementi;
    tabella = new mypair<chiave, valore> *[divisore];
    for (int i = 0; i < divisore; i++) {
        if (mp.tabella[i] == nullptr)
            tabella[i] = nullptr;
        else {
            mypair<K, E> coppia(mp.tabella[i]->getChiave(), mp.tabella[i]->getValore());
            tabella[i] = new mypair<chiave, valore>(coppia);
        }
    }
}

template<class K, class E>
hash_table<K, E>::hash_table(int divisore) {
    this->divisore = divisore;
    this->numElementi = 0;
    tabella = new mypair<chiave, valore> *[divisore];
    for (int i = 0; i < divisore; i++) {
        tabella[i] = nullptr;
    }
}


template<class K, class E>
hash_table<K, E>::~hash_table() {
    for (int i = 0; i < divisore; i++) {
        tabella[i] = nullptr;
    }
    delete[] tabella;
}

template<class K, class E>
bool hash_table<K, E>::dizionarioVuoto() const {
    return numElementi == 0;
}

template<class K, class E>
int hash_table<K, E>::trovaPosizione(const chiave key) const {
    int i = (int) hashm(key) % divisore;
    int j = i;
    do {
        if (tabella[j] == nullptr || tabella[j]->getChiave() == key)
            return j;
        j = (j + 1) % divisore;
    } while (j != i);
    return j;
}

template<class K, class E>
void hash_table<K, E>::inserisci(mypair<chiave, valore> &coppia) {

    if ((double) numElementi >= (double) divisore * 0.7) {
        cambiaDimensione();
        divisore *= 2;
    }

    int i = trovaPosizione(coppia.getChiave());
    if (tabella[i] == nullptr) {
        tabella[i] = new mypair<chiave, valore>(coppia);
        numElementi++;
    } else {
        if (tabella[i]->getChiave() == coppia.getChiave()) {
            cout << "Chiave " << coppia.getChiave()
                 << " gia' esistente, ma e' possibile aggiornarne il valore con l'apposita funzione" << endl;
        } else throw std::out_of_range("MAPPA PIENA");
    }
}

template<class K, class E>
void hash_table<K, E>::cancella(const chiave key) {
    if (numElementi > 0) {
        if (ricerca(key)) {
            int i = hashm(key) % divisore;
            int j = i;
            bool eliminato = false;
            do {

                if (tabella[j]->getChiave() == key) {
                    tabella[j] = nullptr;
                    numElementi--;
                    eliminato = true;
                }
                j = (j + 1) % divisore;
            } while (j != i && !eliminato);
        } else throw std::out_of_range("CHIAVE NON  ESISTENTE");
    } else throw std::out_of_range("MAPPA VUOTA");
}

template<class K, class E>
typename hash_table<K, E>::valore hash_table<K, E>::recupera(const hash_table::chiave key) {
    if (ricerca(key)) {
        int i = funzione_hash(key) % divisore;
        int j = i;
        do {

            if (tabella[j] != nullptr && tabella[j]->getValore() == key) {
                valore valore1 = tabella[j]->getValore();
                return valore1;
            }
            j = (j + 1) % divisore;
        } while (j != i);
    }
    throw std::out_of_range("CHIAVE NON ESISTENTE");
}

template<class K, class E>
int hash_table<K, E>::dimensione() const {
    return numElementi;
}

template<class K, class E>
bool hash_table<K, E>::ricerca(const chiave key) const {
    bool trov = false;
    int i = hashm(key) % divisore;
    int j = i;
    do {

        if (tabella[j] != nullptr && tabella[j]->getChiave() == key) trov = true;
        j = (j + 1) % divisore;
    } while (j != i);
    return trov;
}


template<class K, class E>
bool hash_table<K, E>::contieneValore(const E &valore) const {
    for (int i = 0; i < divisore; i++) {
        if (tabella[i] != nullptr && tabella[i]->getValore() == valore) return true;
    }
    return false;
}

//restituisce la lista dei valori memorizzati nel dizionario
template<class K, class E>
List_vector<E> hash_table<K, E>::values() const {
    List_vector<E> list;
    for (int i = 0; i < divisore; i++) {
        if (tabella[i] != nullptr && tabella[i] != nullptr) list.inserisciCoda(tabella[i]->getValore());
    }
    return list;
}

//restituisce la lista delle chiavi memorizzate nel dizionario
template<class K, class E>
List_vector<K> hash_table<K, E>::keys() const {
    List_vector<K> list;
    for (int i = 0; i < divisore; i++) {
        if (tabella[i] != nullptr) list.inserisciCoda(tabella[i]->getChiave());
    }
    return list;
}

template<class K, class E>
void hash_table<K, E>::modifica(const hash_table::chiave &key, const hash_table::valore &valore) {
    int i = trovaPosizione(key);
    if (tabella[i] == nullptr) {
        cout << "Il valore chiave " << key << " non esiste, si prega di effettuare l'inserimento" << endl;
    } else {
        if (tabella[i]->getChiave() == key) {
            tabella[i]->setValore(valore);
        }

    }
}

template<class K, class E>
void hash_table<K, E>::cambiaDimensione() {
    mypair<K, E> **tmp = new mypair<K, E> *[divisore * 2];
    for (int i = 0; i < divisore; i++) {
        if (tabella[i] != nullptr) {
            mypair<K, E> coppia(tabella[i]->getChiave(), tabella[i]->getValore());
            tmp[i] = new mypair<chiave, valore>(coppia);
        } else tmp[i] = nullptr;
    }
    for (int i = divisore; i < divisore * 2; i++) tmp[i] = nullptr;
    for (int i = 0; i < divisore; i++) {
        tabella[i] = nullptr;
    }
    delete[] tabella;
    tabella = tmp;
}

template<class K, class E>
hash_table<K, E> &hash_table<K, E>::operator=(const hash_table<K, E> &mp) {
    if (this != &mp) {
        divisore = mp.divisore;
        numElementi = mp.numElementi;
        tabella = new mypair<chiave, valore> *[divisore];
        for (int i = 0; i < divisore; i++) {
            if (mp.tabella[i] == nullptr)
                tabella[i] = nullptr;
            else {
                mypair<K, E> coppia(mp.tabella[i]->getChiave(), mp.tabella[i]->getValore());
                tabella[i] = new mypair<chiave, valore>(coppia);
            }
        }
    }
    return *this;
}

template<class K, class E>
bool hash_table<K, E>::operator==(const hash_table<K, E> &coppia) {
    if (this->numElementi != coppia.dimensione()) return false;
    else {
        for (int i = 0; i < divisore; i++) {
            if (tabella[i] != nullptr) {
                if (!coppia.contieneValore(tabella[i]->getValore())) return false;
            }
        }
    }
    return true;
}

template<class K1, class E1>
ostream &operator<<(ostream &os, const hash_table<K1, E1> &coppia) {
    os << "{";
    for (int i = 0; i < coppia.divisore; i++) {
        if (coppia.tabella[i] != nullptr) {
            mypair<K1, E1> cp(coppia.tabella[i]->getChiave(), coppia.tabella[i]->getValore());
            if (i == 0) os << cp;
            else os << ", " << cp;
        }
    }
    os << "}" << endl;
    return os;
}

#endif