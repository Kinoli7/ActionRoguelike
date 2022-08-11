// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SPowerupActor.generated.h"

class USphereComponent;

UCLASS()
class ACTIONROGUELIKE_API ASPowerupActor : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPowerupActor();

protected:
	
	UPROPERTY(EditAnywhere, Category="Powerup")
	float RespawnTime;

	FTimerHandle TimerHandle_RespawnTimer;

	UPROPERTY(ReplicatedUsing="OnRep_IsActive")
	bool bIsActive;

	UFUNCTION()
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnRep_IsActive();
	
	UFUNCTION()
	void ShowPowerup();

	UFUNCTION()
	void HideAndCooldownPowerup();

	UFUNCTION()
	void SetPowerupState(bool bNewIsActive);

	UPROPERTY(VisibleAnywhere, Category="Components")
	USphereComponent* SphereComp;

public:	
	void Interact_Implementation(APawn* InstigatorPawn) override;
	
};
