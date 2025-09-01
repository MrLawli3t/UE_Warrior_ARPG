// Lawliet Studios All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAsset_StartupDataBase.h"
#include "DataAsset_EnemyStartupData.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UDataAsset_EnemyStartupData : public UDataAsset_StartupDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveAbilitiesToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASC, int32 ApplyLevel = 1) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<UWarriorGameplayAbility>> EnemyCombatAbilities;
};
