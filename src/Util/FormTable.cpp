#include "FormTable.h"

#include <fstream>
#include <sstream>
#include <string>

namespace Util {
    void FormTable::setupForms() {
        DCA_PlayerHairColor.loadFile("Dynamic Character Appearance.esp", 0xD62);
    }
}