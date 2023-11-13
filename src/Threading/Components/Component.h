#pragma once

#include "GameAPI/GameActor.h"

namespace Threading {
    class Component {
    public:
        inline Component(GameAPI::GameActor actor) : actor{actor} {}

        virtual void serialize(GameAPI::GameSerializationInterface serial) = 0;

    protected:
        inline GameAPI::GameActor getActor() { return actor; }

    private:
        GameAPI::GameActor actor;
    };
}