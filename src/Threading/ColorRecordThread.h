#pragma once

#include "ColorThread.h"

namespace Threading {
    class ColorRecordThread : public ColorThread {
    public:
        inline ColorRecordThread(GameAPI::GameActor actor, GameAPI::GameColor color) : ColorThread(actor), color{color} {}
        ColorRecordThread(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, uint32_t version);
        
        virtual void serialize(GameAPI::GameSerializationInterface serial);

    protected:
        inline GameAPI::GameColor getColorRecord() { return color; }

        virtual void setColor(GameAPI::RGBColor color);
        virtual void updateColor() = 0;

    private:
        GameAPI::GameColor originalColor;
        GameAPI::GameColor color;
    };
}