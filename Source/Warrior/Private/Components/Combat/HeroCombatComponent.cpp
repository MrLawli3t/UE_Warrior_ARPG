// Lawliet Studios All Rights Reserved


#include "Components/Combat/HeroCombatComponent.h"


UHeroCombatComponent::UHeroCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UHeroCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UHeroCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

