// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"


ATank::ATank()
{
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
    SpringArmComp->SetupAttachment(RootComponent);
    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
    CameraComp->SetupAttachment(SpringArmComp);
}
void ATank::BeginPlay()
{ 
	Super::BeginPlay();
    TankPlayerController = Cast<APlayerController>(GetController());
}
// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(TankPlayerController)
    {
        FHitResult  HitResult;
        TankPlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
        RotateTurret(HitResult.ImpactPoint);
    }
}
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"),this,&ATank::Turn);

    PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed,this,&ATank::Fire);
}
void ATank::Move(float Move)
{
    FVector DeltaLocation(0.0f);
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    DeltaLocation.X = Move*DeltaTime*Speed;
    this->AddActorLocalOffset(DeltaLocation,true);
}
void ATank::Turn(float Turn)
{
    FRotator DeltaRotator(0.0f);
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    DeltaRotator.Yaw = Turn*DeltaTime*TurnRate;
    this->AddActorLocalRotation(DeltaRotator,true);
}

void ATank::Fire()
{
    Super::Fire();
}
void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    IsAlive = false;
    //SFX VFX
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}