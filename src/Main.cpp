#include "Chronact/Chronact.hpp"
#include <iostream>

int main() {

    Chronact* chronact = new Chronact();

    try {
        chronact->Go();
    } catch (std::exception& e) {
        printf(e.what());
    }
}
