#include "trit.h"


using namespace std;
using custom::Unknown;
using custom::True;
using custom::False;
using custom::Trit;


int main() {

    custom::Tritset set(17);
    size_t allocLength = set.capacity();
    assert(allocLength >= 17 * 2 / 8 / sizeof(uint) );


    set[3] = custom::False;
    Trit a = set[3];
    custom::print_trit(a);


    return 0;
}
                    