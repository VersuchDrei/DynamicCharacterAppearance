#include "GameActor.h"

namespace GameAPI {
    bool GameActor::isSex(GameSex sex) const {
        RE::SEX actorSex = form->GetActorBase()->GetSex();
        switch (sex) {
            case MALE:
                return actorSex == RE::SEX::kMale;
            case FEMALE:
                return actorSex == RE::SEX::kFemale;
            case AGENDER:
                return actorSex == RE::SEX::kNone;
        }
        return false;
    }
}