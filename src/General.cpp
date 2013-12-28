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

std::vector<std::string> Explode(std::string str, char split) {

    std::vector<std::string> exploded;
    std::ostringstream currentString;

    char lastChar = split;
    for (int i = 0; i < (int)str.length(); i++) {
        char thisChar = str[i];

        // Build up currentString
        if (thisChar != split)
            currentString << thisChar;

        // If we go from a non-split to a split, that is the end of this section
        if (lastChar != split && thisChar == split) {
            exploded.push_back(currentString.str());

            // Reset the currentString to a blank string
            currentString.str(std::string());
        }

        lastChar = thisChar;
    }

    // Place the final string in the array
    exploded.push_back(currentString.str());

    return exploded;
}

bool StringToInt(std::string &s, int &i) {
    std::istringstream myStream(s);
    myStream >> i;
    return !(myStream.fail());
}
