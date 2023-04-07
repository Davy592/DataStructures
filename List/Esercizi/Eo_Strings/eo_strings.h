#ifndef REALIZZAZIONI_EO_STRINGS_H
#define REALIZZAZIONI_EO_STRINGS_H

#include <string>
#include "../../Linked_list.h"

using namespace std;

class eo_strings {
public:
    //Costruttore
    eo_strings();

    //distruttore
    ~eo_strings();

    //inserisci una stringa nella lista corrispondente
    void inserisci(string s);

    // rimuove la stringa dalla corrispondente lista
    void rimuovi(string s);

// rimuove le stringhe di lunghezza pari che iniziano con il carattere c
    void rimuovi(char c);

// restituisce il numero di stringhe di lunghezza pari
    int freq_pari();

// visualizza le stringhe di lunghezza dispari ordinate per lunghezza
    void visualizza_dispari();


    //funzioni utili
    bool ricerca_stringa(const Linked_list<string> &list, const string s);
    void stampaTutto();

private:
    Linked_list<string> pari;
    Linked_list<string> dispari;
};

eo_strings::eo_strings() {
}

eo_strings::~eo_strings() {}

void eo_strings::inserisci(std::string s) {
    if ((s.length() % 2) == 0)
        pari.inserisciTesta(s);
    else
        dispari.inserisciTesta(s);
}

bool eo_strings::ricerca_stringa(const Linked_list<std::string> &list, const std::string s) {
    Linked_list<string>::posizione p = list.primoLista();
    bool trov = false;
    while (!list.fineLista(p) && !trov) {
        if (list.leggiLista(p) == s) trov = true;
        else p = list.succLista(p);
    }
    return trov;
}

void eo_strings::rimuovi(std::string s) {
    if ((s.length() % 2) == 0) {
        if (ricerca_stringa(pari, s)) {
            Linked_list<string>::posizione p = pari.primoLista();
            while (pari.leggiLista(p) != s) {
                p = pari.succLista(p);
            }
            pari.cancLista(p);
        }
    } else {
        if (ricerca_stringa(dispari, s)) {
            Linked_list<string>::posizione p = dispari.primoLista();
            while (dispari.leggiLista(p) != s) {
                p = dispari.succLista(p);
            }
            dispari.cancLista(p);
        }
    }
}

void eo_strings::rimuovi(char c) {
    Linked_list<string>::posizione p = pari.primoLista();
    while (!pari.fineLista(p)) {
        string s = pari.leggiLista(p);
        if (s[0] == c) {
            pari.cancLista(p);
        } else {
            p = pari.succLista(p);
        }
    }
}

int eo_strings::freq_pari() {
    return pari.lunghezza();
}

//visualizza le stringhe di lunghezza dispari ordinate per lunghezza
void eo_strings::visualizza_dispari() {
    Linked_list<string> tmp;
    Linked_list<string>::posizione p = dispari.primoLista();
    while (!dispari.fineLista(p)) {
        Linked_list<string>::posizione pt = tmp.primoLista();
        string s = dispari.leggiLista(p);
        if (tmp.lunghezza() == 0) tmp.inserisciTesta(s);
        else {
            bool insert = false;
            while (!insert && !tmp.fineLista(pt)) {
                if (tmp.leggiLista(pt).length() > s.length())
                    insert = true;
                else
                    pt = tmp.succLista(pt);
            }
            tmp.insLista(s, pt);
        }

        p = dispari.succLista(p);
    }
    cout << tmp << endl;
}

void eo_strings::stampaTutto() {
    cout << "STAMPA DELLE PARI" << endl;
    Linked_list<string>::posizione p = pari.primoLista();
    while (!pari.fineLista(p)) {
        cout << pari.leggiLista(p) << endl;
        p = pari.succLista(p);
    }
    cout << "STAMPA DELLE DISPARI" << endl;
    p = dispari.primoLista();
    while (!dispari.fineLista(p)) {
        cout << dispari.leggiLista(p) << endl;
        p = dispari.succLista(p);
    }
}

#endif //REALIZZAZIONI_EO_STRINGS_H
