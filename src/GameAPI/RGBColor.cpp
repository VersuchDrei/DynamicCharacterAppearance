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
}