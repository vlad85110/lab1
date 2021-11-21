#include <iostream>

namespace custom {
    class Tritset;

    class TritProxy;

    enum Trit {
        Unknown, True, False
    };

    void print_trit(Trit val);

    class TritProxy {
        friend Tritset;
    private:
        Tritset &origin;
        size_t index;
        size_t shift;
    public:
        TritProxy(Tritset &origin, size_t index);

        TritProxy &operator=(uint value);

        void write(size_t value);

        operator Trit();
    };

    class Tritset {
    private:
        uint *data;
        size_t size;
    public:
        explicit Tritset(size_t length);

        ~Tritset();

        size_t capacity() const;

        void resize(size_t new_size);

        TritProxy operator[](int index);

        void clear_trit(size_t index, size_t pos);

        void set_trit(size_t index, size_t pos, size_t value);

        Trit get_trit(size_t index, size_t pos);
    };
}
