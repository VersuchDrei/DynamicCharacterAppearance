#include "MagickaIndicatorColorComponent.h"

namespace Threading {
    ComponentType MagickaIndicatorColorComponent::getType() {
        return TYPE;
    }

    float MagickaIndicatorColorComponent::getStatPercent() {
        return getActor().getMagickaPercent();
    }
}