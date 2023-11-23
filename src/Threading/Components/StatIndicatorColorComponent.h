#pragma once

#include "ColorComponent.h"

namespace Threading {
    class StatIndicatorColorComponent : public ColorComponent {
    public:
        inline StatIndicatorColorComponent(GameAPI::GameActor actor) : ColorComponent(actor) {
            colors = {{{255, 255, 255, 255}, 1.0f}, {{0, 0, 0, 255}, 0.0f}};
        }

        StatIndicatorColorComponent(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, std::uint32_t version);

        virtual void serialize(GameAPI::GameSerializationInterface serial);

        virtual size_t getColorCount();
        virtual GameAPI::RGBColor getColor(int index);
        virtual void modifyColor(int index, std::function<void(GameAPI::RGBColor*)> mod);
        virtual bool canAddColor();
        virtual void addColor();
        virtual void removeColor();
        virtual GameAPI::RGBColor getColor();

    protected:
        virtual float getStatPercent() = 0;

    private:
        float lastStatPercent = 1.0f;
        std::vector<std::pair<GameAPI::RGBColor, float>> colors;
    };
}