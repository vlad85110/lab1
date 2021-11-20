#include "trit.h"


namespace custom {
    Tritset::Tritset(size_t size) {
        this->size = round_up(size * 2, 8 * sizeof(uint));
        data = new uint [this->size];
        assert(data);
    }

    Tritset::~Tritset() {
        delete [] data;
    }

    size_t Tritset::capacity() const {
        return size;
    }

    size_t round_up(size_t x, size_t y)
    {
         return x / y + ((x % y != 0) ? 1 : 0);
    }


}


