#include "trit.h"
#include "func.h"


namespace custom {

    TritProxy::TritProxy(Tritset &origin, size_t trit_index) : origin(origin) {
        this->origin = origin;
        this->trit_index = trit_index;
        this->uint_index = _uint(trit_index);
        size_t pos = 15 - (trit_index % (sizeof(uint) * 8 / 2));
        this->shift = pos * 2;
    }

    TritProxy &TritProxy::operator=(uint value) {
        if (trit_index >= origin.capacity()) {
            if (value != Unknown) {
                origin.resize(trit_index + 1);
                write(value);
            }
        } else
            write(value);
        return *this;
    }

    void TritProxy::write(size_t value) const {
        origin.set_trit(uint_index, shift, value);
    }

    TritProxy::operator Trit() const {
        return origin.get_trit(uint_index, shift);
    }


}