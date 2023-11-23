#include "Component.h"

namespace Threading {
    size_t Component::getColorCount() { return 0; }
    GameAPI::RGBColor Component::getColor(int index) { return {}; }
    void Component::modifyColor(int index, std::function<void(GameAPI::RGBColor*)> mod) {}
    bool Component::canAddColor() { return false; }
    void Component::addColor() {}
    void Component::removeColor() {}
}