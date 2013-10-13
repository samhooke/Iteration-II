#include "General.hpp"
#include <sstream>

std::string Timestamp(int time) {
    std::ostringstream os;
    os << " [";
    os.width(3);
    os << time;
    os << "] ";
    return os.str();
}
