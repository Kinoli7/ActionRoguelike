// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SAttributeComponent.h"
#include "SItemPotion.generated.h"

// DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FPotionHeal, AActor*, InstigatorActor, USAttributeComponent*, OwningComp, float, NewHealth, float, Delta);

UCLASS()
class ACTIONROGUELIKE_API ASItemPotion : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASItemPotion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly)
	float PotionCooldownTimerSeconds;
	
	UPROPERTY()
	FTimerHandle TimerHandle_PotionCooldown;

	void ResetPotionTimer();

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(APawn* InstigatorPawn) override;
};
