// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Projectile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	RootComponent = Projectile;
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	MovementComponent->InitialSpeed = 1300.f;
	MovementComponent->MaxSpeed = 1300.f;
	TrailingVFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trailing"));
	TrailingVFX->SetupAttachment(Projectile);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	Projectile->OnComponentHit.AddDynamic(this,&AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp,AActor* OtherActor,UPrimitiveComponent* OtherComponent,FVector NormalImpulse,const FHitResult& Hit)
{
	auto MyOwner = GetOwner();
    if(MyOwner == nullptr)
	{
		Destroy();
		return;
	}
    auto MyOwnerInstigator = MyOwner->GetInstigatorController();
    auto DamageType = UDamageType::StaticClass();
    if(OtherActor&& OtherActor!=this&& OtherActor!= MyOwner)
    {
        UGameplayStatics::ApplyDamage(OtherActor,Damage,MyOwnerInstigator,this,DamageType);
		if(HitVFX&&HitSFX){
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitVFX, GetActorLocation(), GetActorRotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSFX, GetActorLocation());
		}
		if(HitCameraShakecClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakecClass);
		}
		Destroy();
    }
	Destroy();
}
