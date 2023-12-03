#pragma once

#include "ColorComponent.h"

#include "Util/FormTable.h"

namespace Threading {
    class RainbowColorComponent : public ColorComponent {
    public:
        static const ComponentType TYPE = ComponentType::RAINBOW;

        inline RainbowColorComponent(GameAPI::GameActor actor) : ColorComponent(actor) {
            colors = {{255, 0, 0, 255}, {0, 255, 0, 255}, {0, 0, 255, 255}};
        }

        RainbowColorComponent(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, std::uint32_t version);

        virtual ComponentType getType();
        virtual void serialize(GameAPI::GameSerializationInterface serial);

        virtual size_t getColorCount();
        virtual GameAPI::RGBColor getColor(int index);
        virtual void modifyColor(int index, std::function<void(GameAPI::RGBColor*)> mod);
        virtual bool canAddColor();
        virtual void addColor();
        virtual void removeColor();
        virtual GameAPI::RGBColor getColor();

        virtual int getSettingCount();
        virtual SettingType getSettingType(int index);
        virtual std::string getSettingName(int index);
        virtual std::string getSettingTooltip(int index);
        virtual int getSettingValueInt(int index);
        virtual float getSettingValueFloat(int index);
        virtual std::string getSettingFormat(int index);
        virtual float getSettingMin(int index);
        virtual float getSettingMax(int index);
        virtual float getSettingInterval(int index);
        virtual bool setSettingValue(int index, int value);
        virtual bool setSettingValue(int index, float value);

    private:
        int idleTime = 1000;
        int transitionTime = 2000;
        int currentColor = 0;
        int colorCountdown = 0;
        bool isTransitioning = false;
        std::vector<GameAPI::RGBColor> colors;
    };
}