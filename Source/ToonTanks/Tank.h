// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	ATank();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(float Move);
	void Turn(float Turn);
	APlayerController* GetTankPlayerController(){return TankPlayerController;}
	void HandleDestruction();
	bool IsAlive = true;
	
protected:
// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Fire() override;

public:	
// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category="Camera Components",meta = (AllowPrivateAccess="true"))
	class UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category="Camera Components",meta = (AllowPrivateAccess="true"))
	class USpringArmComponent* SpringArmComp;
	UPROPERTY(EditAnyWhere)
	float Speed = 300.0f;
	UPROPERTY(EditAnyWhere)
	float TurnRate = 50.0f;

	APlayerController* TankPlayerController ;
};
