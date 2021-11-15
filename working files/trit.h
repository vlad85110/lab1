#include <iostream>
#include <cassert>
#include <vector>

namespace custom {
    enum Trit {False, Unknown, True};

    class Tritset {
    private:
        uint *data;
        size_t size;
        class TritProxy {
        private:
            Tritset & origin;
            int index;
        public:
            TritProxy (Tritset & origin, int index) : origin(origin) {
                this->origin = origin;
                this->index = index;
            }

            ~TritProxy () {
                std::cout << "destructor" << std::endl;
            }

            TritProxy & operator=(uint value){
                if (index >= origin.capacity())
                    if (value != Unknown)
                        origin.data[index] = value;
                /*not ended*/
                return *this;
            }
        };
    public:
        Tritset(size_t length);
        ~Tritset();
        size_t capacity() const;
        TritProxy operator[](int index) {
            TritProxy temp(*this, index);
            return temp;
        }
    };

}
