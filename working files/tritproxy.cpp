#include "trit.h"
#include "func.h"


namespace custom {
    TritProxy::TritProxy(Tritset &origin, size_t index) : origin(origin) {
        this->origin = origin;
        this->index = trit_to_uint(index);
        size_t pos =  15 - (index % (sizeof(uint) * 8 / 2));
        this->shift = pos * 2;
    }

    TritProxy &TritProxy::operator=(uint value) {
        if (uint_to_trit(index) >= origin.capacity()) {
            if (value != Unknown) {
                origin.resize(uint_to_trit(index));
                write(value);
            }
        }
        else
            write(value);
        return *this;
    }

    void TritProxy::write(size_t value) {
        origin.set_trit(index, shift, value);
    }

    TritProxy::operator Trit() {
        return origin.get_trit(index, shift);
    }
}