// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"
class USoundBase;

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	void HandleDestruction();
protected:
	void RotateTurret(FVector TargetLocation);
	virtual void Fire();
private:
	UPROPERTY(VisibleAnyWhere,Category = "Components",BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnyWhere,Category = "Components",BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnyWhere,Category = "Components",BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Turret;
	UPROPERTY(VisibleAnyWhere,Category = "Components",BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	USceneComponent* SpawnPoint;

	UPROPERTY(EditDefaultsOnly,Category ="Compat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnyWhere,Category ="Compat")
	class UParticleSystem* DeathVFX;
	
	UPROPERTY(EditAnyWhere,Category ="Compat")
	USoundBase* DeathSFX;
	UPROPERTY(EditAnyWhere,Category ="Compat")
	USoundBase* FireSFX;
	
	UPROPERTY(EditAnyWhere,Category = "FX")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakecClass;
};
