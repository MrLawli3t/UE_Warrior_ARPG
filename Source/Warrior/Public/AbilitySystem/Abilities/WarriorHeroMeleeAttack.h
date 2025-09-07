// Lawliet Studios All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WarriorHeroGameplayAbility.h"
#include "WarriorHeroMeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorHeroMeleeAttack : public UWarriorHeroGameplayAbility
{
	GENERATED_BODY()
	
public:
	UWarriorHeroMeleeAttack();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<UAnimMontage*> AttackMontages;
	
	/*
1. Sets instancing policy   
2. Removes Player_Status_JumpToFinisher
3. Binds timer for resetting combo index
4. Clears the previous timer
	*/
	virtual void PreMontageLogic();

	//Increments the combo index and waits for Shared_Event_MeleeHit
	virtual void PostMontageLogic();

	virtual void OnResetComboTimer();

	int CurrentComboIndex = 0;
	int UsedComboIndex = 0;
	
private:
	UFUNCTION()
	void OnAbilityCompleted();

	UFUNCTION()
	void OnAbilityCancelled();

	UFUNCTION()
	void OnMeleeHitEvent(FGameplayEventData Payload);

	FTimerDelegate ResetComboTimerDelegate;
	
	FTimerHandle ResetComboTimer;
};
