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


    //1 uint  - 16 trits
    set[0] = Unknown;
    Trit a = set[0];
    uint y = 65532 << 2;



    cout << a << endl;

    return 0;
}
                    