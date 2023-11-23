#pragma once

#include "StatIndicatorColorComponent.h"

namespace Threading {
    class HealthIndicatorColorComponent : public StatIndicatorColorComponent {
    public:
        static const ComponentType TYPE = ComponentType::HEALTHINDICATOR;

        inline HealthIndicatorColorComponent(GameAPI::GameActor actor) : StatIndicatorColorComponent(actor) {}
        inline HealthIndicatorColorComponent(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, std::uint32_t version) : StatIndicatorColorComponent(actor, serial, version) {}

        virtual ComponentType getType();

    protected:
        virtual float getStatPercent();
    };
}