#include "Component.h"

namespace Threading {
    Component::Component(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, uint32_t version) : actor{actor} {
        if (version >= 1) {
            serial.read<size_t>();
        }
    }

    void Component::serialize(GameAPI::GameSerializationInterface serial) {
        serial.write<size_t>(0);
    }

    size_t Component::getColorCount() { return 0; }
    GameAPI::RGBColor Component::getColor(int index) { return {}; }
    void Component::modifyColor(int index, std::function<void(GameAPI::RGBColor*)> mod) {}
    bool Component::canAddColor() { return false; }
    void Component::addColor() {}
    void Component::removeColor() {}
}