#include "trit.h"


namespace custom {
    size_t round_up(size_t x, size_t y) {
        return x / y + ((x % y != 0) ? 1 : 0);
    }

    Tritset::Tritset(size_t size) {
        this->size = round_up(size * 2, 8 * sizeof(uint));
        data = new uint [this->size];
        assert(data);
    }

    Tritset::~Tritset() {
        delete [] data;
    }

    size_t Tritset::capacity() const {
        return size * sizeof(uint) * 8 / 2;
    }

    void Tritset::clear_trit(size_t index, size_t pos) {
        uint cleaner = ~(3 << pos);
        data[index] &= cleaner;
    }

    void Tritset::set_trit(size_t index, size_t pos, size_t value) {
        clear_trit(index, pos);
        data[index] = value << pos;
    }
}


