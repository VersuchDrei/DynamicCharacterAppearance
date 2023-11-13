#include "ColorThread.h"

namespace Threading {
    ColorThread::ColorThread(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, uint32_t version) : Thread(actor) {
        size_t size = serial.read<size_t>();
        for (int i = 0; i < size; i++) {
            ComponentType type = serial.read<ComponentType>();
            switch (type) {
            case RainbowColorComponent::TYPE:
                components.push_back(new RainbowColorComponent(actor, serial, version));
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
}