#include "func.h"
#include "trit.h"


namespace custom {
    size_t round_up(size_t x, size_t y) {
        return x / y + ((x % y != 0) ? 1 : 0);
    }

    size_t uint_to_trit(size_t val) {
        return val * sizeof(uint) * 8 / 2;
    }

    size_t trit_to_uint(size_t val) {
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
}


