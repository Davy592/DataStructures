#ifndef REALIZZAZIONI_PRODOTTO_H
#define REALIZZAZIONI_PRODOTTO_H

#include <string>
#include <ostream>

using namespace std;

class prodotto {
public:
    prodotto(double, string);
    prodotto() = default;
    ~prodotto() = default;

    double getPrezzo() const;

    void setPrezzo(double prezzo);

    const string &getNome() const;

    void setNome(const string &nome);

    bool operator==(const prodotto &p) {
        return ((p.prezzo == this->prezzo) && (p.nome == this->nome));
    }

    bool operator!=(const prodotto &p) {
        return !(this->operator==(p));
    }

    prodotto &operator=(const prodotto &p) {
        if (this != &p) {
            this->prezzo = p.prezzo;
            this->nome = p.nome;
        }
        return *this;
    }


    friend ostream &operator<<(ostream &os, const prodotto &p) {
        os << "(" << p.nome << ":" << p.prezzo << ") ";
        return os;
    }

private:
    double prezzo;
    string nome;
};

double prodotto::getPrezzo() const {
    return prezzo;
}

void prodotto::setPrezzo(double prezzo) {
    prodotto::prezzo = prezzo;
}

const string &prodotto::getNome() const {
    return nome;
}

void prodotto::setNome(const string &nome) {
    prodotto::nome = nome;
}

prodotto::prodotto(double p, string s) : prezzo(p), nome(s) {

}

#endif //REALIZZAZIONI_PRODOTTO_H
