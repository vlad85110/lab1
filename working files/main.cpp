
#include "trit.h"

using namespace std;

int main() {
    custom::Tritset set(50000);
    size_t allocLength = set.capacity();
    set[1] = 1;

    cout <<set[0]<< endl;

    return 0;
}
