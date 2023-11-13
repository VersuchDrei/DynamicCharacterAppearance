#pragma once

#include "Component.h"

#include "GameAPI/RGBColor.h"

namespace Threading {
    class ColorComponent: public Component {
    public:
        inline ColorComponent(GameAPI::GameActor actor) : Component(actor) {}

        virtual GameAPI::RGBColor getColor() = 0;
    };
}