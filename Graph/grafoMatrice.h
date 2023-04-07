#ifndef REALIZZAZIONI_GRAFOMATRICE_H
#define REALIZZAZIONI_GRAFOMATRICE_H

#include <stdexcept>
#include <ostream>
#include "grafo.h"

using namespace std;

template<class E, class P>
class grafoMat;

template<class P>
class infoArco {
public:
    P peso;
    bool vuoto;

    infoArco() {
        vuoto = true;
    }
};


template<class E, class P>
class infoNodo {
    friend class grafoMat<E, P>;

public:
    E etichetta;
    bool vuoto;
    infoArco<P> *archi;

    infoNodo() {
        vuoto = true;
    }

    ~infoNodo() {
        if (vuoto)
            delete[] archi;
    }

private:
    int id;
};


class nodoG {
public:
    nodoG(int i) {
        nodoId = i;
    }

    nodoG() {
        nodoId = -1;
    }

    int getId() const { return nodoId; }

    void setId(const int id) { nodoId = id; }

    bool operator==(nodoG n1) {
        return this->nodoId == n1.nodoId;
    }

    friend ostream &operator<<(ostream &os, nodoG &n) {
        os << n.getId() << " ";
        return os;
    }

private:
    int nodoId;
};


template<class E, class P>
class grafoMat : public grafo<E, P, nodoG> {
public:
    typedef E etichetta;
    typedef P peso;
    typedef nodoG nodo;
    typedef arco<peso, nodo> arco;
    typedef typename grafo<E, P, nodoG>::listaNodi listaNodi;
    typedef typename grafo<E, P, nodoG>::listaArchi listaArchi;
    typedef typename grafo<E, P, nodoG>::posizioneListaNodi posizioneListaNodi;
    typedef typename grafo<E, P, nodoG>::posizioneListaArchi posizioneListaArchi;

    grafoMat();

    grafoMat(int);

    ~grafoMat();

    bool vuoto() const;

    void insNodo(nodoG &);

    void insArco(const nodo, const nodo, const peso);

    void cancNodo(nodo &);

    void cancArco(nodo, nodo);

    bool esisteNodo(nodo) const;

    bool esisteArco(arco) const;

    listaNodi adiacenti(nodo) const;

    listaNodi list_nodi() const;

    etichetta leggiEtichetta(nodo) const;

    void scriviEtichetta(nodo, etichetta &);

    peso leggiPeso(nodo, nodo) const;

    void scriviPeso(nodo, nodo, peso);

    int numNodi() {
        return nodi;
    };

    int numArchi() {
        return archi;
    };

    //ALGORITMI DI VISITA
    void bfs(nodo) const;

    void dfs(nodo) const;

    //FUNZIONI AGGIUNTIVE

    //NUMERO ARCHI ENTRANTI NEL NODO N
    int inDegree(nodo n);

    //NUMERO ARCHI USCENTI DAL NODO N
    int outDegree(nodo n);

    //MEDIA DEL NUMERO DI ARCHI USCENTI PER OGNI NODO DEL GRAFO
    double meanOutDegree();

    //SE ESISTE UN PERCORSO TRA N E D LO STAMPA
    void findPath(nodo n, nodo d);


private:
    infoNodo<E, P> *matrice;
    int dimensione;
    int nodi;
    int archi;

    bool inseribile(nodo);
    void dfs(nodo, int[]) const;
    listaNodi getPath(nodo n1, nodo n2);
};


template<class E, class P>
grafoMat<E, P>::grafoMat() {
    dimensione = 20;
    nodi = 0;
    archi = 0;
    matrice = new infoNodo<E, P>[dimensione];
    for (int i = 0; i < dimensione; i++) {
        matrice[i].archi = new infoArco<P>[dimensione];
    }
}

template<class E, class P>
grafoMat<E, P>::grafoMat(int dimensione) {
    this->dimensione = dimensione;
    nodi = 0;
    archi = 0;
    matrice = new infoNodo<E, P>[dimensione];
    for (int i = 0; i < dimensione; i++) {
        matrice[i].archi = new infoArco<P>[dimensione];
    }
}

template<class E, class P>
grafoMat<E, P>::~grafoMat() {
    for (int i = 0; i < dimensione; i++) {
        if (!matrice[i].vuoto) {
            delete[] matrice[i].archi;
        }
    }
    delete[] matrice;
}

template<class E, class P>
bool grafoMat<E, P>::vuoto() const {
    return (nodi == 0);
}

template<class E, class P>
void grafoMat<E, P>::insNodo(nodoG &n) {
    if (inseribile(n)) {
        if (nodi < dimensione) {
            int i = 0;
            while (matrice[i].vuoto == false) {
                i++;
            }
            matrice[i].vuoto = false;
            n.setId(i);
            nodi++;
        } else throw out_of_range("GRAFO COMPLETO, IMPOSSIBILE INSERIRE ALTRI NODI");
    } else throw out_of_range("NODO GIA PRESENTE");
}

template<class E, class P>
void grafoMat<E, P>::insArco(const nodo u, const nodo v, const peso p) {
    arco a(u, v);
    if (!esisteArco(a)) {
        matrice[u.getId()].archi[v.getId()].vuoto = false;
        matrice[u.getId()].archi[v.getId()].peso = p;
        archi++;
    } else throw out_of_range("ARCO GIA' PRESENTE");
}

template<class E, class P>
void grafoMat<E, P>::cancNodo(nodo &n) {
    if (esisteNodo(n)) {
        //IL NODO PUO ESSERE ELIMINATO SOLO SE NON VI SONO ARCHI A ESSO COLLEGATI
        int eliminato = true;
        int i = 0;
        int j = 0;

        //VERIFICO CHE NON VI SIANO ARCHI USCENTI
        while (i < dimensione && eliminato == true) {
            if (matrice[n.getId()].archi[i].vuoto == false) eliminato = false;
            else i++;
        }

        //VERIFICO CHE NON VI SIANO ARCHI ENTRANI
        while (j < dimensione && eliminato == true) {
            if (!matrice[j].vuoto && matrice[j].archi[n.getId()].vuoto == false) eliminato = false;
            else j++;
        }
        if (eliminato) {
            matrice[n.getId()].vuoto = true;
            nodi--;
            n.setId(-1);
        } else cout << "IMPOSSIBILE ELIMINARE NODO, VI SONO ARCHI A ESSO COLLEGATI" << endl;
    } else throw out_of_range("NODO NON ESISTENTE");
}

template<class E, class P>
void grafoMat<E, P>::cancArco(nodo u, nodo v) {
    arco a(u, v);
    if (esisteArco(a)) {
        matrice[u.getId()].archi[v.getId()].vuoto = true;
        archi--;
    } else throw out_of_range("ARCO NON ESISTENTE");
}

template<class E, class P>
typename grafoMat<E, P>::listaNodi grafoMat<E, P>::adiacenti(nodo n) const {
    listaNodi list;
    for (int i = 0; i < dimensione; i++) {
        if (matrice[n.getId()].archi[i].vuoto == false) {
            nodo v(i);
            list.inserisciTesta(v);
        }
    }
    return list;
}

template<class E, class P>
typename grafoMat<E, P>::listaNodi grafoMat<E, P>::list_nodi() const {
    listaNodi list;
    for (int i = 0; i < dimensione; i++) {
        if (matrice[i].vuoto == false) {
            nodo n;
            n.setId(i);
            list.inserisciTesta(n);
        }
    }
    return list;
}

template<class E, class P>
bool grafoMat<E, P>::esisteNodo(nodo n) const {
    if (n.getId() >= 0)
        return !matrice[n.getId()].vuoto;
    else
        return false;
}

template<class E, class P>
bool grafoMat<E, P>::inseribile(nodo n) {
    if (n.getId() < 0)
        return true;
    else
        return matrice[n.getId()].vuoto;
}

template<class E, class P>
bool grafoMat<E, P>::esisteArco(arco a) const {
    if (esisteNodo(a.nodo1) && esisteNodo(a.nodo2))
        return !matrice[a.nodo1.getId()].archi[a.nodo2.getId()].vuoto;
    else
        throw out_of_range("ALMENO UNO DEI DUE NODI DELL'ARCO NON APPARTIENE AL GRAFO");
};

template<class E, class P>
typename grafoMat<E, P>::etichetta grafoMat<E, P>::leggiEtichetta(nodo n) const {
    if (esisteNodo(n)) {
        return matrice[n.getId()].etichetta;
    } else throw std::out_of_range("NODO NON ESISTETE");
}

template<class E, class P>
void grafoMat<E, P>::scriviEtichetta(nodo n, etichetta &e) {
    if (esisteNodo(n)) {
        matrice[n.getId()].etichetta = e;
    } else throw std::out_of_range("NODO NON ESISTETE");
}

template<class E, class P>
typename grafoMat<E, P>::peso grafoMat<E, P>::leggiPeso(nodo u, nodo v) const {
    arco a(u, v);
    if (esisteArco(a)) {
        return matrice[u.getId()].archi[v.getId()].peso;
    } else throw std::out_of_range("NON ESISTE ARCO");
}

template<class E, class P>

void grafoMat<E, P>::scriviPeso(nodo u, nodo v, peso p) {
    arco a(u, v);
    if (esisteArco(a)) {
        matrice[u.getId()].archi[v.getId()].peso = p;
    } else throw std::out_of_range("NON ESISTE ARCO");
}


template<class E, class P>
void grafoMat<E, P>::dfs(nodo n) const {
    cout << "[";
    if (!vuoto() && esisteNodo(n)) {
        int visitato[dimensione];
        for (int i = 0; i < dimensione; i++) {
            if (!matrice[i].vuoto)
                visitato[i] = 0; //NODO ESISTENTE MA NON VISITATO
            else
                visitato[i] = -1; //NODO NON ESISTE
        }
        dfs(n, visitato);

    }
    cout << "]" << endl;
}

template<class E, class P>
void grafoMat<E, P>::dfs(nodo n, int visitato[]) const {
    listaNodi nodiAdiacenti;
    nodiAdiacenti = adiacenti(n);
    cout << " " << leggiEtichetta(n);
    visitato[n.getId()] = 1;
    if (!nodiAdiacenti.listaVuota()) {
        posizioneListaNodi p = nodiAdiacenti.primoLista();
        while (!nodiAdiacenti.fineLista(p)) {
            nodo v = nodiAdiacenti.leggiLista(p);
            if (visitato[v.getId()] == 0)
                dfs(v, visitato);
            p = nodiAdiacenti.succLista(p);
        }
    }
}


template<class E, class P>
void grafoMat<E, P>::bfs(nodo n) const {
    cout << "[";
    if (!vuoto() && esisteNodo(n)) {
        //PASSAGGI PRELIMINARI
        listaNodi ln;
        posizioneListaNodi p;
        nodo v;
        int visitato[dimensione];
        for (int i = 0; i < dimensione; i++) {
            if (!matrice[i].vuoto)
                visitato[i] = 0; //NODO ESISTENTE MA NON VISITATO
            else
                visitato[i] = -1; //NODO NON ESISTE
        }
        //ALGORITMO DI BFS
        codav<nodo> q;
        q.incoda(n);
        while (!q.codaVuota()) {
            n = q.leggiCoda();
            q.fuoriCoda();
            if (visitato[n.getId()] == 0)
                cout << leggiEtichetta(n) << " ";
            visitato[n.getId()] = 1;
            ln = adiacenti(n);
            p = ln.primoLista();
            while (!ln.fineLista(p)) {
                v = ln.leggiLista(p);
                if (visitato[v.getId()] == 0 && !q.esiste(v)) {
                    q.incoda(v);
                }
                p = ln.succLista(p);
            }
        }
    }
    cout << "]" << endl;
}

template<class E, class P>
int grafoMat<E, P>::inDegree(nodo n) {
    if (esisteNodo(n)) {
        int counter = 0;
        for (int j = 0; j < dimensione; j++) {
            if (matrice[j].archi[n.getId()].vuoto == false) counter++;
        }
        return counter;
    } else return -1;
}

template<class E, class P>
int grafoMat<E, P>::outDegree(nodo n) {
    if (esisteNodo(n)) {
        return adiacenti(n).lunghezza();
    } else return -1;
}


template<class E, class P>
double grafoMat<E, P>::meanOutDegree() {
    if (archi > 0) {
        int counter = 0;
        for (int i = 0; i < dimensione; i++) {
            if (!matrice[i].vuoto) {
                nodo n;
                n.setId(i);
                counter += adiacenti(n).lunghezza();
            }
        }
        return (double) counter / numNodi();
    } else return 0;
}


template<class E, class P>
void grafoMat<E, P>::findPath(nodo n, nodo d) {
    if (esisteNodo(n) && esisteNodo(d)) {
        listaNodi percorso = getPath(n, d);
        if (percorso.lunghezza() > 0) {
            cout << "[ ";
            posizioneListaNodi p = percorso.primoLista();
            while (!percorso.fineLista(p)) {
                int id = percorso.leggiLista(p).getId();
                cout << matrice[id].etichetta << " ";
                p = percorso.succLista(p);
            }
            cout << "]" << endl;
        } else cout << "NON ESISTE CAMMINO" << endl;
    }
}


template<class E, class P>
typename grafoMat<E, P>::listaNodi grafoMat<E, P>::getPath(nodo n1, nodo n2) {
    // PASSAGGI PRELIMINARI
    int visitato[dimensione];
    nodo padre[dimensione]; // NUOVO ARRAY PER SALVARE IL PADRE DI OGNI NODO
    for (int i = 0; i < dimensione; i++) {
        if (!matrice[i].vuoto) {
            visitato[i] = 0; // NODO ESISTENTE MA NON VISITATO
            padre[i] = nodo(-1); // NODO NON HA PADRE
        } else {
            visitato[i] = -1; // NODO NON ESISTE
        }
    }

    // CREA UNA CODA VUOTA
    codav<nodo> s;

    // AGGIUNGO IL NODO DI PARTENZA ALLA CODA
    s.incoda(n1);
    // RIPETI FINCHE LA CODA NON E' VUOTA
    while (!s.codaVuota()) {
// PRENDI IL PRIMO NODO DALLA CODA E ELIMINALO
        nodo n = s.leggiCoda();
        s.fuoriCoda();
        //MARCA IL NODO COME VISITATO
        visitato[n.getId()] = 1;

        // SE IL NODO E' IL NODO "DESTINAZIONE", RISALI IL PERCORSO USANDO L'ARRAY "PADRE"
        // E RITORNA LA LISTA DEI NODI VISITATI
        if (n.getId() == n2.getId()) {
            listaNodi percorso;
            percorso.inserisciCoda(n);
            while (!(padre[n.getId()] == -1)) {
                n = padre[n.getId()];
                percorso.inserisciTesta(n);
            }
            return percorso;
        }

        // AGGIUNGI I VICINI NON VISITATI ALLA CODA E SALVA IL LORO PADRE
        listaNodi vicini = adiacenti(n);
        posizioneListaNodi i = vicini.primoLista();
        while (!vicini.fineLista(i)) {
            nodo vicino = vicini.leggiLista(i);
            if (visitato[vicino.getId()] == 0 && !s.esiste(vicino)) {
                s.incoda(vicino);
                padre[vicino.getId()] = n; // SALVA IL NODO PADRE
            }
            i = vicini.succLista(i);
        }
    }

// SE LA CODA DIVENTA VUOTA PRIMA CHE IL NODO "DESTINAZIONE" SIA TROVATO, RITORNA UNA LISTA VUOTA
    return listaNodi();
}

#endif //REALIZZAZIONI_GRAFOMATRICE_H
