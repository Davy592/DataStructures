#ifndef REALIZZAZIONI_MULTIPLESTACK_H
#define REALIZZAZIONI_MULTIPLESTACK_H

#include "pilav.h"
#include <stdexcept>
#include <vector>

template<class T>
class MultipleStack {
public:
    typedef T tipoelem;
    MultipleStack(unsigned int);
    int PushS(tipoelem &, unsigned int);
    tipoelem &PopS(unsigned int);

    //funzione di prova
    void printMultipleStack();

private:
    unsigned int numStack;
    pilav<T> *stacks;
    vector<pilav<T>> vet;
};

template<class T>
MultipleStack<T>::MultipleStack(unsigned int num) {
    if (num >= 1) {
        numStack = num;
        for (int i = 0; i < numStack; i++) {
            vet.push_back(pilav<T>());
        }
    } else throw std::out_of_range("Numero non valido");
}

template<class T>
int MultipleStack<T>::PushS(MultipleStack::tipoelem &el, unsigned int n) {
    if (n >= 1 && n <= numStack) {
        //stacks[n-1].insPila(el);
        vet[n - 1].insPila(el);

    } else throw std::out_of_range("Numero non valido");

}

template<class T>
typename MultipleStack<T>::tipoelem &MultipleStack<T>::PopS(unsigned int n) {
    if (n >= 1 && n <= numStack) {
        // stacks[n-1].fuoriPila();
        vet[n - 1].fuoriPila();
    } else throw std::out_of_range("Numero non valido");
}

template<class T>
void MultipleStack<T>::printMultipleStack() {
    for (int i = 0; i < numStack; i++) {
        cout << "STACK NUMERO " << (i + 1) << ": " << vet[i];
    }
}


#endif //REALIZZAZIONI_MULTIPLESTACK_H
