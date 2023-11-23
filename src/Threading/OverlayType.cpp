#include "OverlayType.h"

namespace Threading {
    std::string OverlayTypeAPI::getTypeString(OverlayType type) {
        switch (type) {
        case OverlayType::BODY:
            return "Body";
        case OverlayType::FACE:
            return "Face";
        case OverlayType::HANDS:
            return "Hands";
        case OverlayType::FEET:
            return "Feet";
        default:
            return "Error";
        }
    }
}