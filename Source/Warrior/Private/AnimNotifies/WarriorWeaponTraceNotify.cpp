// Lawliet Studios All Rights Reserved


#include "AnimNotifies/WarriorWeaponTraceNotify.h"

#include "WarriorDebugHelper.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Items/Weapons/WarriorWeaponBase.h"

void UWarriorWeaponTraceNotify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
                                           const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (!MeshComp) return;

	if (AWarriorWeaponBase* Weapon = GetWarriorWeaponFromMesh(MeshComp))
	{
		Weapon->WeaponTrace();
	}
}

void UWarriorWeaponTraceNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (!MeshComp) return;

	if (AWarriorWeaponBase* Weapon = GetWarriorWeaponFromMesh(MeshComp))
	{
		Weapon->OnWeaponTraceEnd();
	}
}

AWarriorWeaponBase* UWarriorWeaponTraceNotify::GetWarriorWeaponFromMesh(const USkeletalMeshComponent* MeshComp)
{
	if (!MeshComp) return nullptr;

	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(MeshComp->GetOwner()))
	{
		if (AWarriorWeaponBase* Weapon = PawnCombatInterface->GetPawnCombatComponent()->GetCurrentEquippedWeapon())
		{
			return Weapon;
		}
	}

	return nullptr;
}
