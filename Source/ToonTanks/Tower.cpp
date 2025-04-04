// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ATower::ATower()
{

}

void ATower::BeginPlay()
{
    Super::BeginPlay();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
    GetWorldTimerManager().SetTimer(TimeHandler, this, &ATower::CheckFireCondition, 2.f, true);
}
void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if(InFireRange())
    {
        RotateTurret(Tank->GetActorLocation());
    }
}
void ATower::CheckFireCondition()
{
    if (InFireRange()&&Tank->IsAlive)
    {
        Fire();
    }
    
}
bool ATower::InFireRange()
{
    if(Tank){
        float Distance = FVector::Dist(this->GetActorLocation(),Tank->GetActorLocation());
        if(Distance<=Range)
        {
            return true;
        }
    }
    return false;
}
void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}
