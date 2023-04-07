#ifndef REALIZZAZIONI_REVERSESTACK_H
#define REALIZZAZIONI_REVERSESTACK_H

#include "../pilav.h"

template<class T>
class reverseStack {
public:
    pilav<T> reverse(pilav<T> &);
};

template<class T>
pilav<T> reverseStack<T>::reverse(pilav<T> &p) {
    pilav<T> p2;
    while (!p.pilaVuota()) {
        p2.insPila(p.leggiPila());
        p.fuoriPila();
    }
    return p2;
}

#endif //REALIZZAZIONI_REVERSESTACK_H
