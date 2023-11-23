#pragma once

#include "GameColor.h"
#include "GameSex.h"

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
        bool isSex(GameSex sex) const;

        inline GameColor getHairColor() const { return form->GetActorBase()->headRelatedData->hairColor; }
        inline void setHairColor(GameColor color) const { form->GetActorBase()->SetHairColor(color.form); }
        inline void updateHairColor() { form->UpdateHairColor(); }

        inline float getHealthPercent() { return getAVPercent(form, RE::ActorValue::kHealth); }
        inline float getStaminaPercent() { return getAVPercent(form, RE::ActorValue::kStamina); }
        inline float getMagickaPercent() { return getAVPercent(form, RE::ActorValue::kMagicka); }

    private:
        inline static float getAVPercent(RE::Actor* actor, RE::ActorValue av) {
            using func_t = decltype(getAVPercent);
            REL::Relocation<func_t> func{RELOCATION_ID(36347, 37337)};
            return func(actor, av);
        }
    };
}  // namespace GameAPI