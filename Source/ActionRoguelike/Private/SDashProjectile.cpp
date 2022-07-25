// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASDashProjectile::ASDashProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &ASDashProjectile::Explode, DetonateDelay);
	
}

void ASDashProjectile::Explode_Implementation()
{
	//Super::Explode_Implementation();
	
	if(ensure(IsValid(this)))
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);
		// Exploding animation
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
		EffectComp->DeactivateSystem();

		// Stop movement of projectile
		MovementComp->StopMovementImmediately();
		SetActorEnableCollision(false);

		// Wait 0.2 seconds
		FTimerHandle TimerHandle_DelayedTeleport;
		GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ASDashProjectile::TeleportInstigator, TeleportDelay);

		// Destroys
		//Destroy();
	}
}

void ASDashProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();
	if (ensure(ActorToTeleport))
	{
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);	
	}
}

// Called every frame
void ASDashProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

