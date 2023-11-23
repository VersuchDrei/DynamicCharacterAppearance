#pragma once

#include "ColorComponent.h"

namespace Threading {
    class FallbackColorComponent : public ColorComponent {
    public:
        static const ComponentType TYPE = ComponentType::FALLBACK;

        inline FallbackColorComponent(GameAPI::GameActor actor) : ColorComponent(actor) {

        }

        FallbackColorComponent(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, std::uint32_t version);

        virtual ComponentType getType();
        virtual void serialize(GameAPI::GameSerializationInterface serial);

        virtual GameAPI::RGBColor getColor(int index);
        virtual void modifyColor(int index, std::function<void(GameAPI::RGBColor*)> mod);
        virtual size_t getColorCount();
        virtual GameAPI::RGBColor getColor();

    private:
        GameAPI::RGBColor color;
    };
}