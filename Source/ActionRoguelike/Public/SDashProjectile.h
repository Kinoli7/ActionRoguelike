// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectile.h"
#include "SDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASDashProjectile : public ASProjectile
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASDashProjectile();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float TeleportDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float DetonateDelay;

	// Handle to cancel the time if we are hitting something
	FTimerHandle TimerHandle_DelayedDetonate;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void Explode_Implementation() override;
	
	void TeleportInstigator();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
