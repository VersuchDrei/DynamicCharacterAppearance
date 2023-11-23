#pragma once

#include "StatIndicatorColorComponent.h"

namespace Threading {
    class MagickaIndicatorColorComponent : public StatIndicatorColorComponent {
    public:
        static const ComponentType TYPE = ComponentType::MAGICKAINDICATOR;

        inline MagickaIndicatorColorComponent(GameAPI::GameActor actor) : StatIndicatorColorComponent(actor) {}
        inline MagickaIndicatorColorComponent(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, std::uint32_t version) : StatIndicatorColorComponent(actor, serial, version) {}

        virtual ComponentType getType();

    protected:
        virtual float getStatPercent();
    };
}