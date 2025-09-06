// Lawliet Studios All Rights Reserved


#include "AbilitySystem/Abilities/WarriorHeroLightAttack.h"

#include "WarriorFunctionLibrary.h"
#include "WarriorGameplayTags.h"
#include "Characters/WarriorHeroCharacter.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

void UWarriorHeroLightAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                              const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	ResetComboTimerDelegate.BindUObject(this, &UWarriorHeroLightAttack::OnResetComboTimer);

	UWarriorFunctionLibrary::RemoveGameplayTagFromActor(GetHeroCharacterFromActorInfo(), WarriorGameplayTags::Player_Status_JumpToFinisher);

	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(ResetComboTimer);
	}

	if (UAnimMontage* Montage = AttackMontages[ComboIndex])
	{
		UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this,
			FName(""),
			Montage
		);

		MontageTask->OnCompleted.AddDynamic(this, &UWarriorHeroLightAttack::OnAbilityCompleted);
		MontageTask->OnBlendOut.AddDynamic(this, &UWarriorHeroLightAttack::OnAbilityCompleted);
		MontageTask->OnInterrupted.AddDynamic(this, &UWarriorHeroLightAttack::OnAbilityCancelled);
		MontageTask->OnCancelled.AddDynamic(this, &UWarriorHeroLightAttack::OnAbilityCancelled);

		MontageTask->ReadyForActivation();
	}

	if (ComboIndex + 2 == AttackMontages.Num())
	{
		UWarriorFunctionLibrary::AddGameplayTagToActor(GetHeroCharacterFromActorInfo(), WarriorGameplayTags::Player_Status_JumpToFinisher);
	}

	ComboIndex = (ComboIndex + 1) % AttackMontages.Num();
}

void UWarriorHeroLightAttack::OnAbilityCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);

	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(ResetComboTimer, ResetComboTimerDelegate, 1.f, false, 0.5f);	
	}
}

void UWarriorHeroLightAttack::OnAbilityCancelled()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);

	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(ResetComboTimer, ResetComboTimerDelegate, 1.f, false, 0.5f);	
	}
}

void UWarriorHeroLightAttack::OnResetComboTimer()
{
	ComboIndex = 0;
	UWarriorFunctionLibrary::RemoveGameplayTagFromActor(GetHeroCharacterFromActorInfo(), WarriorGameplayTags::Player_Status_JumpToFinisher);
}
