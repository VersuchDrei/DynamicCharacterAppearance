#pragma once

#include "StatIndicatorColorComponent.h"

namespace Threading {
    class StaminaIndicatorColorComponent : public StatIndicatorColorComponent {
    public:
        static const ComponentType TYPE = ComponentType::STAMINAINDICATOR;

        inline StaminaIndicatorColorComponent(GameAPI::GameActor actor) : StatIndicatorColorComponent(actor) {}
        inline StaminaIndicatorColorComponent(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, std::uint32_t version) : StatIndicatorColorComponent(actor, serial, version) {}

        virtual ComponentType getType();

    protected:
        virtual float getStatPercent();
    };
}