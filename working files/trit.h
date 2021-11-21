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
                this->index = index * 2 / 8 / sizeof(uint);
                this->position =  32 - (index % (sizeof(uint) * 8 / 2));
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
                    write(value);
                /*not ended*/
                return *this;
            }

            void write (size_t value) {
                origin.set_trit(index, position, value);
            }

            void read () {
                origin.get_trit(index, position);
                origin.clear_trit(index, position);
            }

            operator Trit() {
                return origin.get_trit(index, position);
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

        void clear_trit (size_t index, size_t pos) {
            uint cleaner = ~(3 << pos);
            data[index] &= cleaner;
        }

        void set_trit(size_t index, size_t pos, size_t value) {
            clear_trit(index, pos);
            data[index] = value << pos;
        }

        Trit get_trit(size_t index, size_t pos) {
            uint getter = 3 << pos;
            data[index] &= getter;
            getter >>= pos;
            return (Trit)getter;
        }

        explicit operator Trit() {
            return get_trit(1,2);
        }
        // &= ~(000000000000000011 << pos)
    };
}
