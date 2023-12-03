#pragma once

#include "ComponentType.h"

#include "..\SettingType.h"

#include "GameAPI/GameActor.h"

namespace Threading {
    class Component {
    public:
        inline Component(GameAPI::GameActor actor) : actor{actor} {}
        Component(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, uint32_t version);

        virtual void serialize(GameAPI::GameSerializationInterface serial);

        virtual ComponentType getType() = 0;

        virtual size_t getColorCount();
        virtual GameAPI::RGBColor getColor(int index);
        virtual void modifyColor(int index, std::function<void(GameAPI::RGBColor*)> mod);
        virtual bool canAddColor();
        virtual void addColor();
        virtual void removeColor();

        virtual int getSettingCount();
        virtual SettingType getSettingType(int index);
        virtual std::string getSettingName(int index);
        virtual std::string getSettingTooltip(int index);
        virtual bool getSettingValueBool(int index);
        virtual int getSettingValueInt(int index);
        virtual float getSettingValueFloat(int index);
        virtual std::string getSettingValueString(int index);
        virtual std::string getSettingFormat(int index);
        virtual float getSettingMin(int index);
        virtual float getSettingMax(int index);
        virtual float getSettingInterval(int index);
        virtual int getSettingDefaultInt(int index);
        virtual float getSettingDefaultFloat(int index);
        virtual std::vector<std::string> getSettingOptions(int index);
        virtual bool toggleSetting(int index);
        virtual bool setSettingValue(int index, int value);
        virtual bool setSettingValue(int index, float value);


    protected:
        inline GameAPI::GameActor getActor() { return actor; }

    private:
        GameAPI::GameActor actor;
    };
}