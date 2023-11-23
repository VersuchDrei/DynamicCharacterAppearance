#pragma once

namespace Threading {
    enum OverlayType {
        BODY = 0,
        FACE = 1,
        HANDS = 2,
        FEET = 3
    };

    class OverlayTypeAPI {
    public:
        inline static const std::vector<std::string> typeStrings{"Body", "Face", "Hands", "Feet"};

        static std::string getTypeString(OverlayType type);
    };
}