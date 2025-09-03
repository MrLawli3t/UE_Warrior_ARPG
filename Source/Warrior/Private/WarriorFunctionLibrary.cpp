// Lawliet Studios All Rights Reserved


#include "WarriorFunctionLibrary.h"

#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemGlobals.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "Interfaces/PawnCombatInterface.h"

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

bool UWarriorFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, const FGameplayTag Tag)
{
	const UWarriorAbilitySystemComponent* WarriorASC = NativeGetWarriorASCFromActor(InActor);

	return WarriorASC->HasMatchingGameplayTag(Tag);
}

void UWarriorFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, const FGameplayTag Tag, bool& OutBool)
{
	NativeDoesActorHaveTag(InActor, Tag) ? OutBool = true : OutBool = false;
}

UPawnCombatComponent* UWarriorFunctionLibrary::NativeGetPawnCombatComponent(AActor* InActor)
{
	check(InActor);

	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

UPawnCombatComponent* UWarriorFunctionLibrary::BP_GetPawnCombatComponent(AActor* InActor, EWarriorValidType OutValidType)
{
	UPawnCombatComponent* PawnCombatComponent = NativeGetPawnCombatComponent(InActor);
	
	OutValidType = PawnCombatComponent ? EWarriorValidType::Valid : EWarriorValidType::Invalid;
	
	return PawnCombatComponent;
}
