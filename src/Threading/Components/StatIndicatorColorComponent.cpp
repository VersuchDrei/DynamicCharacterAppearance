#include "StatIndicatorColorComponent.h"

namespace Threading {
    StatIndicatorColorComponent::StatIndicatorColorComponent(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, std::uint32_t version) : ColorComponent(actor, serial, version) {
        colors = std::vector<std::pair<GameAPI::RGBColor, float>>(serial.read<size_t>());
        for (std::pair<GameAPI::RGBColor, float>& color : colors) {
            color.first.loadSerial(serial);
            color.second = serial.read<float>();
        }
    }

    void StatIndicatorColorComponent::serialize(GameAPI::GameSerializationInterface serial) {
        Component::serialize(serial);

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
        return true;
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

        if (lastStatPercent >= colors.front().second) {
            return colors.front().first;
        }
        if (lastStatPercent <= colors.back().second) {
            return colors.back().first;
        }

        for (int i = 0; i < colors.size() - 1; i++) {
            if (lastStatPercent > colors[i + 1].second) {
                return colors[i + 1].first.mix(colors[i].first, (lastStatPercent - colors[i + 1].second) / (colors[i].second - colors[i + 1].second));
            }
        }

        return {};
    }

    int StatIndicatorColorComponent::getSettingCount() {
        return colors.size();
    }

    SettingType StatIndicatorColorComponent::getSettingType(int index) {
        return SettingType::SLIDER;
    }

    std::string StatIndicatorColorComponent::getSettingName(int index) {
        return "Color " + std::to_string(index + 1) + " threshold";
    }

    std::string StatIndicatorColorComponent::getSettingTooltip(int index) {
        return "The threshold at which it should be fully at color " + std::to_string(index + 1) + ".";
    }

    int StatIndicatorColorComponent::getSettingValueInt(int index) {
        if (index >= 0 && index < colors.size()) {
            return static_cast<int>(colors[index].second * 100);
        }
        return 0.0f;
    }

    float StatIndicatorColorComponent::getSettingValueFloat(int index) {
        if (index >= 0 && index < colors.size()) {
            return colors[index].second * 100;
        }
        return 0.0f;
    }

    float StatIndicatorColorComponent::getSettingMax(int index) {
        return 100.0f;
    }

    float StatIndicatorColorComponent::getSettingInterval(int index) {
        return 1.0f;
    }

    bool StatIndicatorColorComponent::setSettingValue(int index, int value) {
        if (index < 0 || index >= colors.size()) {
            return false;
        }

        float actualValue = value / 100.0f;
        colors[index].second = actualValue;

        if (index != 0 && colors[index - 1].second < actualValue) {
            sortColors();
            return true;
        }

        if (index < (colors.size() - 1) && colors[index + 1].second > actualValue) {
            sortColors();
            return true;
        }

        return false;
    }

    bool StatIndicatorColorComponent::setSettingValue(int index, float value) {
        if (index < 0 || index >= colors.size()) {
            return false;
        }

        float actualValue = value / 100.0f;
        colors[index].second = actualValue;

        if (index != 0 && colors[index - 1].second < actualValue) {
            sortColors();
            return true;
        }

        if (index < (colors.size() - 1) && colors[index + 1].second > actualValue) {
            sortColors();
            return true;
        }

        return false;
    }


    void StatIndicatorColorComponent::sortColors() {
        std::stable_sort(colors.begin(), colors.end(), [&](std::pair<GameAPI::RGBColor, float> pairA, std::pair<GameAPI::RGBColor, float> pairB) {
            return pairA.second > pairB.second;
        });
    }
}