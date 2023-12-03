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

    int Component::getSettingCount() { return 0; }
    SettingType Component::getSettingType(int index) { return SettingType::NO_SETTING; }
    std::string Component::getSettingName(int index) { return "Error"; }
    std::string Component::getSettingTooltip(int index) { return "Error"; }
    bool Component::getSettingValueBool(int index) { return false; }
    int Component::getSettingValueInt(int index) { return 0; }
    float Component::getSettingValueFloat(int index) { return 0.0f; }
    std::string Component::getSettingValueString(int index) { return ""; }
    std::string Component::getSettingFormat(int index) { return "{0}"; }
    float Component::getSettingMin(int index) { return 0.0f; }
    float Component::getSettingMax(int index) { return 0.0f; }
    float Component::getSettingInterval(int index) { return 1.0f; }
    int Component::getSettingDefaultInt(int index) { return 0; }
    float Component::getSettingDefaultFloat(int index) { return 0.0f; }
    std::vector<std::string> Component::getSettingOptions(int index) { return {}; }
    bool Component::toggleSetting(int index) { return false; }
    bool Component::setSettingValue(int index, int value) { return false; }
    bool Component::setSettingValue(int index, float value) { return false; }
}