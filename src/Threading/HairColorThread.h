#pragma once

#include "ColorRecordThread.h"

namespace Threading {
    class HairColorThread : public ColorRecordThread {
    public:
        inline HairColorThread(GameAPI::GameActor actor, GameAPI::GameColor color) : ColorRecordThread(actor, color), originalColor{actor.getHairColor()} {}
        HairColorThread(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, uint32_t version);

        virtual void serialize(GameAPI::GameSerializationInterface serial);

        virtual void start();
        virtual void stop();

    protected:
        virtual void updateColor();

    private:
        GameAPI::GameColor originalColor;
    };
}