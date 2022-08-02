// Fill out your copyright notice in the Description page of Project Settings.


#include "SProjectile.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASProjectile::ASProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	SphereComp->OnComponentHit.AddDynamic(this, &ASProjectile::OnActorHit);

	MagicProjectileLoopAudio = CreateDefaultSubobject<UAudioComponent>("MagicProjectileLoopAudio");
	MagicProjectileLoopAudio->SetupAttachment(SphereComp);
	
	MagicProjectileExplosionAudio = CreateDefaultSubobject<UAudioComponent>("MagicProjectileExplosionAudio");
	MagicProjectileExplosionAudio->SetupAttachment(SphereComp);

	SetReplicates(true);
}

// Called when the game starts or when spawned
void ASProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASProjectile::OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void ASProjectile::Explode_Implementation()
{
	if(ensure(IsValid(this)))
	{
		MagicProjectileLoopAudio->Stop();
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), MagicProjectileExplosionAudio->Sound, GetActorLocation());
		Destroy();
	}
	
}

// Called every frame
void ASProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

