// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTankPlayerController.h"
#include "TimerManager.h"

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
    StartGame();
    TowersCount = GetTowersCount();
}


void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    if(DeadActor == Tank){
        Tank->HandleDestruction();
        if(TankPlayerController)
        {
            TankPlayerController->SetPlayerEnableState(false);
            GameOver(false);
        }
    }else if(ATower* DeadTower = Cast<ATower>(DeadActor))
    {
        DeadTower->HandleDestruction();
        TowersCount --;
        if(TowersCount <=0){
            GameOver(true);
        }
    }
}
void AToonTanksGameMode::HandleGameStart()
{
    Tank =Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
    TankPlayerController =Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this,0));
    FTimerHandle PlayerEnabledTimeHandler;

    if(TankPlayerController)
    {
        TankPlayerController->SetPlayerEnableState(false);
        UE_LOG(LogTemp, Warning, TEXT("I'm heeeeereeeeeeeee"));
        FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(TankPlayerController,&AToonTankPlayerController::SetPlayerEnableState,true);
        GetWorldTimerManager().SetTimer(PlayerEnabledTimeHandler, TimerDelegate, StartDelay, false);
    }
}
int32 AToonTanksGameMode::GetTowersCount()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(),Towers);
    return Towers.Num();
}
