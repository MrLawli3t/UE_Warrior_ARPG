// Lawliet Studios All Rights Reserved


#include "WarriorFunctionLibrary.h"

#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemGlobals.h"

UWarriorAbilitySystemComponent* UWarriorFunctionLibrary::NativeGetWarriorASCFromActor(const AActor* InActor)
{
	check(InActor);

	return CastChecked<UWarriorAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(InActor));
	
}

void UWarriorFunctionLibrary::AddGameplayTagToActor(AActor* InActor, FGameplayTag Tag)
{
	UWarriorAbilitySystemComponent* WarriorASC = NativeGetWarriorASCFromActor(InActor);

	if (!WarriorASC->HasMatchingGameplayTag(Tag))
	{
		WarriorASC->AddLooseGameplayTag(Tag);
	}
}

void UWarriorFunctionLibrary::RemoveGameplayTagFromActor(AActor* InActor, FGameplayTag Tag)
{
	UWarriorAbilitySystemComponent* WarriorASC = NativeGetWarriorASCFromActor(InActor);

	if (WarriorASC->HasMatchingGameplayTag(Tag))
	{
		WarriorASC->RemoveLooseGameplayTag(Tag);
	}
}

bool UWarriorFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag Tag)
{
	UWarriorAbilitySystemComponent* WarriorASC = NativeGetWarriorASCFromActor(InActor);

	return WarriorASC->HasMatchingGameplayTag(Tag);
}

void UWarriorFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag Tag, bool& OutBool)
{
	NativeDoesActorHaveTag(InActor, Tag) ? OutBool = true : OutBool = false;
}