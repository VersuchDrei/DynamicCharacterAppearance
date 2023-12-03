#include "RainbowColorComponent.h"

#include "Util/Constants.h"

namespace Threading {
    RainbowColorComponent::RainbowColorComponent(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, std::uint32_t version) : ColorComponent(actor, serial, version) {
        idleTime = serial.read<int>();
        transitionTime = serial.read<int>();
        colors = std::vector<GameAPI::RGBColor>(serial.read<size_t>());
        for (GameAPI::RGBColor& color : colors) {
            color.loadSerial(serial);
        }
    }

    void RainbowColorComponent::serialize(GameAPI::GameSerializationInterface serial) {
        Component::serialize(serial);

        serial.write<int>(idleTime);
        serial.write<int>(transitionTime);
        serial.write<size_t>(colors.size());
        for (GameAPI::RGBColor& color : colors) {
            color.writeSerial(serial);
        }
    }

    ComponentType RainbowColorComponent::getType() {
        return TYPE;
    }


    size_t RainbowColorComponent::getColorCount() {
        return colors.size();
    }

    GameAPI::RGBColor RainbowColorComponent::getColor(int index) {
        if (index < 0 || index >= colors.size()) {
            return {};
        }

        return colors[index];
    }

    void RainbowColorComponent::modifyColor(int index, std::function<void(GameAPI::RGBColor*)> mod) {
        if (index < 0 || index >= colors.size()) {
            return;
        }

        mod(&colors[index]);
    }

    bool RainbowColorComponent::canAddColor() {
        return true;
    }

    void RainbowColorComponent::addColor() {
        colors.push_back({255, 255, 255, 255});
    }

    void RainbowColorComponent::removeColor() {
        if (colors.size() > 1) {
            colors.resize(colors.size() - 1);
        }
    }

    GameAPI::RGBColor RainbowColorComponent::getColor() {
        colorCountdown -= Constants::LOOP_TIME_MILLISECONDS;

        if (colorCountdown < 0) {
            if (isTransitioning) {
                isTransitioning = false;
                currentColor = (currentColor + 1) % colors.size();
                colorCountdown = idleTime;
            } else {
                isTransitioning = true;
                colorCountdown = transitionTime;
            }
        }

        if (isTransitioning) {
            int nextColor = (currentColor + 1) % colors.size();
            return colors[nextColor].mix(colors[currentColor], colorCountdown / static_cast<float>(transitionTime));
        } else {
            return colors[currentColor];
        }
    }


    int RainbowColorComponent::getSettingCount() {
        return 2;
    }

    SettingType RainbowColorComponent::getSettingType(int index) {
        return SettingType::SLIDER;
    }

    std::string RainbowColorComponent::getSettingName(int index) {
        switch (index) {
            case 0:
                return "Idle time";
            case 1:
                return "Transition time";
            default:
                return "Error";
        }
    }

    std::string RainbowColorComponent::getSettingTooltip(int index) {
        switch (index) {
            case 0:
                return "The time (in seconds) that this component will stay on a color.";
            case 1:
                return "The time (in seconds) that it takes this component to transition from one color to the next.";
            default:
                return "Error";
        }
    }

    int RainbowColorComponent::getSettingValueInt(int index) {
        switch (index) {
            case 0:
                return idleTime;
            case 1:
                return transitionTime;
            default:
                return 0;
        }
    }

    float RainbowColorComponent::getSettingValueFloat(int index) {
        switch (index) {
            case 0:
                return idleTime / 1000.0f;
            case 1:
                return transitionTime / 1000.0f;
            default:
                return 0.0f;
        }
    }

    std::string RainbowColorComponent::getSettingFormat(int index) {
        return "{1}";
    }

    float RainbowColorComponent::getSettingMin(int index) {
        return 0.1f;
    }

    float RainbowColorComponent::getSettingMax(int index) {
        return 10.0f;
    }

    float RainbowColorComponent::getSettingInterval(int index) {
        return 0.1f;
    }

    bool RainbowColorComponent::setSettingValue(int index, int value) {
        switch (index) {
            case 0:
                idleTime = value;
                break;
            case 1:
                transitionTime = value;
                break;
        }
        return false;
    }

    bool RainbowColorComponent::setSettingValue(int index, float value) {
        switch (index) {
            case 0:
                idleTime = static_cast<int>(value * 1000);
                break;
            case 1:
                transitionTime = static_cast<int>(value * 1000);
                break;
        }
        return false;
    }
}