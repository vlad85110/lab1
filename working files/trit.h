#include <iostream>
#include <cassert>
#include <vector>


namespace custom {
    class Tritset;
    class TritProxy;

    size_t round_up(size_t x, size_t y);

    enum Trit {
        False, Unknown, True
    };

    void print_trit (Trit val);

    class TritProxy {
    private:
        Tritset &origin;
        size_t index;
        size_t shift;
        friend class Tritset;
    public:
        TritProxy(Tritset &origin, size_t index);

        TritProxy & operator=(uint value);

        void write (size_t value);

        void read ();

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

        TritProxy operator[](int index) {
            TritProxy temp(*this, index);
            return temp;
        }

        void clear_trit (size_t index, size_t pos);

        void set_trit(size_t index, size_t pos, size_t value);

        Trit get_trit(size_t index, size_t pos);
    };

}
