#include "Chronact.hpp"
#include <iostream>

int main() {

    Chronact* chronact = new Chronact();

    try {
        chronact->Go();
    } catch (std::exception& e) {
        std::cout << e.what();
    }

    delete chronact;
}
