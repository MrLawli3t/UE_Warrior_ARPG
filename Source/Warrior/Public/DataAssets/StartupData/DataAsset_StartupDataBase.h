// Lawliet Studios All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartupDataBase.generated.h"

class UWarriorAbilitySystemComponent;
class UWarriorGameplayAbility;
/**
 * 
 */
UCLASS()
class WARRIOR_API UDataAsset_StartupDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveAbilitiesToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASC, int32 ApplyLevel = 1);
protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<UWarriorGameplayAbility>> StartupAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<UWarriorGameplayAbility>> ReactiveAbilities;

	void GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>>& InAbilitiesToGive, UWarriorAbilitySystemComponent* InASC, int32 ApplyLevel = 1);
};
