#include "SubThreadType.h"

namespace Threading {
    bool SubThreadTypeAPI::isUnique(SubThreadType type) {
        switch (type) {
        case SubThreadType::OVERLAY_COLOR:
            return false;
        default:
            return true;
        }
    }
}