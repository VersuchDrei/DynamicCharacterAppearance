#include "FormTable.h"

#include <fstream>
#include <sstream>
#include <string>

namespace Util {
    void FormTable::setupForms() {
        DCA_PlayerHairColor.loadFile("Dynamic Character Appearance.esp", 0xD62);

        std::ifstream infile("Data/SKSE/Plugins/DynamicCharacterAppearance.txt");
        // TODO remove this
        std::string line;
        while (std::getline(infile, line)) {
            if (line.length() != 6) {
                continue;
            }

            GameAPI::RGBColor color{.alpha = 255};
            color.red = std::stoi(line.substr(0, 2), 0, 16);
            color.green = std::stoi(line.substr(2, 2), 0, 16);
            color.blue = std::stoi(line.substr(4, 2), 0, 16);

            colors.push_back(color);
        }

        if (colors.empty()) {
            colors.push_back({});
        }
    }
}