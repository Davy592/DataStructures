#ifndef REALIZZAZIONI_BINS_H
#define REALIZZAZIONI_BINS_H

#include "../codap.h"

class Bins {
public:
    void insert(int k);
    void canc(int c);
    double mean(int c);
    int freq(int c);
private:
    codap<int> bin[3];
};

void Bins::insert(int k) {
    if (k >= 1) {
        if (k <= 3) bin[0].incoda(k);
        else if (k <= 6) bin[1].incoda(k);
        else if (k <= 9) bin[2].incoda(k);
        else throw std::out_of_range("Numero troppo grande, e' possibile inserire solo numeri 1<=x<=9");
    } else throw std::out_of_range("Numero troppo piccolo, e' possibile inserire solo numeri 1<=x<=9");
}

void Bins::canc(int c) {
    bin[c].fuoriCoda();
}

double Bins::mean(int c) {
    double sum = 0, cnt = 0;
    codap<int> tmp;
    while (!bin[c].codavuota()) {
        tmp.incoda(bin[c].leggiCoda());
        sum += bin[c].leggiCoda();
        cnt++;
        bin[c].fuoriCoda();
    }
    while (!tmp.codavuota()) {
        bin[c].incoda(tmp.leggiCoda());
        tmp.fuoriCoda();
    }
    return sum / cnt;
}

int Bins::freq(int c) {
    return bin[c].lunghezza();
}

#endif //REALIZZAZIONI_BINS_H
