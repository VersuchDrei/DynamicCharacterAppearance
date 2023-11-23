#include "RainbowColorComponent.h"

#include "Util/Constants.h"

namespace Threading {
    RainbowColorComponent::RainbowColorComponent(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, std::uint32_t version) : ColorComponent(actor) {
        idleTime = serial.read<int>();
        transitionTime = serial.read<int>();
        colors = std::vector<GameAPI::RGBColor>(serial.read<size_t>());
        for (GameAPI::RGBColor& color : colors) {
            color.loadSerial(serial);
        }
    }

    ComponentType RainbowColorComponent::getType() {
        return TYPE;
    }

    void RainbowColorComponent::serialize(GameAPI::GameSerializationInterface serial) {
        serial.write<int>(idleTime);
        serial.write<int>(transitionTime);
        serial.write<size_t>(colors.size());
        for (GameAPI::RGBColor& color : colors) {
            color.writeSerial(serial);
        }
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
}