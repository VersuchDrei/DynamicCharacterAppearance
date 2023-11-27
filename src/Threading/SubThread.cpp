#include "SubThread.h"

namespace Threading {
    int SubThread::getSettingCount() { return 0; }
    SettingType SubThread::getSettingType(int index) { return SettingType::NO_SETTING; }
    std::string SubThread::getSettingName(int index) { return "Error"; }
    std::string SubThread::getSettingTooltip(int index) { return "Error"; }
    bool SubThread::getSettingValueBool(int index) { return false; }
    int SubThread::getSettingValueInt(int index) { return 0; }
    float SubThread::getSettingValueFloat(int index) { return 0.0f; }
    std::string SubThread::getSettingValueString(int index) { return ""; }
    std::string SubThread::getSettingFormat(int index) { return "{0}"; }
    float SubThread::getSettingMin(int index) { return 0.0f; }
    float SubThread::getSettingMax(int index) { return 0.0f; }
    float SubThread::getSettingInterval(int index) { return 1.0f; }
    int SubThread::getSettingDefaultInt(int index) { return 0; }
    float SubThread::getSettingDefaultFloat(int index) { return 0.0f; }
    std::vector<std::string> SubThread::getSettingOptions(int index) { return {}; }
    void SubThread::toggleSetting(int index) {}
    void SubThread::setSettingValue(int index, int value) {}
    void SubThread::setSettingValue(int index, float value) {}

    void SubThread::setComponentColorToCurrent(int componentIndex, int colorIndex) {}
}