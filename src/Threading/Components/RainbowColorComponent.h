#pragma once

#include "ColorComponent.h"
#include "ComponentType.h"

#include "Util/FormTable.h"

namespace Threading {
    class RainbowColorComponent : public ColorComponent {
    public:
        static const ComponentType TYPE = ComponentType::RAINBOW;

        inline RainbowColorComponent(GameAPI::GameActor actor) : ColorComponent(actor) {
            // TODO do this differently
            colors = Util::FormTable::colors;
        }

        RainbowColorComponent(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, std::uint32_t version);

        virtual void serialize(GameAPI::GameSerializationInterface serial);

        virtual GameAPI::RGBColor getColor();

    private:
        int idleTime = 1000;
        int transitionTime = 2000;
        int currentColor = 0;
        int colorCountdown = 0;
        bool isTransitioning = false;
        std::vector<GameAPI::RGBColor> colors;
    };
}