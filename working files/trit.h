#include <iostream>
#include <cassert>
#include <vector>

namespace custom {
    size_t round_up(size_t x, size_t y);

    enum Trit {
        False, Unknown, True
    };

    class Tritset {
    public:
        uint *data;
        size_t size;

        class TritProxy {
        private:
            Tritset &origin;
            size_t index;
            size_t position;
        public:
            TritProxy(Tritset &origin, size_t index) : origin(origin) {
                this->origin = origin;
                this->index = index;
                this->position =  16 - (index % (sizeof(uint) * 8 / 2));
            }

            ~TritProxy() {
                std::cout << "destructor" << std::endl;
            }

            TritProxy & operator=(uint value) {
                if (index >= origin.capacity()) {
                    if (value != Unknown)
                        /*realloc */
                        write(value);
                }
                else
                    origin.data[index * 2 / 8 / sizeof(uint)] |= value << position;


                /*not ended*/
                return *this;
            }

            void write (size_t value) {
                origin.data[index * 2 / 8 / sizeof(uint)] &= value << position;
            }

        };
    public:
        explicit Tritset(size_t length);

        ~Tritset();

        size_t capacity() const;

        TritProxy operator[](int index) {
            TritProxy temp(*this, index);
            return temp;
        }

        operator Trit(){
            return Unknown;
        }
        // &= ~(000000000000000011 << pos)

    };
}
