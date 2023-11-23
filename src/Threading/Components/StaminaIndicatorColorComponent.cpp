#include "StaminaIndicatorColorComponent.h"

namespace Threading {
    ComponentType StaminaIndicatorColorComponent::getType() { return TYPE; }

    float StaminaIndicatorColorComponent::getStatPercent() { return getActor().getStaminaPercent(); }
}