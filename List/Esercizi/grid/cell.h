#ifndef REALIZZAZIONI_CELL_H
#define REALIZZAZIONI_CELL_H

#include <ostream>

using namespace std;

class cell {
private:
    int x;
    int y;
public:
    cell() = default;

    cell(int x, int y) : x(x), y(y) {}

    int getX() const {
        return x;
    }

    void setX(int x) {
        this->x = x;
    }

    int getY() const {
        return y;
    }

    bool operator==(const cell &c) {
        return ((c.x == this->x) && (c.y == this->y));
    }

    bool operator!=(const cell &c) {
        return !(this->operator==(c));
    }

    void setY(int y) {
        this->y = y;
    }

    void setCell(int x, int y) {
        this->x = x;
        this->y = y;
    }

    friend ostream &operator<<(ostream &os, const cell &c) {
        os << "(" << c.x << "," << c.y << ") ";
        return os;
    }

    cell &operator=(const cell &c) {
        if (this != &c) {
            this->x = c.x;
            this->y = c.y;
        }
        return *this;
    }
};


#endif //REALIZZAZIONI_CELL_H
