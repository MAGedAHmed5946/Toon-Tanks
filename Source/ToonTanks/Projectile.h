// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"
class USoundBase;
UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//UFUNCTION(BlueprintImplementableEvent)


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditDefaultsOnly,Category = "Projectile",BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Projectile;
	UPROPERTY(EditDefaultsOnly,Category = "Movement")
	class UProjectileMovementComponent* MovementComponent;
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp,AActor* OtherActor,UPrimitiveComponent* OtherComponent,FVector NormalImpulse,const FHitResult& Hit);
	UPROPERTY(EditAnyWhere)
	float Damage =50.f;
	UPROPERTY(EditAnyWhere)
	class UParticleSystem* HitVFX;

	UPROPERTY(EditAnyWhere,Category = "FX")
	class UParticleSystemComponent* TrailingVFX;
	UPROPERTY(EditAnyWhere,Category = "FX")
	USoundBase* HitSFX;
	UPROPERTY(EditAnyWhere,Category = "FX")
	TSubclassOf<class UCameraShakeBase> HitCameraShakecClass;
};
