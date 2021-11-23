#include "trit.h"
#include "func.h"


namespace custom {
    Tritset::Tritset(size_t size) {
        if (size != 0)
            this->size = round_up(size * 2, 8 * sizeof(uint));
        else
            this->size =0;

        data = new uint [this->size];
        assert(data);
    }

    Tritset::~Tritset() {
        delete [] data;
    }

    size_t Tritset::capacity() const {
        return uint_to_trit(size);
    }

    void Tritset::resize(size_t trit_index)  {
        size_t new_size = trit_to_uint(trit_index) + 1;
        auto temp = new uint [new_size];

        for (int i = 0; i < size && i <new_size; ++i)
            temp[i] = data[i];
        delete [] data;
        size = new_size;
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

    void Tritset::shrink() {
        for (size_t ind = size - 1; ind >= 0; --ind)
            for (int sh = 0; sh <= 30; ++sh)
                if (get_trit(ind, sh) != Unknown) {
                    resize(ind);
                    return;
                }
    }
}