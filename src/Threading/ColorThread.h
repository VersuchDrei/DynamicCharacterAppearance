#pragma once

#include "Thread.h"

#include "Threading/Components/ColorComponent.h"
#include "Threading/Components/RainbowColorComponent.h"

namespace Threading {
    class ColorThread : public Thread {
    public:
        inline ColorThread(GameAPI::GameActor actor) : Thread(actor) {
            // TODO: don't hardcode this
            components.push_back(new RainbowColorComponent(actor));
        }
        ColorThread(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, uint32_t version);
        ~ColorThread();

        virtual void serialize(GameAPI::GameSerializationInterface serial);

        virtual void loop();

    protected:
        virtual void setColor(GameAPI::RGBColor color) = 0;

    private:
        GameAPI::RGBColor lastColor;
        std::vector<ColorComponent*> components;
    };
}