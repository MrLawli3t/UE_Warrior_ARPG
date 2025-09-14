// Lawliet Studios All Rights Reserved


#include "AbilitySystem/Abilities/WarriorHeroLightAttack.h"

#include "WarriorFunctionLibrary.h"
#include "WarriorGameplayTags.h"
#include "Characters/WarriorHeroCharacter.h"
#include "Components/Combat/HeroCombatComponent.h"

void UWarriorHeroLightAttack::PostMontageLogic()
{
	if (CurrentComboIndex + 2 == AttackMontages.Num())
	{
		UWarriorFunctionLibrary::AddGameplayTagToActor(GetHeroCharacterFromActorInfo(), WarriorGameplayTags::Player_Status_JumpToFinisher);
	}
	
	Super::PostMontageLogic();
}

void UWarriorHeroLightAttack::OnResetComboTimer()
{
	Super::OnResetComboTimer();
	
	UWarriorFunctionLibrary::RemoveGameplayTagFromActor(GetHeroCharacterFromActorInfo(), WarriorGameplayTags::Player_Status_JumpToFinisher);
}

void UWarriorHeroLightAttack::OnMeleeHitEvent(FGameplayEventData Payload)
{
	checkf(DamageEffectClass, TEXT("Missing damage effect class for light attack!"));
	ApplyEffectSpecHandleToTarget(Payload.Target, MakeHeroDamageEffectSpec(DamageEffectClass, GetHeroCombatComponentFromActorInfo()->GetEquippedWeaponScaledDamage(GetAbilityLevel()), WarriorGameplayTags::Player_SetByCaller_AttackType_Light, UsedComboIndex));
}