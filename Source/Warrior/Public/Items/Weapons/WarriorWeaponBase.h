// Lawliet Studios All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarriorWeaponBase.generated.h"

class UBoxComponent;

DECLARE_DELEGATE_OneParam(FTargetHitSignature, AActor* HitActor);

UCLASS()
class WARRIOR_API AWarriorWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWarriorWeaponBase();

	void WeaponTrace();
	void OnWeaponTraceEnd();

	FTargetHitSignature HitActorDelegate;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UStaticMeshComponent* WeaponMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UBoxComponent* WeaponBox = nullptr;

private:
	FVector PreviousTraceLocation = FVector::ZeroVector;

	TSet<AActor*> HitActors;

public:
	FORCEINLINE UBoxComponent* GetWeaponBox() const { return WeaponBox; }

};
