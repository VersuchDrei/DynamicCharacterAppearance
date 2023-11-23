#include "ColorRecordThread.h"

namespace Threading {
    ColorRecordThread::ColorRecordThread(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, uint32_t version) : ColorThread(actor, serial, version) {
        originalColor.loadSerial(serial);
        color.loadSerial(serial);
    }

    void ColorRecordThread::serialize(GameAPI::GameSerializationInterface serial) {
        ColorThread::serialize(serial);

        originalColor.writeSerial(serial);
        color.writeSerial(serial);
    }

    void ColorRecordThread::setColor(GameAPI::RGBColor color) {
        this->color.setColor(color);
        updateColor();
    }

    GameAPI::RGBColor ColorRecordThread::getColor() {
        return color.getColor();
    }
}