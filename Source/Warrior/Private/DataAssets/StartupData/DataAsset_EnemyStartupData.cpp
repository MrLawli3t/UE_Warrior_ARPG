// Lawliet Studios All Rights Reserved


#include "DataAssets/StartupData/DataAsset_EnemyStartupData.h"

#include "AbilitySystem/WarriorAbilitySystemComponent.h"

void UDataAsset_EnemyStartupData::GiveAbilitiesToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASC, int32 ApplyLevel)
{
	Super::GiveAbilitiesToAbilitySystemComponent(InASC, ApplyLevel);

	if (!InASC) return;

	GrantAbilities(EnemyCombatAbilities, InASC, ApplyLevel);
}
