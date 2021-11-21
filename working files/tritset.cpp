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
        return size * sizeof(uint) * 8 / 2;
    }

    void Tritset::clear_trit(size_t index, size_t shift) {
        uint cleaner = ~(3 << shift);
        data[index] &= cleaner;
    }

    void Tritset::set_trit(size_t index, size_t shift, size_t value) {
        data[index] |= value << shift;
    }

    Trit Tritset::get_trit(size_t index, size_t shift) {
        uint getter = 3 << shift;
        getter &= data[index];
        getter >>= shift;
        clear_trit(index, shift);
        return (Trit)getter;
    }
}