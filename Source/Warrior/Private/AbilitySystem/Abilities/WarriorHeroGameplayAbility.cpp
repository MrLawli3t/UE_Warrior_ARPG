// Lawliet Studios All Rights Reserved


#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "WarriorGameplayTags.h"
#include "Characters/WarriorHeroCharacter.h"
#include "Controllers/WarriorHeroController.h"

AWarriorHeroCharacter* UWarriorHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if (!CachedHeroCharacter.IsValid())
	{
		CachedHeroCharacter = Cast<AWarriorHeroCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedHeroCharacter.IsValid() ? CachedHeroCharacter.Get() : nullptr;	
}

AWarriorHeroController* UWarriorHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if (!CachedHeroController.IsValid())
	{
		CachedHeroController = Cast<AWarriorHeroController>(CurrentActorInfo->PlayerController);
	}

	return CachedHeroController.IsValid() ? CachedHeroController.Get() : nullptr;	
}

UHeroCombatComponent* UWarriorHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}

FGameplayEffectSpecHandle UWarriorHeroGameplayAbility::MakeHeroDamageEffectSpec(const TSubclassOf<UGameplayEffect> EffectClass,
	const float InWeaponBaseDamage, const FGameplayTag InCurrentAttackTypeTag, const int32 InUsedComboCount) const
{
	FGameplayEffectContextHandle Context = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	Context.SetAbility(this);
	Context.AddSourceObject(GetAvatarActorFromActorInfo());
	Context.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	
	FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		Context
	);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(WarriorGameplayTags::Shared_SetByCaller_BaseDamage, InWeaponBaseDamage);
	if (InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
	}
	
	return EffectSpecHandle;
}
