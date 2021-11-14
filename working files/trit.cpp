#include "trit.h"


namespace custom {
    Tritset::Tritset(size_t length) {
        this->length = length;
        data = new uint [length];
        assert(length >= 1000 * 2 / 8 / sizeof(uint));
        assert(data);
    }

    Tritset::~Tritset() {
        delete [] data;
    }

    size_t Tritset::capacity() {
        return length;
    }

    uint Tritset::operator[](int index) {
        return data[index];
    }

}