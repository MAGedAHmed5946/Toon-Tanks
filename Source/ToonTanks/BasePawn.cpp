// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	BaseMesh->SetupAttachment(CapsuleComponent);
	Turret = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	Turret->SetupAttachment(BaseMesh);
	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Projectile"));
	SpawnPoint->SetupAttachment(Turret);
}


void ABasePawn::RotateTurret(FVector TargetLocation)
{
	FVector LookAtLocation = TargetLocation - Turret->GetComponentLocation();
	FRotator TurretRotation = FRotator(0.0f,LookAtLocation.Rotation().Yaw,0.0f);
	Turret->SetWorldRotation(FMath::RInterpTo(Turret->GetComponentRotation(),
	TurretRotation,
	UGameplayStatics::GetWorldDeltaSeconds(this),
	5.0f)
	);
}
void ABasePawn::Fire()
{
	FVector SpawnPointLocation =  SpawnPoint->GetComponentLocation();
	FRotator SpawnRotation = SpawnPoint->GetComponentRotation();
    AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,SpawnPointLocation,SpawnRotation) ;
	Projectile->SetOwner(this);
	if(FireSFX)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSFX, GetActorLocation());

	}
}
void ABasePawn::HandleDestruction()
{
	//Handl SFX and VFX
	if(DeathVFX&&DeathSFX){
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathVFX, GetActorLocation(), GetActorRotation());
	UGameplayStatics::PlaySoundAtLocation(this, DeathSFX, GetActorLocation());
	}
	if(DeathCameraShakecClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakecClass);
	}
}