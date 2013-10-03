#include "Chronact/Chronact.hpp"

int main() {
    Chronact* chronact = new Chronact();

    try {
        chronact->Go();
    } catch (std::exception& e) {
        LogError(e.what());
    }
}
