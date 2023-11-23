#pragma once

namespace Threading {
    // these need to match the ones in DCA_MCM.psc
    enum SubThreadType {
        HAIR_COLOR = 0,
        SKIN_COLOR = 1,
        OVERLAY_COLOR = 2
    };

    class SubThreadTypeAPI {
    public:
        static bool isUnique(SubThreadType type);
    };
}