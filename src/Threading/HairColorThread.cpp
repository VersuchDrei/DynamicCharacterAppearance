#include "HairColorThread.h"

#include "Util/FormTable.h"

namespace Threading {
    HairColorThread::HairColorThread(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, uint32_t version) : ColorRecordThread(actor, serial, version) {
        originalColor.loadSerial(serial);
    }

    void HairColorThread::serialize(GameAPI::GameSerializationInterface serial) {
        ColorRecordThread::serialize(serial);

        originalColor.writeSerial(serial);
    }

    void HairColorThread::start() {
        if (!getActor().isLoaded()) {
            logger::info("actor wans't loaded");
            return;
        }
        getActor().SetHairColor(getColorRecord());
    }

    void HairColorThread::stop() {
        if (!getActor().isLoaded()) {
            logger::info("actor wans't loaded");
            return;
        }
        getActor().SetHairColor(originalColor);
        getActor().form->UpdateHairColor();
    }

    void HairColorThread::updateColor() {
        getActor().form->UpdateHairColor();
    }
}