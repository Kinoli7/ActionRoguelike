// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerupActor.h"
#include "SPowerup_Coin.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPowerup_Coin : public ASPowerupActor
{
	GENERATED_BODY()

public:
	ASPowerup_Coin();

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult);

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

};
