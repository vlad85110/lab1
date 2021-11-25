#include "func.h"
#include "trit.h"
#include <cmath>


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
               std::cout << "unknown ";//<< std::endl;
               break;
           }
           case 1: {
               std::cout << "true "; //<< std::endl;
               break;
           }
           case 2: {
               std::cout << "false "; //<< std::endl;
               break;
           }
       }
    }

    size_t dec(size_t val) {
        uint new_val = 0;
        for (int i = 0; val > 0; ++i) {
            new_val += (uint)((double)(val % 10) * pow(2,i));
            val /= 10;
        }
        return new_val;
    }
}


