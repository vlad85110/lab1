#include "func.h"
#include "trit.h"


using namespace std;
using custom::Unknown;
using custom::True;
using custom::False;
using custom::Trit;


int main() {

    custom::Tritset set(1000);
// length of internal array
    size_t allocLength = set.capacity();
    assert(allocLength >= 1000*2 / 8 / sizeof(uint) );
// 1000*2 - min bits count
// 1000*2 / 8 - min bytes count
// 1000*2 / 8 / sizeof(uint) - min uint[] size

//не выделяет никакой памяти
    set[1000000000] = Unknown;
    assert(allocLength == set.capacity());

// false, but no exception or memory allocation if(set[2000000000]==True){}
    assert(allocLength == set.capacity());

//выделение памяти
    set[1000000000] = True;
    assert(allocLength < set.capacity());

//no memory operations
    allocLength = set.capacity();
    set[1000000000] = Unknown;
    set[1000000] = False;
    assert(allocLength == set.capacity());

    return 0;
}
                    