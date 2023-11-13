#pragma once

#include "GameAPI/GameActor.h"

namespace Threading {
    class Thread {
    public:
        inline Thread(GameAPI::GameActor actor) : actor{actor} {}

        virtual void serialize(GameAPI::GameSerializationInterface serial) = 0;

        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void loop() = 0;

        inline GameAPI::GameActor getActor() { return actor; }

    private:
        GameAPI::GameActor actor;
    };
}