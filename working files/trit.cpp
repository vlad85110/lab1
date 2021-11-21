#include "trit.h"


namespace custom {
    size_t round_up(size_t x, size_t y) {
        return x / y + ((x % y != 0) ? 1 : 0);
    }

   void print_trit (Trit val){
       switch (val) {
           case 0: {
               std::cout << "unknown" << std::endl;
               break;
           }
           case 1: {
               std::cout << "true" << std::endl;
               break;
           }
           case 2: {
               std::cout << "false" << std::endl;
               break;
           }
       }
    }
}


