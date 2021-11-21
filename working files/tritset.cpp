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
        return uint_to_trit(size);
    }

    void Tritset::resize(size_t new_size)  {
        uint *temp = new uint [trit_to_uint(new_size) + 1];
        for (int i = 0; i < size; ++i)
            temp[i] = data[i];
        delete [] data;
        size = trit_to_uint(new_size) + 1;
        data = temp;
    }

    TritProxy Tritset::operator[](int index) {
        TritProxy temp(*this, index);
        return temp;
    }

    void Tritset::clear_trit(size_t index, size_t shift) {
        uint cleaner = ~(3 << shift);
        data[index] &= cleaner;
    }

    void Tritset::set_trit(size_t index, size_t shift, size_t value) {
        clear_trit(index, shift);
        data[index] |= value << shift;
    }

    Trit Tritset::get_trit(size_t index, size_t shift) {
        if (uint_to_trit(index) >= capacity())
            return Unknown;
        uint getter = 3 << shift;
        getter &= data[index];
        getter >>= shift;
        return (Trit)getter;
    }
}