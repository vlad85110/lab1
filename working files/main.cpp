#include "trit.h"

using namespace std;
using custom::Unknown;
using custom::True;
using custom::False;



int main() {

    custom::Tritset set(17);
    size_t allocLength = set.capacity();
    assert(allocLength >= 17 * 2 / 8 / sizeof(uint) );

    std::vector<int> d(20);
    d[20] = 11;





    //1 uint  - 16 trits
    set[0] = Unknown;
    custom::Trit a = set[0];
    uint y = 65532 << 2;




    cout << y  << endl;

    return 0;
}
                    