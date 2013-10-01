#include "Chronauto.hpp"
#include "Logger.hpp"

int main() {
    Chronauto* chronauto = new Chronauto();

    try {
        LogInfo("Running Chronauto");
        chronauto->Go();
    } catch (char* e) {
        LogError(e);
    }
}
