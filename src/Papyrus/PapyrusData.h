#pragma once

#include "Threading/ThreadManager.h"

namespace PapyrusData {
	using VM = RE::BSScript::IVirtualMachine;

#pragma region util
    Threading::SubThread* getSubThread(RE::Actor* actor, int SubThreadType, int subThreadIndex) {
        Threading::ActorThread* thread = Threading::ThreadManager::getThread(actor);
        if (!thread) {
            return nullptr;
        }

        return thread->getSubThread(static_cast<Threading::SubThreadType>(SubThreadType), subThreadIndex);
    }

    Threading::Component* getComponent(RE::Actor* actor, int subThreadType, int subThreadIndex, int componentIndex) {
        Threading::SubThread* subThread = getSubThread(actor, subThreadType, subThreadIndex);
        if (!subThread) {
            return nullptr;
        }

        return subThread->getComponent(componentIndex);
    }
#pragma endregion

#pragma region actors
    bool IsActorThreadRunning(RE::StaticFunctionTag*, RE::Actor* actor) {
        Threading::ActorThread* thread = Threading::ThreadManager::getThread(actor);
        if (thread) {
            return thread->isRunning();
        }
        return false;
    }

    void StartActorThread(RE::StaticFunctionTag*, RE::Actor* actor) {
        Threading::ActorThread* thread = Threading::ThreadManager::getThread(actor);
        if (thread) {
            thread->start();
        }
    }

    void StopActorThread(RE::StaticFunctionTag*, RE::Actor* actor) {
        Threading::ActorThread* thread = Threading::ThreadManager::getThread(actor);
        if (thread) {
            thread->stop();
        }
    }
#pragma endregion

#pragma region subthreads
    bool IsSubThreadUnique(RE::StaticFunctionTag*, int subThreadType) {
        return Threading::SubThreadTypeAPI::isUnique(static_cast<Threading::SubThreadType>(subThreadType));
    }

    int GetSubThreadCount(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType) {
        Threading::ActorThread* thread = Threading::ThreadManager::getThread(actor);
        if (thread) {
            return thread->getSubThreadCount(static_cast<Threading::SubThreadType>(subThreadType));
        }

        return 0;
    }

    void AddSubThread(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType) {
        Threading::ActorThread* thread = Threading::ThreadManager::getThread(actor);
        if (thread) {
            thread->addSubThread(static_cast<Threading::SubThreadType>(subThreadType));
        }
    }

    void RemoveSubThread(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex) {
        Threading::ActorThread* thread = Threading::ThreadManager::getThread(actor);
        if (thread) {
            thread->removeSubThread(static_cast<Threading::SubThreadType>(subThreadType), subThreadIndex);
        }
    }
#pragma endregion

#pragma region subthreadsettings
    int GetSubThreadSettingCount(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex) {
        Threading::SubThread* subThread = getSubThread(actor, subThreadType, subThreadIndex);
        if (!subThread) {
            return -1;
        }

        return subThread->getSettingCount();
    }

    int GetSubThreadSettingType(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int SubThreadSettingIndex) {
        Threading::SubThread* subThread = getSubThread(actor, subThreadType, subThreadIndex);
        if (!subThread) {
            return -1;
        }

        return static_cast<int>(subThread->getSettingType(SubThreadSettingIndex));
    }

    std::string GetSubThreadSettingName(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int SubThreadSettingIndex) {
        Threading::SubThread* subThread = getSubThread(actor, subThreadType, subThreadIndex);
        if (!subThread) {
            return "Error";
        }

        return subThread->getSettingName(SubThreadSettingIndex);
    }

    std::string GetSubThreadSettingTooltip(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int SubThreadSettingIndex) {
        Threading::SubThread* subThread = getSubThread(actor, subThreadType, subThreadIndex);
        if (!subThread) {
            return "Error";
        }

        return subThread->getSettingTooltip(SubThreadSettingIndex);
    }

    bool GetSubThreadSettingValueBool(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int SubThreadSettingIndex) {
        Threading::SubThread* subThread = getSubThread(actor, subThreadType, subThreadIndex);
        if (!subThread) {
            return false;
        }

        return subThread->getSettingValueBool(SubThreadSettingIndex);
    }

    int GetSubThreadSettingValueInt(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int SubThreadSettingIndex) {
        Threading::SubThread* subThread = getSubThread(actor, subThreadType, subThreadIndex);
        if (!subThread) {
            return 0;
        }

        return subThread->getSettingValueInt(SubThreadSettingIndex);
    }

    float GetSubThreadSettingValueFloat(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int SubThreadSettingIndex) {
        Threading::SubThread* subThread = getSubThread(actor, subThreadType, subThreadIndex);
        if (!subThread) {
            return 0.0f;
        }

        return subThread->getSettingValueFloat(SubThreadSettingIndex);
    }

    std::string GetSubThreadSettingValueString(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int SubThreadSettingIndex) {
        Threading::SubThread* subThread = getSubThread(actor, subThreadType, subThreadIndex);
        if (!subThread) {
            return "";
        }

        return subThread->getSettingValueString(SubThreadSettingIndex);
    }


    std::string GetSubThreadSettingFormat(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int SubThreadSettingIndex) {
        Threading::SubThread* subThread = getSubThread(actor, subThreadType, subThreadIndex);
        if (!subThread) {
            return "{0}";
        }

        return subThread->getSettingFormat(SubThreadSettingIndex);
    }

    float GetSubThreadSettingMin(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int SubThreadSettingIndex) {
        Threading::SubThread* subThread = getSubThread(actor, subThreadType, subThreadIndex);
        if (!subThread) {
            return 0.0f;
        }

        return subThread->getSettingMin(SubThreadSettingIndex);
    }

    float GetSubThreadSettingMax(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int SubThreadSettingIndex) {
        Threading::SubThread* subThread = getSubThread(actor, subThreadType, subThreadIndex);
        if (!subThread) {
            return 0.0f;
        }

        return subThread->getSettingMax(SubThreadSettingIndex);
    }

    float GetSubThreadSettingInterval(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int SubThreadSettingIndex) {
        Threading::SubThread* subThread = getSubThread(actor, subThreadType, subThreadIndex);
        if (!subThread) {
            return 1.0f;
        }

        return subThread->getSettingInterval(SubThreadSettingIndex);
    }

    int GetSubThreadSettingDefaultInt(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int SubThreadSettingIndex) {
        Threading::SubThread* subThread = getSubThread(actor, subThreadType, subThreadIndex);
        if (!subThread) {
            return 0;
        }

        return subThread->getSettingDefaultInt(SubThreadSettingIndex);
    }

    float GetSubThreadSettingDefaultFloat(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int SubThreadSettingIndex) {
        Threading::SubThread* subThread = getSubThread(actor, subThreadType, subThreadIndex);
        if (!subThread) {
            return 0.0f;
        }

        return subThread->getSettingDefaultFloat(SubThreadSettingIndex);
    }

    std::vector<std::string> GetSubThreadSettingOptions(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int SubThreadSettingIndex) {
        Threading::SubThread* subThread = getSubThread(actor, subThreadType, subThreadIndex);
        if (!subThread) {
            return {};
        }

        return subThread->getSettingOptions(SubThreadSettingIndex);
    }


    bool ToggleSubThreadSetting(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int SubThreadSettingIndex) {
        Threading::SubThread* subThread = getSubThread(actor, subThreadType, subThreadIndex);
        if (!subThread) {
            return false;
        }

        return subThread->toggleSetting(SubThreadSettingIndex);
    }

    bool SetSubThreadSettingValueInt(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int SubThreadSettingIndex, int value) {
        Threading::SubThread* subThread = getSubThread(actor, subThreadType, subThreadIndex);
        if (!subThread) {
            return false;
        }

        return subThread->setSettingValue(SubThreadSettingIndex, value);
    }

    bool SetSubThreadSettingValueFloat(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int SubThreadSettingIndex, float value) {
        Threading::SubThread* subThread = getSubThread(actor, subThreadType, subThreadIndex);
        if (!subThread) {
            return false;
        }

        return subThread->setSettingValue(SubThreadSettingIndex, value);
    }
#pragma endregion

#pragma region components
    int GetComponentType(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int componentIndex) {
        Threading::Component* component = getComponent(actor, subThreadType, subThreadIndex, componentIndex);
        if (!component) {
            return -1;
        }

        return static_cast<int>(component->getType());
    }

    void SetComponentType(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int componentIndex, int componentType) {
        Threading::ActorThread* thread = Threading::ThreadManager::getThread(actor);
        if (!thread) {
            return;
        }

        Threading::SubThread* subThread = thread->getSubThread(static_cast<Threading::SubThreadType>(subThreadType), subThreadIndex);
        if (!subThread) {
            return;
        }

        subThread->setComponentType(componentIndex, static_cast<Threading::ComponentType>(componentType));
    }
#pragma endregion

#pragma region compoentcolors
    int GetComponentColorCount(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int componentIndex) {
        Threading::Component* component = getComponent(actor, subThreadType, subThreadIndex, componentIndex);
        return component ? component->getColorCount() : -1;
    }

    int GetComponentColorRed(RE::StaticFunctionTag*, RE::Actor* actor, int SubThreadType, int subThreadIndex, int componentIndex, int colorIndex) {
        Threading::Component* component = getComponent(actor, SubThreadType, subThreadIndex, componentIndex);
        return component ? component->getColor(colorIndex).red : -1;
    }

    int GetComponentColorGreen(RE::StaticFunctionTag*, RE::Actor* actor, int SubThreadType, int subThreadIndex, int componentIndex, int colorIndex) {
        Threading::Component* component = getComponent(actor, SubThreadType, subThreadIndex, componentIndex);
        return component ? component->getColor(colorIndex).green : -1;
    }

    int GetComponentColorBlue(RE::StaticFunctionTag*, RE::Actor* actor, int SubThreadType, int subThreadIndex, int componentIndex, int colorIndex) {
        Threading::Component* component = getComponent(actor, SubThreadType, subThreadIndex, componentIndex);
        return component ? component->getColor(colorIndex).blue : -1;
    }

    int GetComponentColorAlpha(RE::StaticFunctionTag*, RE::Actor* actor, int SubThreadType, int subThreadIndex, int componentIndex, int colorIndex) {
        Threading::Component* component = getComponent(actor, SubThreadType, subThreadIndex, componentIndex);
        return component ? component->getColor(colorIndex).alpha : -1;
    }

    void SetComponentColorToCurrent(RE::StaticFunctionTag*, RE::Actor* actor, int SubThreadType, int subThreadIndex, int componentIndex, int colorIndex) {
        Threading::ActorThread* thread = Threading::ThreadManager::getThread(actor);
        if (!thread) {
            return;
        }

        Threading::SubThread* subThread = thread->getSubThread(static_cast<Threading::SubThreadType>(SubThreadType), subThreadIndex);
        if (!subThread) {
            return;
        }

        subThread->setComponentColorToCurrent(componentIndex, colorIndex);
    }

    void SetComponentColorRed(RE::StaticFunctionTag*, RE::Actor* actor, int SubThreadType, int subThreadIndex, int componentIndex, int colorIndex, int red) {
        Threading::Component* component = getComponent(actor, SubThreadType, subThreadIndex, componentIndex);
        if (!component) {
            return;
        }

       component->modifyColor(colorIndex, [red](GameAPI::RGBColor * color) { color->red = red; });
    }

    void SetComponentColorGreen(RE::StaticFunctionTag*, RE::Actor* actor, int SubThreadType, int subThreadIndex, int componentIndex, int colorIndex, int green) {
       Threading::Component* component = getComponent(actor, SubThreadType, subThreadIndex, componentIndex);
       if (!component) {
            return;
       }

       component->modifyColor(colorIndex, [green](GameAPI::RGBColor* color) { color->green = green; });
    }

    void SetComponentColorBlue(RE::StaticFunctionTag*, RE::Actor* actor, int SubThreadType, int subThreadIndex, int componentIndex, int colorIndex, int blue) {
       Threading::Component* component = getComponent(actor, SubThreadType, subThreadIndex, componentIndex);
       if (!component) {
            return;
       }

       component->modifyColor(colorIndex, [blue](GameAPI::RGBColor* color) { color->blue = blue; });
    }

    void SetComponentColorAlpha(RE::StaticFunctionTag*, RE::Actor* actor, int SubThreadType, int subThreadIndex, int componentIndex, int colorIndex, int alpha) {
       Threading::Component* component = getComponent(actor, SubThreadType, subThreadIndex, componentIndex);
       if (!component) {
            return;
       }

       component->modifyColor(colorIndex, [alpha](GameAPI::RGBColor* color) { color->alpha = alpha; });
    }

    bool CanAddComponentColor(RE::StaticFunctionTag*, RE::Actor* actor, int SubThreadType, int subThreadIndex, int componentIndex) {
       Threading::Component* component = getComponent(actor, SubThreadType, subThreadIndex, componentIndex);
       return component ? component->canAddColor() : false;
    }

    void AddComponentColor(RE::StaticFunctionTag*, RE::Actor* actor, int SubThreadType, int subThreadIndex, int componentIndex) {
       Threading::Component* component = getComponent(actor, SubThreadType, subThreadIndex, componentIndex);
       if (!component) {
            return;
       }

       component->addColor();
    }

    void RemoveComponentColor(RE::StaticFunctionTag*, RE::Actor* actor, int SubThreadType, int subThreadIndex, int componentIndex) {
       Threading::Component* component = getComponent(actor, SubThreadType, subThreadIndex, componentIndex);
       if (!component) {
            return;
       }

       component->removeColor();
    }
#pragma endregion

#pragma region componentsettings
    int GetComponentSettingCount(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int componentIndex) {
        Threading::Component* component = getComponent(actor, subThreadType, subThreadIndex, componentIndex);
       if (!component) {
            return -1;
        }

        return component->getSettingCount();
    }

    int GetComponentSettingType(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int componentIndex, int componentSettingIndex) {
        Threading::Component* component = getComponent(actor, subThreadType, subThreadIndex, componentIndex);
        if (!component) {
            return -1;
        }

        return static_cast<int>(component->getSettingType(componentSettingIndex));
    }

    std::string GetComponentSettingName(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int componentIndex, int componentSettingIndex) {
        Threading::Component* component = getComponent(actor, subThreadType, subThreadIndex, componentIndex);
        if (!component) {
            return "Error";
        }

        return component->getSettingName(componentSettingIndex);
    }

    std::string GetComponentSettingTooltip(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int componentIndex, int componentSettingIndex) {
        Threading::Component* component = getComponent(actor, subThreadType, subThreadIndex, componentIndex);
        if (!component) {
            return "Error";
        }

        return component->getSettingTooltip(componentSettingIndex);
    }

    bool GetComponentSettingValueBool(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int componentIndex, int componentSettingIndex) {
        Threading::Component* component = getComponent(actor, subThreadType, subThreadIndex, componentIndex);
        if (!component) {
            return false;
        }

        return component->getSettingValueBool(componentSettingIndex);
    }

    int GetComponentSettingValueInt(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int componentIndex, int componentSettingIndex) {
        Threading::Component* component = getComponent(actor, subThreadType, subThreadIndex, componentIndex);
        if (!component) {
            return 0;
        }

        return component->getSettingValueInt(componentSettingIndex);
    }

    float GetComponentSettingValueFloat(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int componentIndex, int componentSettingIndex) {
        Threading::Component* component = getComponent(actor, subThreadType, subThreadIndex, componentIndex);
        if (!component) {
            return 0.0f;
        }

        return component->getSettingValueFloat(componentSettingIndex);
    }

    std::string GetComponentSettingValueString(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int componentIndex, int componentSettingIndex) {
        Threading::Component* component = getComponent(actor, subThreadType, subThreadIndex, componentIndex);
        if (!component) {
            return "";
        }

        return component->getSettingValueString(componentSettingIndex);
    }


    std::string GetComponentSettingFormat(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int componentIndex, int componentSettingIndex) {
        Threading::Component* component = getComponent(actor, subThreadType, subThreadIndex, componentIndex);
        if (!component) {
            return "{0}";
        }

        return component->getSettingFormat(componentSettingIndex);
    }

    float GetComponentSettingMin(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int componentIndex, int componentSettingIndex) {
        Threading::Component* component = getComponent(actor, subThreadType, subThreadIndex, componentIndex);
        if (!component) {
            return 0.0f;
        }

        return component->getSettingMin(componentSettingIndex);
    }

    float GetComponentSettingMax(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int componentIndex, int componentSettingIndex) {
        Threading::Component* component = getComponent(actor, subThreadType, subThreadIndex, componentIndex);
        if (!component) {
            return 0.0f;
        }

        return component->getSettingMax(componentSettingIndex);
    }

    float GetComponentSettingInterval(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int componentIndex, int componentSettingIndex) {
        Threading::Component* component = getComponent(actor, subThreadType, subThreadIndex, componentIndex);
        if (!component) {
            return 1.0f;
        }

        return component->getSettingInterval(componentSettingIndex);
    }

    int GetComponentSettingDefaultInt(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int componentIndex, int componentSettingIndex) {
        Threading::Component* component = getComponent(actor, subThreadType, subThreadIndex, componentIndex);
        if (!component) {
            return 0;
        }

        return component->getSettingDefaultInt(componentSettingIndex);
    }

    float GetComponentSettingDefaultFloat(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int componentIndex, int componentSettingIndex) {
        Threading::Component* component = getComponent(actor, subThreadType, subThreadIndex, componentIndex);
        if (!component) {
            return 0.0f;
        }

        return component->getSettingDefaultFloat(componentSettingIndex);
    }

    std::vector<std::string> GetComponentSettingOptions(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int componentIndex, int componentSettingIndex) {
        Threading::Component* component = getComponent(actor, subThreadType, subThreadIndex, componentIndex);
        if (!component) {
            return {};
        }

        return component->getSettingOptions(componentSettingIndex);
    }


    bool ToggleComponentSetting(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int componentIndex, int componentSettingIndex) {
        Threading::Component* component = getComponent(actor, subThreadType, subThreadIndex, componentIndex);
        if (!component) {
            return false;
        }

        return component->toggleSetting(componentSettingIndex);
    }

    bool SetComponentSettingValueInt(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int componentIndex, int componentSettingIndex, int value) {
        Threading::Component* component = getComponent(actor, subThreadType, subThreadIndex, componentIndex);
        if (!component) {
            return false;
        }

        return component->setSettingValue(componentSettingIndex, value);
    }

    bool SetComponentSettingValueFloat(RE::StaticFunctionTag*, RE::Actor* actor, int subThreadType, int subThreadIndex, int componentIndex, int componentSettingIndex, float value) {
        Threading::Component* component = getComponent(actor, subThreadType, subThreadIndex, componentIndex);
        if (!component) {
            return false;
        }

        return component->setSettingValue(componentSettingIndex, value);
    }
#pragma endregion


	bool Bind(VM* a_vm) {
        const auto obj = "DCA_Data"sv;

        BIND(IsActorThreadRunning);
        BIND(StartActorThread);
        BIND(StopActorThread);

        BIND(IsSubThreadUnique);
        BIND(GetSubThreadCount);
        BIND(AddSubThread);
        BIND(RemoveSubThread);

        BIND(GetSubThreadSettingCount);
        BIND(GetSubThreadSettingType);
        BIND(GetSubThreadSettingName);
        BIND(GetSubThreadSettingTooltip);
        BIND(GetSubThreadSettingValueBool);
        BIND(GetSubThreadSettingValueInt);
        BIND(GetSubThreadSettingValueFloat);
        BIND(GetSubThreadSettingValueString);
        BIND(GetSubThreadSettingFormat);
        BIND(GetSubThreadSettingMin);
        BIND(GetSubThreadSettingMax);
        BIND(GetSubThreadSettingInterval);
        BIND(GetSubThreadSettingDefaultInt);
        BIND(GetSubThreadSettingDefaultFloat);
        BIND(GetSubThreadSettingOptions);
        BIND(ToggleSubThreadSetting);
        BIND(SetSubThreadSettingValueInt);
        BIND(SetSubThreadSettingValueFloat);

        BIND(GetComponentType);
        BIND(SetComponentType);

        BIND(GetComponentColorCount);
        BIND(GetComponentColorRed);
        BIND(GetComponentColorGreen);
        BIND(GetComponentColorBlue);
        BIND(GetComponentColorAlpha);
        BIND(SetComponentColorToCurrent);
        BIND(SetComponentColorRed);
        BIND(SetComponentColorGreen);
        BIND(SetComponentColorBlue);
        BIND(SetComponentColorAlpha);
        BIND(CanAddComponentColor);
        BIND(AddComponentColor);
        BIND(RemoveComponentColor);

        BIND(GetComponentSettingCount);
        BIND(GetComponentSettingType);
        BIND(GetComponentSettingName);
        BIND(GetComponentSettingTooltip);
        BIND(GetComponentSettingValueBool);
        BIND(GetComponentSettingValueInt);
        BIND(GetComponentSettingValueFloat);
        BIND(GetComponentSettingValueString);
        BIND(GetComponentSettingFormat);
        BIND(GetComponentSettingMin);
        BIND(GetComponentSettingMax);
        BIND(GetComponentSettingInterval);
        BIND(GetComponentSettingDefaultInt);
        BIND(GetComponentSettingDefaultFloat);
        BIND(GetComponentSettingOptions);
        BIND(ToggleComponentSetting);
        BIND(SetComponentSettingValueInt);
        BIND(SetComponentSettingValueFloat);

        return true;
    }
}