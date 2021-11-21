#include "trit.h"


namespace custom {
    TritProxy::TritProxy(Tritset &origin, size_t index) : origin(origin) {
        this->origin = origin;
        this->index = index * 2 / 8 / sizeof(uint);
        size_t pos =  15 - (index % (sizeof(uint) * 8 / 2));
        this->shift = pos * 2;
    }

    TritProxy &TritProxy::operator=(uint value) {
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

    void TritProxy::write(size_t value) {
        origin.set_trit(index, shift, value);
    }

    void TritProxy::read() {
        origin.get_trit(index, shift);
        origin.clear_trit(index, shift);
    }

    TritProxy::operator Trit() {
        return origin.get_trit(index, shift);
    }
}