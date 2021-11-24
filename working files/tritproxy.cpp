#include "trit.h"
#include "func.h"


namespace custom {
    TritProxy::TritProxy(Tritset &origin) : origin(origin) {
        this->origin = origin;
        uint_index = 0;
        trit_index = 0;
        shift = 0;
    }

    TritProxy::TritProxy(Tritset &origin, size_t index) : origin(origin) {
        this->origin = origin;
        this->trit_index = index;
        this->uint_index = trit_to_uint(index);
        size_t pos =  15 - (index % (sizeof(uint) * 8 / 2));
        this->shift = pos * 2;
    }

    TritProxy &TritProxy::operator=(uint value) {
        if (uint_to_trit(uint_index) >= origin.capacity()) {
            if (value != Unknown) {
                origin.resize(trit_index + 1);
                write(value);
            }
        }
        else
            write(value);
        return *this;
    }

    void TritProxy::write(size_t value) {
        origin.set_trit(uint_index, shift, value);
    }

    TritProxy::operator Trit() {
        return origin.get_trit(uint_index, shift);
    }

    /*for testing*/
   /* void TritproxyTest::SetUp() {

    }

    void TritproxyTest::TearDown() {

    }

    size_t TritproxyTest::get_index(const TritProxy &obj) const{
        return obj.uint_index;
    }

    size_t TritproxyTest::get_trit_index(const TritProxy &obj) const {
        return obj.trit_index;
    }

    size_t TritproxyTest::get_shift(const TritProxy &obj) const {
        return obj.shift;
    }*/
}