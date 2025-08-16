// Lawliet Studios All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"


class AWarriorWeaponBase;
struct FGameplayTag;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WARRIOR_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWarriorWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	AWarriorWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	UPROPERTY(BlueprintReadWrite, Category = "Warrior|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	AWarriorWeaponBase* GetCurrentEquippedWeapon() const;
	
private:
	TMap<FGameplayTag, AWarriorWeaponBase*> CharacterCarriedWeaponMap;
};