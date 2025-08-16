// Lawliet Studios All Rights Reserved


#include "DataAssets/StartupData/DataAsset_StartupDataBase.h"

#include "AbilitySystem/WarriorAbilitySystemComponent.h"

void UDataAsset_StartupDataBase::GiveAbilitiesToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASC, int32 ApplyLevel)
{
	check(InASC);

	GrantAbilities(StartupAbilities, InASC, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASC, ApplyLevel);
}

void UDataAsset_StartupDataBase::GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>>& InAbilitiesToGive,
	UWarriorAbilitySystemComponent* InASC, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty()) return;

	for (const TSubclassOf<UWarriorGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASC->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		
		InASC->GiveAbility(AbilitySpec);
	}
}
