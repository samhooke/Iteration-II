#include "PRNG.hpp"

unsigned int badRand(unsigned int low, unsigned int high) {
    static unsigned int seed = 5323;
    seed = (8253729 * seed + 2396403);
    return seed % (high - low + 1) + low;
}
