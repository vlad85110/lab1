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

        data = (uint *)calloc(this->size, sizeof(uint));
        assert(data);
    }

    Tritset::~Tritset() {
        if (size == 0)
            return;
        delete [] data;
    }

    const size_t Tritset::capacity() const {
        return _trit(size);
    }

    void Tritset::resize(size_t trit_size) {
        if (trit_size == 0) {
            delete [] data;
            size = 0;
            return;
        }

        size_t new_size = round_up(trit_size * 2, 8 * sizeof(uint));
        uint * temp = (uint *)calloc(new_size, sizeof(uint));//new uint [new_size];
        for (int i = 0; i < size && i <new_size; ++i)
            temp[i] = data[i];

        delete [] data;
        size = new_size;
        data = temp;
    }

    TritProxy Tritset::operator[](size_t index) {
        TritProxy temp(*this, index);
        return temp;
    }

    Trit Tritset::operator[](size_t index) const {
        size_t trit_index = index;
        size_t pos = 15 - (trit_index % (sizeof(uint) * 8 / 2));
        return get_trit(_uint(trit_index), pos * 2);
    }

    Tritset & Tritset::operator=(const Tritset &obj) {
        if (this == &obj)
            return *this;

        this->resize(_trit(obj.size));
        for (size_t i = 0; i < this->size; ++i)
            this->data[i] = obj.data[i];

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

    const Trit Tritset::get_trit(size_t index, size_t shift) const {
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

    Tritset Tritset::operator&(const Tritset &s_2) const {
        size_t res_size = max(this->capacity(), s_2.capacity());
        Tritset res(res_size);
        size_t t_1, t_2;

        for (int i = 0; i < res.size; ++i) {
            for (int sh = 0; sh <= 30; sh+=2) {
                t_1 = this->get_trit(i, sh);
                t_2 = s_2.get_trit(i, sh);
                res.set_trit(i, sh, _and(t_1, t_2));
            }
        }
        return res;
    }

    Tritset Tritset::operator|(const Tritset &s_2) const {
        size_t res_size = max(this->capacity(), s_2.capacity());
        Tritset res(res_size);
        size_t t_1, t_2;

        for (int i = 0; i < res.size; ++i) {
            for (int sh = 0; sh <= 30; sh += 2) {
                t_1 = this->get_trit(i, sh);
                t_2 = s_2.get_trit(i, sh);
                res.set_trit(i, sh, _or(t_1, t_2));
            }
        }
        return res;
    }

    Tritset Tritset::operator~() const {
        Tritset res (this->capacity());
        size_t t;

        for (int i = 0; i < res.size; ++i)
            for (int sh = 0; sh <= 30; sh += 2) {
                t = this->get_trit(i, sh);
                res.set_trit(i, sh, _not(t));
            }
        return res;
    }

    const size_t Tritset::cardinality(Trit value) const {
        size_t cnt = 0;
        size_t l_sh = 0;

        if (value == Unknown) {
            size_t last_ind = size - 1;

            for (size_t i = size - 1; i != 0; i--)
                if (data[i] != 0) {
                    last_ind = i;
                    break;
                }

            for (size_t sh = 30; sh != 0; sh -= 2)
                if (get_trit(last_ind, sh) != value)
                    l_sh = sh;

            for (size_t i = 0; i < last_ind; ++i)
                for (size_t sh = 0; sh <= 30; sh += 2) {
                    if (get_trit(i, sh) == value)
                        cnt++;
                }

            for (int sh = 30; sh != l_sh - 2; sh -= 2) {
                if (get_trit(last_ind, sh) == value)
                    cnt++;
            }
            return cnt;
        }

        for (size_t i = 0; i < size; ++i)
            for (size_t sh = 0; sh <= 30; sh += 2)
                if (get_trit(i, sh) == value)
                    cnt++;

        return cnt;
    }

    const std::unordered_map<Trit, int, std::hash<int>> Tritset::cardinality() const {
        std::unordered_map<Trit, int, std::hash<int>> res;
        for (int i = 0; i < size; ++i)
            for (int sh = 0; sh <= 30; sh += 2)
                res[get_trit(i, sh)]++;
        return res;
    }

    void Tritset::trim(size_t lastIndex) {
        resize(lastIndex + 1);

        for (size_t sh = 30 - 2 * (lastIndex % 16); sh != -2; --sh) {
           set_trit(_uint(lastIndex),sh, Unknown);
        }
    }

     const size_t Tritset::length() const {
        for (size_t ind = size - 1; ind >= 0; --ind)
            if (data[ind] != 0)
                for (size_t sh = 30, pos = 0; sh >= 0; sh -= 2, pos +=2)
                    if (get_trit(ind, sh) != Unknown)
                        return _trit(ind) + pos / 2 + 1;
        return 0;
    }

    Tritset::Iterator::Iterator(Tritset *origin, size_t index)  {
        this->index = index;
        this->origin = origin;
    }

    Tritset::Iterator Tritset::Iterator::operator++() {
        index++;
    }

    Tritset::Iterator Tritset::Iterator::operator--() {
        index--;
    }

    bool Tritset::Iterator::operator==(const Iterator &it) const {
        if (this->index == it.index && this->origin == it.origin)
            return true;
        else
            return false;
    }

    bool Tritset::Iterator::operator!=(const Iterator &it) const {
        if (this->operator==(it))
            return false;
        else
            return true;
    }

    TritProxy Tritset::Iterator::operator*() {
        return  (*origin)[index];
    }

    Tritset::Iterator Tritset::begin() {
        return Tritset::Iterator(this, 0);
    }

    Tritset::Iterator Tritset::end() {
        return Tritset::Iterator(this, _trit(size) - 1);
    }



    /*class for testing*/
    void TritsetTest::SetUp() {
       t1 = new Tritset(10);
       t2 = new Tritset(16);
       t3 = new Tritset(60);
       t4 = new Tritset(33);
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