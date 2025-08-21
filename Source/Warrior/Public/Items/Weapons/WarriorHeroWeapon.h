// Lawliet Studios All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "WarriorWeaponBase.h"
#include "WarriorTypes/WarriorStructTypes.h"
#include "WarriorHeroWeapon.generated.h"

UCLASS()
class WARRIOR_API AWarriorHeroWeapon : public AWarriorWeaponBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FWarriorHeroWeaponData HeroWeaponData;

private:
	TArray<FGameplayAbilitySpecHandle> AbilityHandles;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void AssignAbilityHandles(const TArray<FGameplayAbilitySpecHandle>& InAbilityHandles) {AbilityHandles = InAbilityHandles;}

	UFUNCTION(BlueprintPure)
	FORCEINLINE TArray<FGameplayAbilitySpecHandle> GetAbilityHandles() const {return AbilityHandles;}
};
