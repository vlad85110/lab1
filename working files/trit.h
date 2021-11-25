#include <iostream>
#include <gtest/gtest.h>

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

        void write(size_t value);
    public:
        TritProxy(Tritset &origin, size_t index);

        TritProxy &operator=(uint value);

        operator Trit();
    };

    class Tritset {
        friend class TritsetTest;
        friend class TritProxy;
    private:
        uint *data;
        size_t size;

        void clear_trit(size_t index, size_t pos);

        void set_trit(size_t index, size_t pos, size_t value);

        Trit get_trit(size_t index, size_t pos);
    public:
        Tritset();

        explicit Tritset(size_t length);

        ~Tritset();

        size_t capacity() const;

        void resize(size_t new_size);

        TritProxy operator[](int index);

        Tritset & operator=(const Tritset *obj);

        void shrink();
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
