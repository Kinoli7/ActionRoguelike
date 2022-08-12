// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerupActor.h"
#include "SPowerup_HealthPotion.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASPowerup_HealthPotion : public ASPowerupActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPowerup_HealthPotion();

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly)
	float PotionCooldownTimerSeconds;

	UPROPERTY(EditDefaultsOnly)
	float PotionHealthValue;
	
	UPROPERTY()
	FTimerHandle TimerHandle_PotionCooldown;

	UPROPERTY(EditAnywhere)
	int CreditCost;
	
	void ResetPotionTimer();

	
public:	
	void Interact_Implementation(APawn* InstigatorPawn) override;

	FText GetInteractText_Implementation(APawn* InstigatorPawn) override;
};
