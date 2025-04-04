// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankPlayerController.h"
#include "BasePawn.generated.h"

void AToonTankPlayerController::SetPlayerEnableState(bool Enabled)
{
    if(Enabled)
    {
        GetPawn()->EnableInput(this);
    }else{
        GetPawn()->DisableInput(this);
    }
    bShowMouseCursor = Enabled;
}

