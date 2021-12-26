#include "func.h"
#include "trit.h"


namespace custom {
    size_t round_up(size_t x, size_t y) {
        return x / y + ((x % y != 0) ? 1 : 0);
    }

    size_t _trit(size_t val) {
        return val * sizeof(uint) * 8 / 2;
    }

    size_t _uint(size_t val) {
        return val * 2 / 8 / sizeof(uint);
    }

    void print_trit (Trit val) {
       switch (val) {
           case 0: {
               std::cout << "unknown ";
               break;
           }
           case 1: {
               std::cout << "true ";
               break;
           }
           case 2: {
               std::cout << "false ";
               break;
           }
       }
    }

    size_t dec(size_t val) {
        if (val == 10)
            return 2;

        if (val == 11)
            return 3;

        return 0;
    }

    uint _and(uint x, uint y) {
        if (x == dec(10) || y == dec(10))
            return dec(10);

        if (x == 0 || y == 0)
            return 0;

        return 1;
    }

    uint _or(uint x, uint y) {
        if (x == 1 || y == 1)
            return 1;
        if (x == 0 || y == 0)
            return 0;

        return dec(10);
    }

    uint _not(uint x) {
        if (x == 1)
            return 2;

        if (x == 2)
            return 1;

        return 0;
    }

    size_t max(size_t x, size_t y) {
        return ((x > y) ? x : y);
    }
}


