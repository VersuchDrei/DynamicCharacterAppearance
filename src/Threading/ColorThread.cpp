#include "ColorThread.h"

#include "Components/FallbackColorComponent.h"
#include "Components/HealthIndicatorColorComponent.h"
#include "Components/MagickaIndicatorColorComponent.h"
#include "Components/RainbowColorComponent.h"
#include "Components/StaminaIndicatorColorComponent.h"

namespace Threading {
    ColorThread::ColorThread(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, uint32_t version) : SubThread(actor) {
        size_t size = serial.read<size_t>();
        for (int i = 0; i < size; i++) {
            ComponentType type = serial.read<ComponentType>();
            switch (type) {
            case RainbowColorComponent::TYPE:
                components.push_back(new RainbowColorComponent(actor, serial, version));
                break;
            case FallbackColorComponent::TYPE:
                components.push_back(new FallbackColorComponent(actor, serial, version));
                break;
            case HealthIndicatorColorComponent::TYPE:
                components.push_back(new HealthIndicatorColorComponent(actor, serial, version));
                break;
            case StaminaIndicatorColorComponent::TYPE:
                components.push_back(new StaminaIndicatorColorComponent(actor, serial, version));
                break;
            case MagickaIndicatorColorComponent::TYPE:
                components.push_back(new MagickaIndicatorColorComponent(actor, serial, version));
                break;
            }
        }
    }

    ColorThread::~ColorThread() {
        for (ColorComponent* component : components) {
            delete component;
        }
    }

    void ColorThread::serialize(GameAPI::GameSerializationInterface serial) {
        serial.write<size_t>(components.size());
        for (ColorComponent* component : components) {
            serial.write<ComponentType>(component->getType());
            component->serialize(serial);
        }
    }

    void ColorThread::loop() {
        GameAPI::RGBColor nextColor = components[0]->getColor();
        if (nextColor != lastColor) {
            setColor(nextColor);
            lastColor = nextColor;
        }
    }

    Component* ColorThread::getComponent(int index) {
        if (index < 0 || index >= components.size()) {
            return nullptr;
        }

        return components[index];
    }

    void ColorThread::setComponentType(int index, ComponentType type) {
        if (index < 0 || index >= components.size()) {
            return;
        }

        delete components[index];
        switch (type) {
        case RainbowColorComponent::TYPE:
            components[index] = new RainbowColorComponent(getActor());
            break;
        case FallbackColorComponent::TYPE:
            components[index] = new FallbackColorComponent(getActor());
            break;
        case HealthIndicatorColorComponent::TYPE:
            components[index] = new HealthIndicatorColorComponent(getActor());
            break;
        case StaminaIndicatorColorComponent::TYPE:
            components[index] = new StaminaIndicatorColorComponent(getActor());
            break;
        case MagickaIndicatorColorComponent::TYPE:
            components[index] = new MagickaIndicatorColorComponent(getActor());
            break;
        default:
            components[index] = new FallbackColorComponent(getActor());
        }
    }

    void ColorThread::setComponentColorToCurrent(int componentIndex, int colorIndex) {
        if (componentIndex < 0 || componentIndex >= components.size()) {
            return;
        }

        GameAPI::RGBColor currentColor = getColor();
        components[componentIndex]->modifyColor(colorIndex, [currentColor](GameAPI::RGBColor* color) {
            color->red = currentColor.red;
            color->green = currentColor.green;
            color->blue = currentColor.blue;
            color->alpha = currentColor.alpha;
        });
    }
}