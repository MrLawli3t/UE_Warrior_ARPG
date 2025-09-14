// Lawliet Studios All Rights Reserved


#include "AbilitySystem/Abilities/WarriorHeroMeleeAttack.h"

#include "WarriorDebugHelper.h"
#include "WarriorFunctionLibrary.h"
#include "WarriorGameplayTags.h"
#include "Characters/WarriorHeroCharacter.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Components/Combat/HeroCombatComponent.h"

UWarriorHeroMeleeAttack::UWarriorHeroMeleeAttack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UWarriorHeroMeleeAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                              const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	PreMontageLogic();
	
	if (UAnimMontage* Montage = AttackMontages[CurrentComboIndex])
	{
		UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this,
			FName(""),
			Montage
		);

		MontageTask->OnCompleted.AddDynamic(this, &ThisClass::OnAbilityCompleted);
		MontageTask->OnBlendOut.AddDynamic(this, &ThisClass::OnAbilityCompleted);
		MontageTask->OnInterrupted.AddDynamic(this, &ThisClass::OnAbilityCancelled);
		MontageTask->OnCancelled.AddDynamic(this, &ThisClass::OnAbilityCancelled);
		
		MontageTask->ReadyForActivation();
	}

	PostMontageLogic();
}

void UWarriorHeroMeleeAttack::PreMontageLogic()
{
	UWarriorFunctionLibrary::RemoveGameplayTagFromActor(GetHeroCharacterFromActorInfo(), WarriorGameplayTags::Player_Status_JumpToFinisher);

	ResetComboTimerDelegate.BindUObject(this, &ThisClass::OnResetComboTimer);

	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(ResetComboTimer);
	}
}

void UWarriorHeroMeleeAttack::PostMontageLogic()
{
	UAbilityTask_WaitGameplayEvent* WaitForHitEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, WarriorGameplayTags::Shared_Event_MeleeHit, nullptr);
	WaitForHitEvent->EventReceived.AddDynamic(this, &ThisClass::OnMeleeHitEvent);
	WaitForHitEvent->ReadyForActivation();

	UsedComboIndex = CurrentComboIndex;
	CurrentComboIndex = (CurrentComboIndex + 1) % AttackMontages.Num();
}

void UWarriorHeroMeleeAttack::OnAbilityCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);

	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(ResetComboTimer, ResetComboTimerDelegate, 1.f, false, 0.5f);	
	}
}

void UWarriorHeroMeleeAttack::OnAbilityCancelled()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);

	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(ResetComboTimer, ResetComboTimerDelegate, 1.f, false, 0.5f);	
	}
}

void UWarriorHeroMeleeAttack::OnMeleeHitEvent(FGameplayEventData Payload)
{
	Debug::Print(FString::Printf(TEXT("Melee hit event received: %s, Combo Count: %i"), *Payload.Target->GetActorLabel(), UsedComboIndex));
}

void UWarriorHeroMeleeAttack::OnResetComboTimer()
{
	CurrentComboIndex = 0;
}
