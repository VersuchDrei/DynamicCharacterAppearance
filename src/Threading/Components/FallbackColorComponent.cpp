#include "FallbackColorComponent.h"

namespace Threading {
    FallbackColorComponent::FallbackColorComponent(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, std::uint32_t version) : ColorComponent(actor) {
        color.loadSerial(serial);
    }

    ComponentType FallbackColorComponent::getType() {
        return TYPE;
    }

    void FallbackColorComponent::serialize(GameAPI::GameSerializationInterface serial) {
        color.writeSerial(serial);
    }


    GameAPI::RGBColor FallbackColorComponent::getColor(int index) {
        return color;
    }

    void FallbackColorComponent::modifyColor(int index, std::function<void(GameAPI::RGBColor*)> mod) {
        mod(&color);
    }

    size_t FallbackColorComponent::getColorCount() {
        return 1;
    }

    GameAPI::RGBColor FallbackColorComponent::getColor() {
        return color;
    }
}