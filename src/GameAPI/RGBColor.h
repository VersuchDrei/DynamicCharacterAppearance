#pragma once

#include "GameSerializationInterface.h"

namespace GameAPI {
    struct RGBColor {
        uint8_t red = 0;
        uint8_t green = 0;
        uint8_t blue = 0;
        uint8_t alpha = 0;

        inline bool operator==(const RGBColor other) { return red == other.red && green == other.green && blue == other.blue && alpha == other.alpha; }
        inline bool operator!=(const RGBColor other) { return red != other.red || green != other.green || blue != other.blue || alpha != other.alpha; }

        inline RGBColor operator+(const RGBColor other) {
            return {
                static_cast<uint8_t>(red + other.red),
                static_cast<uint8_t>(green + other.green),
                static_cast<uint8_t>(blue + other.blue),
                static_cast<uint8_t>(alpha + other.alpha)
            };
        }

        inline RGBColor operator*(const float multiplier) {
            return {
                static_cast<uint8_t>(red * multiplier),
                static_cast<uint8_t>(green * multiplier),
                static_cast<uint8_t>(blue * multiplier),
                static_cast<uint8_t>(alpha * multiplier)
            };
        }

        void loadSerial(GameSerializationInterface serial);
        void writeSerial(GameSerializationInterface serial);
    };
}