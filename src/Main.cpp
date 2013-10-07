#include "Chronact/Chronact.hpp"
#include <iostream>

int main() {

    Chronact* chronact = new Chronact();
    chronact->Go();

    /*
    try {
        chronact->Go();
    } catch (std::exception& e) {
        std::cout << e.what();
    }
    */

    delete chronact;
}
