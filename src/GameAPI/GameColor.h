#pragma once

#include "GameRecord.h"
#include "RGBColor.h"

namespace GameAPI {
    struct GameColor : public GameRecord<RE::BGSColorForm> {
        inline GameColor() {}
        inline GameColor(RE::BGSColorForm* color) { form = color; }

        inline RGBColor getColor() { return {form->color.red, form->color.green, form->color.blue, form->color.alpha}; }
        void setColor(RGBColor color);
    };
}