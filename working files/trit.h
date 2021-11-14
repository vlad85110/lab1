#include <iostream>
#include <cassert>

namespace custom {
    class Tritset {
    private:
        enum Trit {False, Unknown, True};
        uint *data;
        size_t length;
    public:
        Tritset(size_t length);
        ~Tritset();
        size_t capacity();
        uint operator[](int value);
};
}



