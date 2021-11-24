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
    public:
        TritProxy(Tritset &origin);

        TritProxy(Tritset &origin, size_t index);

        TritProxy &operator=(uint value);

        void write(size_t value);

        operator Trit();
    };

    class Tritset {
        friend class TritsetTest;
    private:
        uint *data;
        size_t size;
    public:
        Tritset();

        explicit Tritset(size_t length);

        ~Tritset();

        size_t capacity() const;

        void resize(size_t new_size);

        TritProxy operator[](int index);

        void clear_trit(size_t index, size_t pos);

        void set_trit(size_t index, size_t pos, size_t value);

        Trit get_trit(size_t index, size_t pos);

        void shrink();
    };

    class TritsetTest : public ::testing::Test {
    protected:
        void SetUp() override;
        void TearDown() override;
        const size_t get_size(const Tritset &obj) const;
        const uint get_data(const Tritset &obj, int index) const;

        Tritset t1;
        Tritset t2;
        Tritset t3;
        Tritset t4;
    };

   /* class TritproxyTest : public ::testing::Test {
    protected:
    public:
        TritproxyTest();

    protected:
        void SetUp() override;
        void TearDown() override;
        size_t get_trit_index(const TritProxy &obj) const;
        size_t get_index(const TritProxy &obj) const;
        size_t get_shift(const TritProxy &obj) const;

        TritProxy t1;
        TritProxy t2;
        TritProxy t3;
        TritProxy t4;
    };*/
}
