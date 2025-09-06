// Lawliet Studios All Rights Reserved


#include "Items/Weapons/WarriorWeaponBase.h"

#include "WarriorDebugHelper.h"
#include "Components/BoxComponent.h"

AWarriorWeaponBase::AWarriorWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponBox"));
	WeaponBox->SetupAttachment(GetRootComponent());
	WeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AWarriorWeaponBase::WeaponTrace()
{
	checkf(GetInstigator(), TEXT("Weapon does not have an instigator"))
	
	if (!WeaponBox) return;
	const FVector CurrentTraceLocation = WeaponBox->GetComponentLocation();

	if (PreviousTraceLocation.IsZero()) PreviousTraceLocation = CurrentTraceLocation;

	TArray<FHitResult> HitResults;

	FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(WeaponTrace), false);
	QueryParams.AddIgnoredActors(TArray<AActor*>({this, GetInstigator()}));

	DrawDebugLine(GetWorld(), PreviousTraceLocation, CurrentTraceLocation, FColor(255, 0, 0, 100), false, 1.f, 0, 50.f);
	if (GetWorld()->SweepMultiByChannel(
		HitResults,
		PreviousTraceLocation,
		CurrentTraceLocation,
		WeaponBox->GetComponentQuat(),
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeBox(WeaponBox->GetScaledBoxExtent()),
		QueryParams
	))
	{
		for (const FHitResult HitResult : HitResults)
		{
			AActor* HitActor = HitResult.GetActor();
			
			if (HitActor && !HitActors.Contains(HitActor))
			{
				HitActors.Add(HitActor);
				HitActorDelegate.ExecuteIfBound(HitActor);
			}
		}
	}

	PreviousTraceLocation = CurrentTraceLocation;
}

void AWarriorWeaponBase::OnWeaponTraceEnd()
{
	HitActors.Empty();
	PreviousTraceLocation = FVector::ZeroVector;
}


