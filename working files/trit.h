#pragma once
#include <unordered_map>
#include <gtest/gtest.h>
#include <iterator>

namespace custom {
    class Tritset;

    class TritProxy;

    enum Trit {
        Unknown, True, False
    };

    void print_trit(Trit val);

    class TritProxy {
        friend class TritsetTest;
    private:
        Tritset &origin;
        size_t uint_index;
        size_t trit_index;
        size_t shift;

        void write(size_t value) const;
    public:
        TritProxy(Tritset &origin, size_t index);

        TritProxy &operator=(uint value);

        operator Trit() const;
    };

    class Tritset {
        friend class TritsetTest;
        friend class TritProxy;
    private:
        uint *data;
        size_t size;

        void clear_trit(size_t index, size_t pos);

        void set_trit(size_t index, size_t pos, size_t value);

        const Trit get_trit(size_t index, size_t pos) const;
    public:
        class Iterator {
        private:
            Tritset *origin;
            size_t index;
        public:
            Iterator(Tritset *origin, size_t index);

            Iterator operator++();

            Iterator operator--();

            bool operator==(const Iterator& it) const;

            bool operator!=(const Iterator& it) const;

            TritProxy operator*();
        };

        Iterator begin();

        Iterator end();

        Tritset();

        explicit Tritset(size_t length);

        ~Tritset();

        const size_t capacity() const;

        void resize(size_t new_size);

        TritProxy operator[](size_t index);

        Trit operator[](size_t index) const;

        Tritset & operator=(const Tritset &obj);

        void shrink();

        Tritset operator&(const Tritset &s_2) const;

        Tritset operator|(const Tritset &s_2) const;

        Tritset operator~() const;

        const size_t cardinality(Trit value) const;

        const std::unordered_map< Trit, int, std::hash<int> > cardinality() const;

        void trim(size_t lastIndex);

        const size_t length() const;


    };

    class TritsetTest : public ::testing::Test {
    protected:
        void SetUp() override;
        void TearDown() override;
        const size_t get_size(const Tritset &obj) const;
        const uint get_data(const Tritset &obj, int index) const;

        Tritset *t1;
        Tritset *t2;
        Tritset *t3;
        Tritset *t4;
    };
}
