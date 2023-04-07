#ifndef REALIZZAZIONI_CODAPRIORITA_H
#define REALIZZAZIONI_CODAPRIORITA_H

#include <ostream>
#include <iostream>
#include <stdexcept>

using namespace std;

template<class T>
class codaPrior {
public:
    typedef T tipoelem;
    //COSTRUTTORI
    codaPrior();
    codaPrior(int);
    codaPrior(const codaPrior &);

    //DISTRUTTORE
    ~codaPrior();

    //OPERATORI
    void crea();
    bool vuoto() const;
    void inserisci(tipoelem);
    tipoelem min() const;
    void cancellaMin();
    void ordina();


    //SOVRACCARICO
    codaPrior<T> &operator=(const codaPrior<T> &);
    bool operator==(const codaPrior<T> &);

    //FUNZIONI DI SERVIZIO
    void stampa() const;

    //heapsort
private:
    tipoelem *elementi;
    int lunghezzaArray;
    int ultimo;
    void cambiaDimensione(int);
    void fix_up();
    void fix_down(int, int);
    bool esiste(tipoelem) const;
    void heapSort(tipoelem *, int);

};

#endif //REALIZZAZIONI_CODAPRIORITA_H

template<class T>
bool codaPrior<T>::esiste(tipoelem e) const {
    bool esiste = false;
    int i = 0;
    while (i < ultimo && !esiste) {
        if (elementi[i] == e) esiste = true;
        else i++;
    }
    return esiste;
}

template<class T>
codaPrior<T>::codaPrior() {
    lunghezzaArray = 20;
    crea();
}

template<class T>
codaPrior<T>::codaPrior(int dim) {
    lunghezzaArray = dim;
    crea();
}

template<class T>
codaPrior<T>::codaPrior(const codaPrior<T> &cp) {
    this->lunghezzaArray = cp.lunghezzaArray;
    this->ultimo = cp.ultimo;
    elementi = new tipoelem[lunghezzaArray];
    for (int i = 0; i < ultimo; i++) {
        elementi[i] = cp.elementi[i];
    }
}

template<class T>
codaPrior<T>::~codaPrior() {
    delete[] elementi;
}


template<class T>
void codaPrior<T>::crea() {
    ultimo = 0;
    elementi = new tipoelem[lunghezzaArray];
}

template<class T>
bool codaPrior<T>::vuoto() const {
    return (ultimo == 0);
}

template<class T>
void codaPrior<T>::inserisci(tipoelem e) {
    //da specifica sintattica posso inserire un elemento solo se questo non è gia presente
    if (!esiste(e)) {
        if (ultimo == lunghezzaArray) {
            cambiaDimensione(lunghezzaArray * 2);
            lunghezzaArray *= 2;
        }
        elementi[ultimo] = e;
        ultimo++;
        fix_up();
    }
}

template<class T>
typename codaPrior<T>::tipoelem codaPrior<T>::min() const {
    if (!vuoto())
        return elementi[0];
    else throw out_of_range("Coda vuota");
}


template<class T>
void codaPrior<T>::cancellaMin() {
    if (!vuoto()) {
        elementi[0] = elementi[ultimo - 1];
        ultimo--;
        fix_down(1, ultimo);
    } else throw out_of_range("Coda vuota");
}


template<class T>
void codaPrior<T>::stampa() const {
    cout << "[";
    for (int i = 0; i < ultimo; i++) {
        cout << elementi[i];
        if (i != ultimo - 1) cout << ", ";
    }
    cout << "]" << endl;
}

template<class T>
void codaPrior<T>::cambiaDimensione(int new_dim) {
    tipoelem *tmp = new tipoelem[new_dim];
    for (int i = 0; i < ultimo; i++)
        tmp[i] = elementi[i];
    delete[] elementi;
    elementi = tmp;
}


template<class T>
codaPrior<T> &codaPrior<T>::operator=(const codaPrior<T> &cp) {
    if (this != &cp) {
        delete[] elementi;
        ultimo = cp.ultimo;
        lunghezzaArray = cp.lunghezzaArray;
        elementi = new tipoelem[lunghezzaArray];
        for (int i = 0; i < ultimo; i++) {
            elementi[i] = cp.elementi[i];
        }
    }
    return *this;
}


template<class T>
bool codaPrior<T>::operator==(const codaPrior<T> &cp) {
    if (ultimo != cp.ultimo)
        return false;
    else {
        for (int i = 0; i < ultimo; i++) {
            if (elementi[i] != cp.elementi[i])
                return false;
        }
        return true;
    }
}


/* Per ripristinare i vincoli dello heap quando la priorità di un nodo è      *
 * cresciuta, ci spostiamo nello heap verso l'alto, scambiando, se necessario,*
 * il nodo in posizione k con il suo nodo padre (in posizione k/2),           *
 * continuando fintanto che heap[k]<heap[k/2] oppure fino a quando            *
 * raggiungiamo la cima dello heap.                                           */
template<class T>
void codaPrior<T>::fix_up() {
    int k = ultimo;
    tipoelem tmp;
    while (k > 1 && elementi[k - 1] < elementi[k / 2 - 1]) {
        tmp = elementi[k - 1];
        elementi[k - 1] = elementi[k / 2 - 1];
        elementi[k / 2 - 1] = tmp;
        k /= 2;
    }
}

/* Per ripristinare i vincoli dello heap quando la priorità di un nodo si è   *
 * ridotta, ci spostiamo nello heap verso il basso, scambiando, se necessario,*
 * il nodo in posizione k con il minore dei suoi nodi figli e arrestandoci    *
 * quando il nodo al posto k non è più grande di almeno uno dei suoi figli    *
 * oppure quando raggiungiamo il fondo dello heap. Si noti che se N è pari e  *
 * k è N/2, allora il nodo in posizione k ha un solo figlio: questo caso      *
 * particolare deve essere trattato in modo appropriato.                      */
template<class T>
void codaPrior<T>::fix_down(int corrente, int last) {
    bool scambio = true;
    tipoelem tmp;
    while (corrente <= last / 2 && scambio) {
        int j;
        //controllo se ha entrambi i figli, nel caso mi posiziono in quello con priorità minore
        if (corrente * 2 + 1 > ultimo) {
            if (elementi[corrente * 2] < elementi[corrente * 2 + 1])
                j = corrente * 2;
            else j = corrente * 2 + 1;
        } else j = corrente * 2;
        if (j < last && elementi[j - 1] > elementi[j])
            j++;
        scambio = elementi[j - 1] < elementi[corrente - 1];
        if (scambio) {
            tmp = elementi[corrente - 1];
            elementi[corrente - 1] = elementi[j - 1];
            elementi[j - 1] = tmp;
            corrente = j;
        }
    }
}


template<class T>
void codaPrior<T>::ordina() {
    if (!vuoto())
        heapSort(elementi, ultimo);
}

template<class T>
void codaPrior<T>::heapSort(tipoelem *array, int n) {
    codaPrior<int> c1(n);
    for (int i = 0; i < n; i++) {
        c1.inserisci(array[i]);
    }
    for (int j = 0; j < n; j++) {
        array[j] = c1.min();
        c1.cancellaMin();
    }
}

