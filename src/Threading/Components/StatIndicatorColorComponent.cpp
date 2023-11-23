#include "StatIndicatorColorComponent.h"

namespace Threading {
    StatIndicatorColorComponent::StatIndicatorColorComponent(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, std::uint32_t version) : ColorComponent(actor) {
        colors = std::vector<std::pair<GameAPI::RGBColor, float>>(serial.read<size_t>());
        for (std::pair<GameAPI::RGBColor, float>& color : colors) {
            color.first.loadSerial(serial);
            color.second = serial.read<float>();
        }
    }

    void StatIndicatorColorComponent::serialize(GameAPI::GameSerializationInterface serial) {
        serial.write<size_t>(colors.size());
        for (std::pair<GameAPI::RGBColor, float>& color : colors) {
            color.first.writeSerial(serial);
            serial.write<float>(color.second);
        }
    }


    size_t StatIndicatorColorComponent::getColorCount() {
        return colors.size();
    }

    GameAPI::RGBColor StatIndicatorColorComponent::getColor(int index) {
        if (index < 0 || index >= colors.size()) {
            return {};
        }

       return colors[index].first;
    }

    void StatIndicatorColorComponent::modifyColor(int index, std::function<void(GameAPI::RGBColor*)> mod) {
        if (index < 0 || index >= colors.size()) {
            return;
        }

        mod(&colors[index].first);
    }

    bool StatIndicatorColorComponent::canAddColor() {
        // TODO make this true
        return false;
    }

    void StatIndicatorColorComponent::addColor() {
        colors.push_back({{255, 255, 255, 255}, 0.0f});
    }

    void StatIndicatorColorComponent::removeColor() {
        if (colors.size() > 1) {
            colors.resize(colors.size() - 1);
        }
    }

    GameAPI::RGBColor StatIndicatorColorComponent::getColor() {
        float newStatPercent = getStatPercent();
        if (newStatPercent > lastStatPercent) {
            lastStatPercent += 0.04f;
            if (newStatPercent < lastStatPercent) {
                lastStatPercent = newStatPercent;
            }
        } else if (newStatPercent < lastStatPercent) {
            lastStatPercent -= 0.04f;
            if (newStatPercent > lastStatPercent) {
                lastStatPercent = newStatPercent;
            }
        }

        // TODO support more than two colors
        return colors[1].first.mix(colors[0].first, lastStatPercent);
    }
}