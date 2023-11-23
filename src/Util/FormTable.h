#pragma once

#include "GameAPI/GameColor.h"

namespace Util {
    class FormTable {
    public:
        static void setupForms();

        static inline GameAPI::GameColor getPlayerHairColor() { return DCA_PlayerHairColor; }
    private:
        static inline GameAPI::GameColor DCA_PlayerHairColor;
    };
}