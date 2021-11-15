#include "trit.h"


namespace custom {
    Tritset::Tritset(size_t size) {
        this->size = size;
        data = new uint [size];
        assert(size >= 1000 * 2 / 8 / sizeof(uint));
        assert(data);
    }

    Tritset::~Tritset() {
        delete [] data;
    }

    size_t Tritset::capacity() const {
        return size;
    }

}


