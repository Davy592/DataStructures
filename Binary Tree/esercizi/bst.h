#ifndef REALIZZAZIONI_BST_H
#define REALIZZAZIONI_BST_H

#include "../alberoBinario_array.h"
#include <iostream>
#include <stdexcept>

using namespace std;

class BST {
public:
    //stabilisce se l'albero binario è un BST
    bool is_bst();

    //inserisci in modo ordinato nel BST il valore passato
    void insert(int);

    //verifica se un elemento appartiene al BST
    bool search(int);


    //restituisce il massimo valore dell albero
    int max();

    //restituisce il minimo valore dell albero
    int min();

    //stampa ordinata di un BST
    void print();

    //elimina l'elemento K dal BST
    void elimina(int k);

    //restituisce il successore di un nodo
    alberoBinario_array<int>::nodo sucessore(alberoBinario_array<int>::nodo);

    alberoBinario_array<int>::nodo predecessore(alberoBinario_array<int>::nodo);

private:
    alberoBinario_array<int> T;

    bool ricerca(int, alberoBinario_array<int>::nodo);

    void stampa(alberoBinario_array<int>::nodo);

    void verifica_bst(alberoBinario_array<int>::nodo, bool &);

    int max(alberoBinario_array<int>::nodo n);

    int min(alberoBinario_array<int>::nodo n);

    void cancellaNodo(alberoBinario_array<int>::nodo n, int k);
};


void BST::elimina(int k) {
    if (!T.alberoBinVuoto() && search(k)) {
        cancellaNodo(T.radice(), k);
    }
}

void BST::cancellaNodo(alberoBinario_array<int>::nodo n, int k) {
    if (k < T.leggiNodo(n) && !T.sinistroVuoto(n)) cancellaNodo(T.figlioSinistro(n), k);
    if (k > T.leggiNodo(n) && !T.destroVuoto(n)) cancellaNodo(T.figlioDestro(n), k);
        //CHIAVE TROVATA
    else {
        //CASO 1 -> STO ELIMINANDO UNA FOGLIA
        if (T.destroVuoto(n) && T.sinistroVuoto(n))
            T.cancellaSottoalbero(n);
            //CASO 2 -> IL NODO DA ELIMINARE HA DUE FIGLI
        else if (!T.sinistroVuoto(n) && !T.destroVuoto(n)) {
            //TROVA IL SUCCESSORE DA SOSTITUIRE
            alberoBinario_array<int>::nodo succ = sucessore(n);
            //copia il valore del successore nel nodo corrente
            T.scriviNodo(n, T.leggiNodo(succ));
            //cancella ricorsivamente il successivo
            cancellaNodo(T.figlioSinistro(n), T.leggiNodo(succ));
        }
            //CASO 3 -> IL NODO HA SOLO UN FIGLIO
        else {
            alberoBinario_array<int>::nodo figlio;
            if (T.destroVuoto(n))
                figlio = T.figlioSinistro(n);
            else
                figlio = T.figlioDestro(n);
            T.scriviNodo(n, T.leggiNodo(figlio));
            //cancella ricorsivamente il successivo
            cancellaNodo(T.figlioSinistro(n), T.leggiNodo(figlio));
        }
    }
}

//ricerca un elemento nel BST
bool BST::search(int k) {
    bool esiste = false;
    if (!T.alberoBinVuoto()) {
        esiste = ricerca(k, T.radice());
    }
    return esiste;
}

bool BST::ricerca(int k, alberoBinario_array<int>::nodo n) {
    if (T.leggiNodo(n) == k) return true;
    if (k < T.leggiNodo(n) && !T.sinistroVuoto(n)) return ricerca(k, T.figlioSinistro(n));
    if (k > T.leggiNodo(n) && !T.destroVuoto(n)) return ricerca(k, T.figlioDestro(n));
    return false;

}

//inserisci in modo ordinato nel BST il valore passato
void BST::insert(int k) {
    if (!search(k)) {
        if (T.alberoBinVuoto()) {
            T.inserisciRadice(k);
        } else {
            alberoBinario_array<int>::nodo n = T.radice();
            bool continua = true;
            while (continua) {
                if (k < T.leggiNodo(n) && !T.sinistroVuoto(n)) n = T.figlioSinistro(n);
                else if (k > T.leggiNodo(n) && !T.destroVuoto(n)) n = T.figlioDestro(n);
                else continua = false;
            }
            if (k < T.leggiNodo(n)) {
                T.inserisciSinistro(n, k);
            } else {
                T.inserisciDestro(n, k);
            }
        }
    }
}

int BST::max() {
    if (!T.alberoBinVuoto()) {
        return max(T.radice());

    } else throw out_of_range("ALBERO VUOTO");
}

int BST::max(alberoBinario_array<int>::nodo n) {
    if (T.destroVuoto(n)) return T.leggiNodo(n);
    else return max(T.figlioDestro(n));
}


int BST::min() {
    if (!T.alberoBinVuoto()) {
        return min(T.radice());
    } else throw out_of_range("ALBERO VUOTO");
}

int BST::min(alberoBinario_array<int>::nodo n) {
    if (T.sinistroVuoto(n)) return T.leggiNodo(n);
    else return min(T.figlioSinistro(n));
}

bool BST::is_bst() {
    if (!T.alberoBinVuoto()) {
        bool isBst = true;
        verifica_bst(T.radice(), isBst);
        return isBst;
    }
    return true;
}


void BST::verifica_bst(alberoBinario_array<int>::nodo n, bool &isBst) {
    if (isBst) {
        //calcolo MAX e MIN dell'albero avente come radice N
        int min_value = min(n);
        int max_value = max(n);
        if (max_value < T.leggiNodo(n) || min_value > T.leggiNodo(n)) isBst = false;
        //verifico se il valore di N esiste gia nei suoi sottoalberi, nel caso esista gia allora non è un BST
        if (!T.sinistroVuoto(n))
            if (ricerca(T.leggiNodo(n), T.figlioSinistro(n)))
                isBst = false;
        if (!T.destroVuoto(n))
            if (ricerca(T.leggiNodo(n), T.figlioDestro(n)))
                isBst = false;
        if (isBst) {
            if (!T.sinistroVuoto(n)) verifica_bst(T.figlioSinistro(n), isBst);
            if (!T.destroVuoto(n)) verifica_bst(T.destroVuoto(n), isBst);
        }
    }
}

void BST::print() {
    cout << "[ ";
    if (!T.alberoBinVuoto()) {
        stampa(T.radice());
    }
    cout << "]" << endl;
}

void BST::stampa(alberoBinario_array<int>::nodo n) {
    if (!T.sinistroVuoto(n)) stampa(T.figlioSinistro(n));
    cout << T.leggiNodo(n) << " ";
    if (!T.destroVuoto(n)) stampa(T.figlioDestro(n));
}


//restituisce il successore di un nodo
alberoBinario_array<int>::nodo BST::sucessore(alberoBinario_array<int>::nodo n) {
    // Se il nodo ha un figlio destro, il successore è il nodo
    // più a sinistra del sottoalbero destro di n
    if (!T.destroVuoto(n)) {
        n = T.figlioDestro(n);
        while (!T.sinistroVuoto(n)) {
            n = T.figlioSinistro(n);
        }
        return n;
    }
    // Altrimenti, il successore è il piu piccolo antenato di n il cui figlio sinistro è antenato di n
    alberoBinario_array<int>::nodo p;
    if (n != T.radice()) p = T.genitore(n);
    while (p != T.radice() && n == T.figlioDestro(n)) {
        n = p;
        p = T.genitore(p);
    }
    return p;
}

//restituisce il predecessore di un un nodo
alberoBinario_array<int>::nodo BST::predecessore(alberoBinario_array<int>::nodo n) {
// Verifica se n ha un figlio sinistro
    if (!T.sinistroVuoto(n)) {
        // Se n ha un figlio sinistro, il predecessore di n è il nodo più a destra della sua sottostruttura di sinistra
        n = T.figlioSinistro(n);
        while (!T.destroVuoto(n)) {
            n = T.figlioDestro(n);
        }
        return n;
    } else {
        // Se n non ha figli sinistri, il predecessore di n è il primo antenato di n che sia a sinistra del suo genitore
        alberoBinario_array<int>::nodo p;
        if (n != T.radice()) p = T.genitore(n);
        while (p != T.radice() && T.figlioSinistro(n) == n) {
            n = p;
            p = T.genitore(p);
        }
        return p;
    }
}


#endif //REALIZZAZIONI_BST_H
