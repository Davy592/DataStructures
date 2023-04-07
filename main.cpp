#include "List/Linked_list.h"
#include "Enary Tree/AlberoPt.h"
#include "Stack/pilapt.h"
//#include "alberoBinario_pt.h"
#include "Queue/codap.h"
#include "Queue/Esercizi/Bins.h"
//#include "util_bin_tree.cpp"
#include "Graph/grafoMatrice.h"
#include "Graph/Esercizi/graphCounting.h"
#include "Graph/Esercizi/graphPath.h"
#include "Dictionary/hashtableAperto.h"
//#include "graphColor.h"
#include <iostream>

using namespace std;

template<class T>
int freq(const Linked_list<T> &L, int k) {
    int cnt=0;
    typename Linked_list<T>::posizione p=L.primoLista();
    while(!L.fineLista(p)){
        if(L.leggiLista(p)%k==0) cnt++;
        p=L.succLista(p);
    }
    return cnt;
}

template<class T>
void hist(const Linked_list<T> &L) {
    open_hash_table<int, int> cnt;
    mypair<int, int> mp;
    typename Linked_list<T>::posizione p=L.primoLista();
    while(!L.fineLista(p)){
        mp.setChiave(L.leggiLista(p));
        if(!cnt.ricerca(L.leggiLista(p))){
            mp.setValore(1);
            cnt.inserisci(mp);
        }else{
            typename open_hash_table<int, int>::valore v;
            v=cnt.recupera(L.leggiLista(p));
            mp.setValore(v+1);
            cnt.cancella(L.leggiLista(p));
            cnt.inserisci(mp);
        }
        p=L.succLista(p);
    }
    p=L.primoLista();
    while(!L.fineLista(p)){
        if(cnt.ricerca(L.leggiLista(p))){
            cout<<L.leggiLista(p)<<" e' presente "<<cnt.recupera(L.leggiLista(p))<<" volte nella lista"<<endl;
            cnt.cancella(L.leggiLista(p));
        }
        p=L.succLista(p);
    }
}

template<class T>
void remp(Linked_list<T> &L) {
    typename Linked_list<T>::posizione p=L.primoLista(), tmp;
    while(!L.fineLista(L.succLista(p))){
        tmp=L.succLista(p);
        if(L.leggiLista(tmp)%2==0){
            L.cancLista(p);
            p=tmp;
        }else p=L.succLista(p);
    }
}

/*template<class T>
int max_level(alberoPt<T> &A) {
    int somme[100], ma=INT_MIN, ret;
    fill(somme, somme+100, 0);
    A.sommaLivello(A.radice(), 0, somme);
    for(int i=0;i<100;i++){
        if(somme[i]>ma){
            ma=somme[i];
            ret=i;
        }
    }
    return ret;
}*/

/*void sommaLivello(alberoPt<int> &A, typename alberoPt<int>::nodo n, open_hash_table<int, int> &cnt, int liv) {
    if (cnt.ricerca(liv)) {
        cnt.modifica(liv, cnt.recupera(liv) + A.leggiNodo(n));
    }else {
        mypair<int, int> mp(liv, A.leggiNodo(n));
        cnt.inserisci(mp);
    }
    if(!A.foglia(n)) sommaLivello(A, A.primoFiglio(n), cnt, liv+1);
    if(!A.ultimoFratello(n)) sommaLivello(A, A.fratelloSuccessivo(n), cnt, liv);
}

template<class T>
int max_level(alberoPt<T> &A) {
    int ma, ret, liv;
    open_hash_table<int, int> cnt;
    if(!A.alberoVuoto()){
        sommaLivello(A, A.radice(), cnt, 0);
        ma=cnt.recupera(0);
        ret=0;
        cnt.cancella(0);
        liv=1;
        while(!cnt.dizionarioVuoto()) {
            if(cnt.recupera(liv)>ma){
                ma=cnt.recupera(liv);
                ret=liv;
            }
            cnt.cancella(liv);
            liv++;
        }
        return ret;
    }
    throw std::out_of_range("L'albero e' vuoto");
}*/

/*int main() {
    Linked_list<int> L;
    L.inserisciCoda(5);
    L.inserisciCoda(6);
    L.inserisciCoda(4);
    L.inserisciCoda(4);
    L.inserisciCoda(4);
    L.inserisciCoda(5);
    L.inserisciCoda(6);
    L.inserisciCoda(1);
    L.inserisciCoda(2);
    L.inserisciCoda(3);
    L.inserisciCoda(1);
    L.inserisciCoda(6);
    L.inserisciCoda(10);
    cout<<L;
    cout<<freq(L, 2)<<endl;
    hist(L);
    remp(L);
    cout<<L;
    alberoPt<int> A;
    A.inserisciRadice(5);
    A.inserisciPrimoFiglio(A.radice(), 10);
    A.inserisciPrimoFiglio(A.radice(), 20);
    A.inserisciPrimoFiglio(A.radice(), 5);
    A.inserisciPrimoFiglio(A.radice(), 15);
    cout<<max_level(A);
    return 0;
}*/

template<class T>
pilapt<T> reverse_pila(pilapt<T> &s){
    pilapt<T> reversed, tmp;
    while(!s.pilaVuota()){
        reversed.insPila(s.leggiPila());
        tmp.insPila(s.leggiPila());
        s.fuoriPila();
    }
    while(!tmp.pilaVuota()){
        s.insPila(tmp.leggiPila());
        tmp.fuoriPila();
    }
    return reversed;
}

/*int multipli(alberoBinario_pt<int> &A, typename alberoBinario_pt<int>::nodo n){
    int ret=A.leggiNodo(n)%2==0;
    if(A.sinistroVuoto(n) && A.destroVuoto(n)){
        A.scriviNodo(n, ret);
        return ret;
    }else{
        int pari=0;
        if(!A.sinistroVuoto(n)) pari+=multipli(A, A.figlioSinistro(n));
        if(!A.destroVuoto(n)) pari+=multipli(A, A.figlioDestro(n));
        A.scriviNodo(n, pari+ret);
        return pari+ret;
    }
}*/

/*void multipli(alberoBinario_pt<int> &A){
    if(!A.alberoBinVuoto()) multipli(A, A.radice());
    else throw std::out_of_range("Albero vuoto");
}*/

/*int main() {
    pilapt<int> s;
    alberoBinario_pt<int> A;
    s.insPila(5);
    s.insPila(6);
    s.insPila(7);
    s.insPila(9);
    s.insPila(10);
    s.insPila(2);
    s.insPila(3);
    s.insPila(1);
    s.insPila(4);
    s.insPila(5);
    cout<<s<<reverse_pila(s);
    A.inserisciRadice(5);
    A.inserisciSinistro(A.radice(), 5);
    A.inserisciDestro(A.radice(), 6);
    A.inserisciSinistro(A.figlioSinistro(A.radice()), 10);
    A.inserisciDestro(A.figlioSinistro(A.radice()), 19);
    A.inserisciSinistro(A.figlioDestro(A.radice()), 20);
    A.inserisciDestro(A.figlioDestro(A.radice()), 63);
    cout<<A;
    multipli(A);
    cout<<A;
    return 0;
}*/

/*/////////////////////////////////////////////////////////////////*/

/*int main(){
    Bins b;
    b.insert(1);
    b.insert(2);
    b.insert(3);
    b.insert(3);
    b.insert(2);
    b.insert(4);
    b.insert(4);
    b.insert(5);
    b.insert(6);
    b.insert(7);
    b.insert(8);
    b.insert(8);
    b.insert(9);
    b.insert(9);
    b.insert(9);
    cout<<"Le lunghezze sono: "<<b.freq(0)<<" - "<<b.freq(1)<<" - "<<b.freq(2)<<endl;
    cout<<"Le medie sono: "<<b.mean(0)<<" - "<<b.mean(1)<<" - "<<b.mean(2)<<endl;
    b.canc(0);
    b.canc(0);
    b.canc(1);
    b.canc(2);
    b.canc(2);
    b.canc(2);
    cout<<"Le lunghezze sono: "<<b.freq(0)<<" - "<<b.freq(1)<<" - "<<b.freq(2)<<endl;
    cout<<"Le medie sono: "<<b.mean(0)<<" - "<<b.mean(1)<<" - "<<b.mean(2)<<endl;
    return 0;
}*/

/*int main(){
    alberoBinario_pt<int> A;
    A.inserisciRadice(5);
    A.inserisciSinistro(A.radice(), 5);
    A.inserisciDestro(A.radice(), 5);
    A.inserisciSinistro(A.figlioSinistro(A.radice()), 10);
    A.inserisciDestro(A.figlioSinistro(A.radice()), 19);
    A.inserisciSinistro(A.figlioDestro(A.radice()), 20);
    A.inserisciDestro(A.figlioDestro(A.radice()), 62);
    cout<<A;
    cout<<odd(A, 0)<<" "<<odd(A, 1)<<" "<<odd(A, 2)<<" "<<odd(A, 3)<<endl;
    cout<<even_leafs(A)<<" "<<leaves_with_even_parent(A)<<endl;
    return 0;
}*/

/*int main(){
    alberoBinario_pt<int> A;
    A.inserisciRadice(5);
    A.inserisciSinistro(A.radice(), 5);
    A.inserisciDestro(A.radice(), 5);
    A.inserisciSinistro(A.figlioSinistro(A.radice()), 10);
    A.inserisciDestro(A.figlioSinistro(A.radice()), 19);
    A.inserisciSinistro(A.figlioDestro(A.radice()), 20);
    A.inserisciDestro(A.figlioDestro(A.radice()), 62);
    cout<<A;
    cout<<d3(A, 0)<<" "<<d3(A, 1)<<" "<<d3(A, 2)<<" "<<d3(A, 3)<<endl;
    cout<<lp(A)<<" "<<l2p(A)<<endl;
    return 0;
}*/

/*int main(){
    alberoBinario_pt<int> A;
    A.inserisciRadice(5);
    A.inserisciSinistro(A.radice(), 5);
    A.inserisciDestro(A.radice(), 5);
    A.inserisciSinistro(A.figlioSinistro(A.radice()), 10);
    A.inserisciDestro(A.figlioSinistro(A.radice()), 19);
    A.inserisciSinistro(A.figlioDestro(A.radice()), 20);
    A.inserisciDestro(A.figlioDestro(A.radice()), 62);
    cout<<A;
    cout<<d3(A, 0)<<" "<<d3(A, 1)<<" "<<d3(A, 2)<<" "<<d3(A, 3)<<endl;
    cout<<lp(A)<<" "<<l2p(A)<<endl;
    return 0;
}*/

/*int main(){
    graphColor G;
    grafoMat<string, int>::nodo n1, n2, n3, n4, n5, n6, n7, n8, n9, n10;
    G.insNodo(n1);
    G.insNodo(n2);
    G.insNodo(n3);
    G.insNodo(n4);
    G.insNodo(n5);
    G.insNodo(n6);
    G.insNodo(n7);
    G.insNodo(n8);
    G.insNodo(n9);
    G.insNodo(n10);
    G.scriviEtichetta(n1, "rosso");
    G.scriviEtichetta(n2, "rosso");
    G.scriviEtichetta(n3, "rosso");
    G.scriviEtichetta(n4, "rosso");
    G.scriviEtichetta(n5, "rosso");
    G.scriviEtichetta(n6, "rosso");
    G.scriviEtichetta(n7, "rosso");
    G.scriviEtichetta(n8, "rosso");
    G.scriviEtichetta(n9, "rosso");
    G.scriviEtichetta(n10, "rosso");
    G.insArco(n1, n2, 0);
    G.insArco(n2, n1, 0);
    G.insArco(n1, n4, 0);
    G.insArco(n4, n1, 0);
    G.insArco(n2, n3, 0);
    G.insArco(n3, n2, 0);
    G.insArco(n3, n6, 0);
    G.insArco(n6, n3, 0);
    G.insArco(n4, n5, 0);
    G.insArco(n5, n4, 0);
    G.insArco(n5, n6, 0);
    G.insArco(n6, n5, 0);
    G.insArco(n3, n7, 0);
    G.insArco(n7, n3, 0);
    G.insArco(n7, n8, 0);
    G.insArco(n8, n7, 0);
    G.insArco(n7, n9, 0);
    G.insArco(n9, n7, 0);
    G.insArco(n8, n10, 0);
    G.insArco(n10, n8, 0);
    G.insArco(n9, n10, 0);
    G.insArco(n10, n9, 0);
    cout<<G.sameColorPath(n1, n10)<<" "<<G.uniformColorPath(n1, n10)<<endl;
    return 0;
}*/

int subsum(alberoPt<int> &T, alberoPt<int>::nodo n){
    if(T.foglia(n)) return T.leggiNodo(n);
    int figli=0;
    alberoPt<int>::nodo cur=T.primoFiglio(n);
    while(!T.ultimoFratello(cur)){
        figli+=subsum(T, cur);
        cur=T.fratelloSuccessivo(cur);
    }
    figli+=subsum(T, cur);
    T.scriviNodo(n, figli+T.leggiNodo(n));
    return T.leggiNodo(n);
}

void subsum(alberoPt<int> &T){
    if(!T.alberoVuoto()) subsum(T, T.radice());
    else throw out_of_range("ALBERO VUOTO");
}

/*int main(){
    alberoPt<int> T;
    T.inserisciRadice(10);
    T.inserisciPrimoFiglio(T.radice(), 5);
    T.inserisciPrimoFiglio(T.radice(), 6);
    T.inserisciPrimoFiglio(T.radice(), 8);
    T.inserisciPrimoFiglio(T.primoFiglio(T.radice()), 3);
    T.inserisciPrimoFiglio(T.fratelloSuccessivo(T.primoFiglio(T.radice())), 5);
    T.inserisciPrimoFiglio(T.fratelloSuccessivo(T.primoFiglio(T.radice())), 9);
    T.inserisciPrimoFiglio(T.fratelloSuccessivo(T.fratelloSuccessivo(T.primoFiglio(T.radice()))), 6);
    T.inserisciPrimoFiglio(T.fratelloSuccessivo(T.fratelloSuccessivo(T.primoFiglio(T.radice()))), 3);
    T.inserisciPrimoFiglio(T.fratelloSuccessivo(T.fratelloSuccessivo(T.primoFiglio(T.radice()))), 1);
    subsum(T);
    cout<<T.leggiNodo(T.radice())<<" "<<T.leggiNodo(T.primoFiglio(T.radice()));
    return 0;
}*/

template<class T>
int numero_cammini(grafoMat<T, int> &G, typename grafoMat<T, int>::nodo n, typename grafoMat<T, int>::nodo fine, bool visitato[], int lung, vector<int> &vet){
    if(n.getId()==fine.getId()){
        vet.push_back(lung);
        return 1;
    }
    int ret=0;
    typename grafoMat<T, int>::listaNodi nodiAdiacenti = G.adiacenti(n);
    typename grafoMat<T, int>::posizioneListaNodi p;
    typename grafoMat<T, int>::nodo v;
    visitato[n.getId()] = true;
    if (!nodiAdiacenti.listaVuota()) {
        p = nodiAdiacenti.primoLista();
        while (!nodiAdiacenti.fineLista(p)) {
            v = nodiAdiacenti.leggiLista(p);
            if (!visitato[v.getId()] && G.leggiPeso(n, v)==1) {
                ret += numero_cammini(G, v, fine, visitato, lung+1, vet);
                visitato[v.getId()] = false;
            }
            p = nodiAdiacenti.succLista(p);
        }
    }
    return ret;
}

template<class T>
int numero_cammini(grafoMat<T, int> &G, typename grafoMat<T, int>::nodo a, typename grafoMat<T, int>::nodo b){
    if(!G.vuoto()){
        bool visitato[G.numNodi()];
        fill(visitato, visitato+G.numNodi(), false);
        vector<int> vet;
        return numero_cammini(G, a, b, visitato, 0, vet);
    }else throw out_of_range("GRAFO VUOTO");
}

template<class T>
double media_cammini(grafoMat<T, int> &G, typename grafoMat<T, int>::nodo a, typename grafoMat<T, int>::nodo b){
    if(!G.vuoto()){
        double cnt=0;
        bool visitato[G.numNodi()];
        vector<int> vet;
        fill(visitato, visitato+G.numNodi(), false);
        numero_cammini(G, a, b, visitato, 0, vet);
        for(int i=0;i<vet.size();i++){
            cnt+=vet[i];
        }
        return cnt/numero_cammini(G, a, b, visitato, 0, vet);
    }else throw out_of_range("GRAFO VUOTO");
}

/*int main(){
    grafoMat<int, int> G;
    grafoMat<string, int>::nodo n[11];
    for(int i=0;i<11;i++){
        G.insNodo(n[i]);
        G.scriviEtichetta(n[i], i);
    }
    G.insArco(n[1], n[2], 1);
    G.insArco(n[2], n[1], 1);
    G.insArco(n[1], n[4], 1);
    G.insArco(n[4], n[1], 1);
    G.insArco(n[2], n[3], 1);
    G.insArco(n[3], n[2], 1);
    G.insArco(n[3], n[6], 1);
    G.insArco(n[6], n[3], 1);
    G.insArco(n[4], n[5], 1);
    G.insArco(n[5], n[4], 1);
    G.insArco(n[5], n[6], 1);
    G.insArco(n[6], n[5], 1);
    G.insArco(n[3], n[7], 1);
    G.insArco(n[7], n[3], 1);
    G.insArco(n[7], n[8], 1);
    G.insArco(n[8], n[7], 1);
    G.insArco(n[7], n[9], 1);
    G.insArco(n[9], n[7], 1);
    G.insArco(n[8], n[10], 1);
    G.insArco(n[10], n[8], 1);
    G.insArco(n[9], n[10], 1);
    G.insArco(n[10], n[9], 1);
    cout<<numero_cammini(G, n[1], n[10])<<" "<<media_cammini(G, n[1], n[10]);
    return 0;
}*/

void elimina(pilapt<int> &p, int k){
    pilapt<int> tmp;
    while(!p.pilaVuota()){
        if(p.leggiPila()<=k) tmp.insPila(p.leggiPila());
        p.fuoriPila();
    }
    while(!tmp.pilaVuota()){
        p.insPila(tmp.leggiPila());
        tmp.fuoriPila();
    }
}

/*int main(){
    pilapt<int> p;
    p.insPila(5);
    p.insPila(7);
    p.insPila(1);
    p.insPila(2);
    p.insPila(9);
    p.insPila(8);
    p.insPila(3);
    p.insPila(4);
    cout<<p;
    elimina(p, 5);
    cout<<p;
    elimina(p, 3);
    cout<<p;
    return 0;
}*/

int pp(alberoPt<int> &T, alberoPt<int>::nodo n){
    if(T.foglia(n)) return T.leggiNodo(T.padre(n))%2==0;
    int figli=0;
    alberoPt<int>::nodo cur=T.primoFiglio(n);
    while(!T.ultimoFratello(cur)){
        figli+=pp(T, cur);
        cur=T.fratelloSuccessivo(cur);
    }
    figli+=pp(T, cur);
    return figli+(n!=T.radice()?T.leggiNodo(T.padre(n))%2==0:0);
}

int pp(alberoPt<int> &T){
    if(!T.alberoVuoto()) return pp(T, T.radice());
    else throw out_of_range("ALBERO VUOTO");
}

/*int main(){
    alberoPt<int> T;
    T.inserisciRadice(10);
    T.inserisciPrimoFiglio(T.radice(), 5);
    T.inserisciPrimoFiglio(T.radice(), 6);
    T.inserisciPrimoFiglio(T.radice(), 8);
    T.inserisciPrimoFiglio(T.primoFiglio(T.radice()), 3);
    T.inserisciPrimoFiglio(T.fratelloSuccessivo(T.primoFiglio(T.radice())), 5);
    T.inserisciPrimoFiglio(T.fratelloSuccessivo(T.primoFiglio(T.radice())), 9);
    T.inserisciPrimoFiglio(T.fratelloSuccessivo(T.fratelloSuccessivo(T.primoFiglio(T.radice()))), 6);
    T.inserisciPrimoFiglio(T.fratelloSuccessivo(T.fratelloSuccessivo(T.primoFiglio(T.radice()))), 3);
    T.inserisciPrimoFiglio(T.fratelloSuccessivo(T.fratelloSuccessivo(T.primoFiglio(T.radice()))), 1);
    cout<<pp(T);
    return 0;
}*/

void elimina_multipli(Linked_list<int> &L){
    if(!L.listaVuota()){
        int ord=1;
        Linked_list<int>::posizione p=L.primoLista();
        while(!L.fineLista(p)){
            if(L.leggiLista(p)%ord==0) L.cancLista(p);
            else p=L.succLista(p);
            ord++;
        }
    }else throw out_of_range("LISTA VUOTA");
}

/*int main(){
    Linked_list<int> L;
    L.inserisciCoda(1);
    L.inserisciCoda(2);
    L.inserisciCoda(15);
    L.inserisciCoda(5);
    L.inserisciCoda(8);
    L.inserisciCoda(6);
    L.inserisciCoda(14);
    L.inserisciCoda(9);
    L.inserisciCoda(12);
    cout<<L;
    elimina_multipli(L);
    cout<<L;
    return 0;
}*/

/*int main(){
    int n;
    grafoMat<int, int> G;
    grafoMat<int, int>::nodo n1, n2, n3, n4, n5, n6, n7, n8, n9, n10;
    graphCounting g;
    G.insNodo(n1);
    G.insNodo(n2);
    G.insNodo(n3);
    G.insNodo(n4);
    G.insNodo(n5);
    G.insNodo(n6);
    G.insNodo(n7);
    G.insNodo(n8);
    G.insNodo(n9);
    G.insNodo(n10);
    n=1;
    G.scriviEtichetta(n1, n);
    n=8;
    G.scriviEtichetta(n2, n);
    n=3;
    G.scriviEtichetta(n3, n);
    n=5;
    G.scriviEtichetta(n4, n);
    n=2;
    G.scriviEtichetta(n5, n);
    n=5;
    G.scriviEtichetta(n6, n);
    n=6;
    G.scriviEtichetta(n7, n);
    n=1;
    G.scriviEtichetta(n8, n);
    n=7;
    G.scriviEtichetta(n9, n);
    n=1;
    G.scriviEtichetta(n10, n);
    G.insArco(n1, n2, 0);
    G.insArco(n2, n1, 0);
    G.insArco(n1, n4, 0);
    G.insArco(n4, n1, 0);
    G.insArco(n2, n3, 0);
    G.insArco(n3, n2, 0);
    G.insArco(n3, n6, 0);
    G.insArco(n6, n3, 0);
    G.insArco(n4, n5, 0);
    G.insArco(n5, n4, 0);
    G.insArco(n5, n6, 0);
    G.insArco(n6, n5, 0);
    G.insArco(n3, n7, 0);
    G.insArco(n7, n3, 0);
    G.insArco(n7, n8, 0);
    G.insArco(n8, n7, 0);
    G.insArco(n7, n9, 0);
    G.insArco(n9, n7, 0);
    G.insArco(n8, n10, 0);
    G.insArco(n10, n8, 0);
    G.insArco(n9, n10, 0);
    G.insArco(n10, n9, 0);
    cout<<g.countSame(G, n1)<<" "<<g.meanN2(G, n1);
    return 0;
}*/

int main(){
    int n;
    graph_path G;
    graph_path::nodo n1, n2, n3, n4, n5, n6, n7, n8, n9, n10;
    G.insNodo(n1);
    G.insNodo(n2);
    G.insNodo(n3);
    G.insNodo(n4);
    G.insNodo(n5);
    G.insNodo(n6);
    G.insNodo(n7);
    G.insNodo(n8);
    G.insNodo(n9);
    G.insNodo(n10);
    n=1;
    G.scriviEtichetta(n1, n);
    n=8;
    G.scriviEtichetta(n2, n);
    n=3;
    G.scriviEtichetta(n3, n);
    n=5;
    G.scriviEtichetta(n4, n);
    n=2;
    G.scriviEtichetta(n5, n);
    n=5;
    G.scriviEtichetta(n6, n);
    n=6;
    G.scriviEtichetta(n7, n);
    n=1;
    G.scriviEtichetta(n8, n);
    n=7;
    G.scriviEtichetta(n9, n);
    n=1;
    G.scriviEtichetta(n10, n);
    G.insArco(n1, n2, 0);
    G.insArco(n2, n1, 0);
    G.insArco(n1, n4, 0);
    G.insArco(n4, n1, 0);
    G.insArco(n2, n3, 0);
    G.insArco(n3, n2, 0);
    G.insArco(n3, n6, 0);
    G.insArco(n6, n3, 0);
    G.insArco(n4, n5, 0);
    G.insArco(n5, n4, 0);
    G.insArco(n5, n6, 0);
    G.insArco(n6, n5, 0);
    G.insArco(n3, n7, 0);
    G.insArco(n7, n3, 0);
    G.insArco(n7, n8, 0);
    G.insArco(n8, n7, 0);
    G.insArco(n7, n9, 0);
    G.insArco(n9, n7, 0);
    G.insArco(n8, n10, 0);
    G.insArco(n10, n8, 0);
    G.insArco(n9, n10, 0);
    G.insArco(n10, n9, 0);
    cout<<"Vedi: "<<G.sumPath(21, n1, n10);
    return 0;
}

int somma_sottoalbero(alberoPt<int> &T, alberoPt<int>::nodo n){
    if(T.foglia(n)) return T.leggiNodo(n);
    int figli=0;
    alberoPt<int>::nodo cur=T.primoFiglio(n);
    while(!T.ultimoFratello(cur)){
        figli+=somma_sottoalbero(T, cur);
        cur=T.fratelloSuccessivo(cur);
    }
    figli+=somma_sottoalbero(T, cur);
    return figli+T.leggiNodo(n);
}

int sottoalberi_con_somma(alberoPt<int> &T, alberoPt<int>::nodo n, int k){
    if(T.foglia(n)) {
        /*if (n != T.radice())*/ return (T.leggiNodo(n) == k);
        /*else return 0;*/
    }
    int figli=0;
    alberoPt<int>::nodo cur=T.primoFiglio(n);
    while(!T.ultimoFratello(cur)){
        figli+=(somma_sottoalbero(T, cur)==k);
        cur=T.fratelloSuccessivo(cur);
    }
    figli+=(somma_sottoalbero(T, cur)==k);
    return figli+(somma_sottoalbero(T, n)==k);
}

int sottoalberi_con_somma(alberoPt<int> &T, int k){
    if(!T.alberoVuoto()) return sottoalberi_con_somma(T, T.radice(), k);
    else throw out_of_range("ALBERO VUOTO");
}

/*int main(){
    alberoPt<int> T;
    T.inserisciRadice(0);
    T.inserisciPrimoFiglio(T.radice(), 2);
    T.inserisciPrimoFiglio(T.radice(), -6);
    T.inserisciPrimoFiglio(T.primoFiglio(T.radice()), 11);
    T.inserisciPrimoFiglio(T.fratelloSuccessivo(T.primoFiglio(T.radice())), 7);
    T.inserisciPrimoFiglio(T.fratelloSuccessivo(T.primoFiglio(T.radice())), -4);
    cout<<"Ci sono "<<sottoalberi_con_somma(T, 5)<<" sottoalberi con somma 5"<<endl;
    return 0;
}*/