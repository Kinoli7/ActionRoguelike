// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Particles/ParticleSystemComponent.h>
#include "SProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class ACTIONROGUELIKE_API ASProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASProjectile();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ImpactVFX;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* EffectComp;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();

	void OnActorHit(AActor OnActorHit, AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
