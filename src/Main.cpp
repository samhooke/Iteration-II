#include "Chronact\Chronact.hpp"

int main() {
    Chronact* chronact = new Chronact();

    try {
        LogInfo("Running Chronact engine");
        chronact->Go();
    } catch (char* e) {
        LogError(e);
    }
}
