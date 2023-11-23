#pragma once

#include "ComponentType.h"

#include "GameAPI/GameActor.h"

namespace Threading {
    class Component {
    public:
        inline Component(GameAPI::GameActor actor) : actor{actor} {}

        virtual ComponentType getType() = 0;
        virtual void serialize(GameAPI::GameSerializationInterface serial) = 0;

        virtual size_t getColorCount();
        virtual GameAPI::RGBColor getColor(int index);
        virtual void modifyColor(int index, std::function<void(GameAPI::RGBColor*)> mod);
        virtual bool canAddColor();
        virtual void addColor();
        virtual void removeColor();

    protected:
        inline GameAPI::GameActor getActor() { return actor; }

    private:
        GameAPI::GameActor actor;
    };
}