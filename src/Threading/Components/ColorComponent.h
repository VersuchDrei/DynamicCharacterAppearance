#pragma once

#include "Component.h"

#include "GameAPI/RGBColor.h"

namespace Threading {
    class ColorComponent: public Component {
    public:
        inline ColorComponent(GameAPI::GameActor actor) : Component(actor) {}
        inline ColorComponent(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, uint32_t version) : Component(actor, serial, version) {}

        virtual GameAPI::RGBColor getColor() = 0;
    };
}