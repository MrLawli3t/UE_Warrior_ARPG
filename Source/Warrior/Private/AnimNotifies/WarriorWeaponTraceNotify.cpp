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

	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(MeshComp->GetOwner()))
	{
		Debug::Print(PawnCombatInterface->GetPawnCombatComponent()->GetCurrentEquippedWeapon()->GetActorLabel());
	}
}
