#pragma once

#include "ColorThread.h"
#include "OverlayType.h"

namespace Threading {
    class OverlayColorThread : public ColorThread {
    public:
        inline OverlayColorThread(GameAPI::GameActor actor) : ColorThread(actor), isFemale{actor.isSex(GameAPI::GameSex::FEMALE)} {}
        OverlayColorThread(GameAPI::GameActor actor, GameAPI::GameSerializationInterface serial, uint32_t version);

        virtual void serialize(GameAPI::GameSerializationInterface serial);

        virtual void start();
        virtual void stop();

        virtual int getSettingCount();
        virtual SettingType getSettingType(int index);
        virtual std::string getSettingName(int index);
        virtual std::string getSettingTooltip(int index);
        virtual int getSettingValueInt(int index);
        virtual float getSettingValueFloat(int index);
        virtual std::string getSettingValueString(int index);
        virtual float getSettingMax(int index);
        virtual std::vector<std::string> getSettingOptions(int index);
        virtual void setSettingValue(int index, int value);
        virtual void setSettingValue(int index, float value);

    protected:
        virtual void setColor(GameAPI::RGBColor color);
        virtual GameAPI::RGBColor getColor();

    private:
        bool isFemale = false;
        OverlayType type = OverlayType::BODY;
        int index = 0;
    };
}