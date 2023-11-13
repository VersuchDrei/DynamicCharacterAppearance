#pragma once

#include "GameColor.h"

namespace GameAPI {
    struct GameActor : public GameRecord<RE::Actor> {
    public:
        inline static GameActor getPlayer() { return RE::PlayerCharacter::GetSingleton(); }

        inline GameActor() {}
        inline GameActor(RE::Actor* actor) { form = actor; }

        inline uint32_t getBaseFormID() const { return form->GetActorBase()->formID; }

        inline bool isLoaded() const { return form->Is3DLoaded(); }
        inline bool isDisabled() const { return form->IsDisabled(); }
        inline bool isDeleted() const { return form->IsMarkedForDeletion() || form->IsDeleted(); }

        inline bool isPlayer() const { return form->IsPlayerRef(); }
        inline std::string getName() const { return form->GetDisplayFullName(); }

        inline GameColor getHairColor() const { return form->GetActorBase()->headRelatedData->hairColor; }
        inline void SetHairColor(GameColor color) const { form->GetActorBase()->SetHairColor(color.form); }
    };
}  // namespace GameAPI