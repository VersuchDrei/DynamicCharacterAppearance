#include "RGBColor.h"

namespace GameAPI {
    void RGBColor::loadSerial(GameSerializationInterface serial) {
        serial.object->ReadRecordData(&red, sizeof(red));
        serial.object->ReadRecordData(&green, sizeof(green));
        serial.object->ReadRecordData(&blue, sizeof(blue));
        serial.object->ReadRecordData(&alpha, sizeof(alpha));
    }

    void RGBColor::writeSerial(GameSerializationInterface serial) {
        serial.object->WriteRecordData(&red, sizeof(red));
        serial.object->WriteRecordData(&green, sizeof(green));
        serial.object->WriteRecordData(&blue, sizeof(blue));
        serial.object->WriteRecordData(&alpha, sizeof(alpha));
    }

    uint8_t RGBColor::getStrength() {
        if (red > green) {
            if (red > blue) {
                return red;
            } else {
                return blue;
            }
        } else {
            if (green > blue) {
                return green;
            } else {
                return blue;
            }
        }
    }

    RGBColor RGBColor::mix(RGBColor other, float ratio) {
        RGBColor newColor = *this * (1.0f - ratio) + other * ratio;
        float newStrength = getStrength() * (1.0f - ratio) + other.getStrength() * ratio;
        float strengthMult = newStrength / newColor.getStrength();
        newColor.red = static_cast<uint8_t>(newColor.red * strengthMult);
        newColor.green = static_cast<uint8_t>(newColor.green * strengthMult);
        newColor.blue = static_cast<uint8_t>(newColor.blue * strengthMult);
        return newColor;
    }
}