// Lawliet Studios All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WarriorHeroGameplayAbility.h"
#include "WarriorHeroLightAttack.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorHeroLightAttack : public UWarriorHeroGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<UAnimMontage*> AttackMontages;
	
private:
	UFUNCTION()
	void OnAbilityCompleted();

	UFUNCTION()
	void OnAbilityCancelled();

	void OnResetComboTimer();

	FTimerDelegate ResetComboTimerDelegate;
	
	FTimerHandle ResetComboTimer;
	int ComboIndex;
};
