#include "trit.h"
#include "func.h"


namespace custom {
    Tritset::Tritset() {
        data = new uint [1];
        data[0] = 0;
        size = 1;
    }

    Tritset::Tritset(size_t size) {
        if (size != 0)
            this->size = round_up(size * 2, 8 * sizeof(uint));
        else
            this->size =0;

        data = new uint [this->size];
        for (size_t i = 0; i < this->size; ++i)
            data[i] = 0;
        assert(data);
    }

    Tritset::~Tritset() {
        if (size == 0)
            return;
        delete [] data;
    }

    size_t Tritset::capacity() const {
        return _trit(size);
    }

    void Tritset::resize(size_t trit_size) {
        if (trit_size == 0) {
            delete [] data;
            size = 0;
            return;
        }

        size_t new_size = _uint(trit_size) + 1;
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

    Tritset & Tritset::operator=(const Tritset *obj) {
        if (this == obj)
            return *this;

        this->resize(_trit(obj->size - 1));
        for (size_t i = 0; i < this->size; ++i)
            this->data[i] = obj->data[i];

        return *this;
    }

    void Tritset::clear_trit(size_t index, size_t shift) {
        uint cleaner = ~(dec(11) << shift);
        data[index] &= cleaner;
    }

    void Tritset::set_trit(size_t index, size_t shift, size_t value) {
        clear_trit(index, shift);
        data[index] |= value << shift;
    }

    Trit Tritset::get_trit(size_t index, size_t shift) {
        if (_trit(index) >= capacity())
            return Unknown;

        uint getter = dec(11) << shift;
        getter &= data[index];
        getter >>= shift;
        return (Trit)getter;
    }

    void Tritset::shrink() {
        for (size_t ind = size - 1; ind >= 0; --ind)
            if (data[ind] != 0) {
                resize(_trit(ind) + 1);
                return;
            }
    }

    void TritsetTest::SetUp() {
       t1 = new Tritset(10);
       t2 = new Tritset(16);
       t3 = new Tritset(60);
       t4 = new Tritset(32);
    }

    void TritsetTest::TearDown() {
        delete t1;
        delete t2;
        delete t3;
        delete t4;
    }

    const uint TritsetTest::get_data(const Tritset &obj, int index) const {
        return obj.data[index];
    }

    const size_t TritsetTest::get_size(const Tritset &obj) const {
        return obj.size;
    }
}