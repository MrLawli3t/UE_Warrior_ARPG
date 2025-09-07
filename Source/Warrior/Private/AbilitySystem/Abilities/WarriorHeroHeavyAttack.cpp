// Lawliet Studios All Rights Reserved


#include "AbilitySystem/Abilities/WarriorHeroHeavyAttack.h"

#include "WarriorDebugHelper.h"
#include "WarriorFunctionLibrary.h"
#include "WarriorGameplayTags.h"
#include "Characters/WarriorHeroCharacter.h"

void UWarriorHeroHeavyAttack::PreMontageLogic()
{
	if (UWarriorFunctionLibrary::NativeDoesActorHaveTag(GetHeroCharacterFromActorInfo(), WarriorGameplayTags::Player_Status_JumpToFinisher))
	{
		CurrentComboIndex = AttackMontages.Num()-1;
		Debug::Print(FString::Printf(TEXT("Jumping to finisher. Current Combo Index: %i"), CurrentComboIndex));
		UWarriorFunctionLibrary::RemoveGameplayTagFromActor(GetHeroCharacterFromActorInfo(), WarriorGameplayTags::Player_Status_JumpToFinisher);
	}
	
	Super::PreMontageLogic();
}
