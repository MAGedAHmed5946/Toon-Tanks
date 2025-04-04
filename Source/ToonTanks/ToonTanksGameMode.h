// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	
	void ActorDied(AActor* DeadActor);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWinGame);
private:
	class ATank* Tank;
	class AToonTankPlayerController* TankPlayerController;

	float StartDelay = 3.f;

	void HandleGameStart();

	int32 TowersCount;

	int32 GetTowersCount();
	
};
