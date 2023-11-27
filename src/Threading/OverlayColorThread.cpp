#include "OverlayColorThread.h"

namespace Threading {
    OverlayColorThread::OverlayColorThread(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, uint32_t version) : ColorThread(actor, serial, version), isFemale{actor.isSex(GameAPI::GameSex::FEMALE)} {
        type = serial.read<OverlayType>();
        index = serial.read<int>();
    }

    void OverlayColorThread::serialize(GameAPI::GameSerializationInterface serial) {
        ColorThread::serialize(serial);

        serial.write<OverlayType>(type);
        serial.write<int>(index);
    }

    void OverlayColorThread::start() {}

    void OverlayColorThread::stop() {}


    int OverlayColorThread::getSettingCount() {
        return 2;
    }

    SettingType OverlayColorThread::getSettingType(int index) {
        switch (index) {
        case 0:
            return SettingType::MENU;
        case 1:
            return SettingType::SLIDER;
        default:
            return SettingType::NO_SETTING;
        }
    }

    std::string OverlayColorThread::getSettingName(int index) {
        switch (index) {
        case 0:
            return "Overlay type";
        case 1:
            return "Overlay index";
        default:
            return "Error";
        }
    }

    std::string OverlayColorThread::getSettingTooltip(int index) {
        switch (index) {
        case 0:
            return "The type of the overlay you want to define dynamic colors for.";
        case 1:
            return "The index of the overlay you want to define dynamic colors for.";
        default:
            return "Error";
        }
    }

    int OverlayColorThread::getSettingValueInt(int index) {
        switch (index) {
        case 0:
            return type;
        case 1:
            return this->index;
        default:
            return 0;
        }
    }

    float OverlayColorThread::getSettingValueFloat(int index) {
        switch (index) {
        case 0:
            return type;
        case 1:
            return this->index;
        default:
            return 0.0f;
        }
    }

    std::string OverlayColorThread::getSettingValueString(int index) {
        switch (index) {
        case 0:
            return OverlayTypeAPI::getTypeString(type);
        case 1:
            return std::to_string(this->index);
        default:
            return "";
        }
    }

    float OverlayColorThread::getSettingMax(int index) {
        switch (index) {
        case 0:
            return 3.0f;
        case 1:
            return 50.0f;
        default:
            return 0.0f;
        }
    }

    std::vector<std::string> OverlayColorThread::getSettingOptions(int index) {
        switch (index) {
        case 0:
            return OverlayTypeAPI::typeStrings;
        default:
            return {};
        }
    }

    void OverlayColorThread::setSettingValue(int index, int value) {
        switch (index) {
        case 0:
            type = static_cast<OverlayType>(value);
            break;
        case 1:
            this->index = value;
            break;
        }
    }

    void OverlayColorThread::setSettingValue(int index, float value) {
        switch (index) {
        case 0:
            type = static_cast<OverlayType>(value);
            break;
        case 1:
            this->index = value;
            break;
        }
    }


    void OverlayColorThread::setColor(GameAPI::RGBColor color) {
        bool isFemale = this->isFemale;
        std::string typeString = OverlayTypeAPI::getTypeString(type) + " [ovl" + std::to_string(index) + "]";
        int colorInt = (static_cast<int>(color.red) << 16) + (static_cast<int>(color.green) << 8) + color.blue;
        float alphaFloat = static_cast<float>(color.alpha) / 255.0f;
        const auto skyrimVM = RE::SkyrimVM::GetSingleton();
        auto vm = skyrimVM ? skyrimVM->impl : nullptr;
        if (vm) {
            RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback;
            auto args = RE::MakeFunctionArguments<RE::Actor*, bool, std::string, int, float>(std::move(getActor().form), std::move(isFemale), std::move(typeString), std::move(colorInt), std::move(alphaFloat));
            vm->DispatchStaticCall("DCA_SKSE", "ApplyOverlayColor", args, callback);
        }
    }

    GameAPI::RGBColor OverlayColorThread::getColor() {
        return {};
    }
}