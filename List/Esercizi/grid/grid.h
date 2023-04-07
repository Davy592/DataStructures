#ifndef REALIZZAZIONI_GRID_H
#define REALIZZAZIONI_GRID_H

#include "../../Linked_list.h"
#include "cell.h"

//DA INSERIRE LE PRE-CONDIZIONI e i controlli sulle celle e le eccezioni
class grid
{
public:
    ~grid();

    grid(int,int);
// inserisce una cella viva nella griglia
    void insert(cell &);
// rimuove una cella nella griglia
    void remove(cell &);
// sposta a sinistra di una posizione la cella viva presente in posizione (x,y)
    void moveLeft(int x, int y);
// sposta a destra di una posizione la cella viva presente in posizione (x,y)
    void moveRight(int x, int y);
// sposta in alto di una posizione la cella viva presente in posizione (x,y)
    void moveUpper(int x, int y);
// sposta in basso di una posizione la cella viva presente in posizione (x,y)
    void moveDown(int x, int y);
// stabilisce se la cella viva presente in posizione (x,y) `e circondata,
// ovvero tutte le celle vicine alla cella data sono vive
    bool surrounded(int x, int y);
// rimuove dalla griglia tutte le celle circondate
    void removeSurrounded();

    //funzioni stampa
    void stampa();
private:
    Linked_list<cell> list;
    int n; //righe (la x della cella)
    int m; //colonne (la y della cella)
};




grid::grid(int n,int m): n(n),m(m) {
}




//inserisci cella viva
void grid::insert(cell & c) {
    list.inserisciTesta(c);
}

// rimuove una cella nella griglia
void grid::remove(cell & c)
{
    if (list.ricercaElemento(c))
    {
        Linked_list<cell>::posizione p=list.primoLista();
        while (c!=list.leggiLista(p))
        {
            p=list.succLista(p);
        }
        list.cancLista(p);
    }
}
// sposta a sinistra di una posizione la cella viva presente in posizione (x,y)
void grid::moveLeft(int x, int y)
{
    //le operazioni possono svolgersi solo se non mi trovo gia nell'estremo sinistro della griglia
    if (y>1) {
        cell c(x, y);
        //controllo se esiste una cella nella posizione cercata
        if (list.ricercaElemento(c)) {
            //cerco la posizione nella lista
            Linked_list<cell>::posizione p=list.primoLista();
            while (list.leggiLista(p)!=c)
            {
                p=list.succLista(p);
            }
            //controllo se gia esiste una cella in posizione (x,y-1). Se esiste allora cancello la cella in posizione p,
            // altrimenti sovrascrivo la cella in posizione p con le nuove coordinate
            y=y-1;
            c.setY(y);
            if (!list.ricercaElemento(c)) {
                list.scriviLista(c,p);
            }
            else
                list.cancLista(p);
        }
    }
}
// sposta a destra di una posizione la cella viva presente in posizione (x,y)
void grid::moveRight(int x, int y)
{
    //ragionamento analogo a quello del movimento a sinistra
    if (y<m) {
        cell c(x, y);
        //controllo se esiste una cella nella posizione cercata
        if (list.ricercaElemento(c)) {
            //cerco la posizione nella lista
            Linked_list<cell>::posizione p=list.primoLista();
            while (list.leggiLista(p)!=c)
            {
                p=list.succLista(p);
            }
            //controllo se gia esiste una cella in posizione (x,y+1). Se esiste allora cancello la cella in posizione p,
            // altrimenti sovrascrivo la cella in posizione p con le nuove coordinate
            y=y+1;
            c.setY(y);
            if (!list.ricercaElemento(c)) {
                list.scriviLista(c,p);
            }
            else
                list.cancLista(p);
        }
    }
}
// sposta in alto di una posizione la cella viva presente in posizione (x,y)
void grid::moveUpper(int x, int y)
{
    if (x>1) {
        cell c(x, y);
        //controllo se esiste una cella nella posizione cercata
        if (list.ricercaElemento(c)) {
            //cerco la posizione nella lista
            Linked_list<cell>::posizione p=list.primoLista();
            while (list.leggiLista(p)!=c)
            {
                p=list.succLista(p);
            }
            //controllo se gia esiste una cella in posizione (x-1,y1). Se esiste allora cancello la cella in posizione p,
            // altrimenti sovrascrivo la cella in posizione p con le nuove coordinate
            x=x-1;
            c.setX(x);
            if (!list.ricercaElemento(c)) {
                list.scriviLista(c,p);
            }
            else
                list.cancLista(p);
        }
    }
}
// sposta in basso di una posizione la cella viva presente in posizione (x,y)
void grid::moveDown(int x, int y)
{
    if (x<n) {
        cell c(x, y);
        //controllo se esiste una cella nella posizione cercata
        if (list.ricercaElemento(c)) {
            //cerco la posizione nella lista
            Linked_list<cell>::posizione p=list.primoLista();
            while (list.leggiLista(p)!=c)
            {
                p=list.succLista(p);
            }
            //controllo se gia esiste una cella in posizione (x+1,y1). Se esiste allora cancello la cella in posizione p,
            // altrimenti sovrascrivo la cella in posizione p con le nuove coordinate
            x=x+1;
            c.setX(x);
            if (!list.ricercaElemento(c)) {
                list.scriviLista(c,p);
            }
            else
            {
                list.cancLista(p);
        }
    }
}}

// stabilisce se la cella viva presente in posizione (x,y) `e circondata,
// ovvero tutte le celle vicine alla cella data sono vive
bool grid::surrounded(int x, int y)
{
    //check indica le celle da controllare per la verifica del surrounded, count indica da quante celle si è circondati
    int check=4,count=0;
    //se mi trovo in prima riga non devo controllare in alto, se mi trovo in ultima riga non devo controllare in basso
    if (x==1 || x==n) check--;
    //se mi trovo in prima colonna non devo controllare a sinisra, se mi trovo in ultima colonna non devo controllare a destra
    if (y==1 || y==m) check--;
    //controllo in alto, se possibile
    cell c(x,y);
    int tmpx,tmpy;
    if (x>1)
    {
        tmpx=x-1;
        c.setX(tmpx);
        c.setY(y);
        if (list.ricercaElemento(c))
        {
            count++;
        }
    }
    //controllo in basso, se possibile
    if (x<n)
    {
        tmpx=x+1;
        c.setX(tmpx);
        c.setY(y);
        if (list.ricercaElemento(c))
        {
            count++;
        }
    }
    //controllo a sinistra, se possibile
    if (y>1)
    {
        c.setX(x);
        tmpy=y-1;
        c.setY(tmpy);
        if (list.ricercaElemento(c))  {
            count++;
        }
    }
    //controllo a destra, se possibile
    if (y<n)
    {
        c.setX(x);
        tmpy=y+1;
        c.setY(tmpy);
        if (list.ricercaElemento(c))  {
            count++;
        }
    }
    return (check==count);
}
// rimuove dalla griglia tutte le celle circondate
void grid::removeSurrounded()
{
    Linked_list<cell>::posizione p=list.primoLista();
    cell c;
    while (!list.fineLista(p))
    {
        c=list.leggiLista(p);
        if (surrounded(c.getX(),c.getY()))
        {
            list.cancLista(p);
            //Se lista a puntatori
            //p=list.succLista(p);
        }

        else
        {
            p=list.succLista(p);
            if(!list.fineLista(p))
            {
                c=list.leggiLista(p);
            }
        }
    }
}


void grid::stampa()
{
    cout<<list;
}

grid::~grid() {
}

#endif //REALIZZAZIONI_GRID_H