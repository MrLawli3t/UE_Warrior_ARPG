// Lawliet Studios All Rights Reserved


#include "AbilitySystem/Abilities/WarriorHeroLightAttack.h"

#include "WarriorFunctionLibrary.h"
#include "WarriorGameplayTags.h"
#include "Characters/WarriorHeroCharacter.h"

void UWarriorHeroLightAttack::PostMontageLogic()
{
	if (CurrentComboIndex + 2 == AttackMontages.Num())
	{
		UWarriorFunctionLibrary::AddGameplayTagToActor(GetHeroCharacterFromActorInfo(), WarriorGameplayTags::Player_Status_JumpToFinisher);
	}
	
	Super::PostMontageLogic();
}

void UWarriorHeroLightAttack::OnResetComboTimer()
{
	Super::OnResetComboTimer();
	
	UWarriorFunctionLibrary::RemoveGameplayTagFromActor(GetHeroCharacterFromActorInfo(), WarriorGameplayTags::Player_Status_JumpToFinisher);
}
