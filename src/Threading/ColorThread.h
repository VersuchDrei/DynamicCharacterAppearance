#pragma once

#include "SubThread.h"

#include "Threading/Components/ColorComponent.h"
#include "Threading/Components/FallbackColorComponent.h"

namespace Threading {
    class ColorThread : public SubThread {
    public:
        inline ColorThread(GameAPI::GameActor actor) : SubThread(actor) {
            // TODO: don't hardcode this
            components.push_back(new FallbackColorComponent(actor));
        }
        ColorThread(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, uint32_t version);
        ~ColorThread();

        virtual void serialize(GameAPI::GameSerializationInterface serial);

        virtual void loop();

        virtual Component* getComponent(int index);

        virtual void setComponentType(int index, ComponentType type);

        virtual void setComponentColorToCurrent(int componentIndex, int colorIndex);

    protected:
        virtual void setColor(GameAPI::RGBColor color) = 0;
        virtual GameAPI::RGBColor getColor() = 0;

    private:
        GameAPI::RGBColor lastColor;
        std::vector<ColorComponent*> components;
    };
}