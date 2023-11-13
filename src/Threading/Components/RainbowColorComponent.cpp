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

        // TODO do this differently
        colors = Util::FormTable::colors;
    }

    void RainbowColorComponent::serialize(GameAPI::GameSerializationInterface serial) {
        serial.write<ComponentType>(TYPE);
        serial.write<int>(idleTime);
        serial.write<int>(transitionTime);
        serial.write<size_t>(colors.size());
        for (GameAPI::RGBColor& color : colors) {
            color.writeSerial(serial);
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
            float currentPercent = colorCountdown / static_cast<float>(transitionTime);
            return colors[currentColor] * currentPercent + colors[nextColor] * (1.0f - currentPercent);
        } else {
            return colors[currentColor];
        }
    }
}