// Lawliet Studios All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WarriorGameplayAbility.h"
#include "WarriorHeroGameplayAbility.generated.h"

class UHeroCombatComponent;
class AWarriorHeroController;
class AWarriorHeroCharacter;
/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorHeroGameplayAbility : public UWarriorGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	AWarriorHeroCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	AWarriorHeroController* GetHeroControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

	FGameplayEffectSpecHandle MakeHeroDamageEffectSpec(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount) const;

private:
	TWeakObjectPtr<AWarriorHeroCharacter> CachedHeroCharacter = nullptr;
	TWeakObjectPtr<AWarriorHeroController> CachedHeroController = nullptr;
};
