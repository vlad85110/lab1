#pragma once
typedef unsigned int uint;
typedef unsigned long size_t;



namespace custom {
    size_t round_up(size_t x, size_t y);

    size_t _trit(size_t val);

    size_t _uint(size_t val);

    size_t dec(size_t val_10);

    uint _and(uint x, uint y);

    uint _or(uint x, uint y);

    uint _not(uint x);

    size_t max(size_t x, size_t y);
}
