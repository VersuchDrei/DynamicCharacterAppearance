#pragma once

namespace Threading {
    // do NOT change the values of these, they are getting serialized
    enum ComponentType: uint8_t {
        NONE = 255,
        RAINBOW = 0,
        FALLBACK = 1,
        HEALTHINDICATOR = 2,
        STAMINAINDICATOR = 3,
        MAGICKAINDICATOR = 4
    };
}