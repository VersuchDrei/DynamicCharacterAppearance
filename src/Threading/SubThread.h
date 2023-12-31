#pragma once

#include "SettingType.h"
#include "Thread.h"

#include "Components/Component.h"

namespace Threading{
    class SubThread : public Thread {
    public:
        inline SubThread(GameAPI::GameActor actor) : Thread(actor) {}

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

        virtual Component* getComponent(int index) = 0;

        virtual void setComponentType(int index, ComponentType type) = 0;

        virtual void setComponentColorToCurrent(int componentIndex, int colorIndex);
    };
}