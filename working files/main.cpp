#include "trit.h"

using namespace std;

int main() {
    custom::Tritset set(50000);
    size_t allocLength = set.capacity();
    vector<int> a(10);
    int b = a.capacity();

    set[50000] = custom::Unknown;


    cout <<allocLength<< endl;

    return 0;
}
