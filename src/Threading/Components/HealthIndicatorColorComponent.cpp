#include "HealthIndicatorColorComponent.h"

namespace Threading {
    ComponentType HealthIndicatorColorComponent::getType() {
        return TYPE;
    }

    float HealthIndicatorColorComponent::getStatPercent() {
        return getActor().getHealthPercent();
    }
}