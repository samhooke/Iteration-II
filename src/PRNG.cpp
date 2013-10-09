#include "PRNG.hpp"

int badRand(int low, int high) {
    static int seed = 5323;
    seed = (8253729 * seed + 2396403);
    return seed % (high - low + 1) + low;
}
