// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAddCoin);

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ASPlayerState();
	
protected:
	UPROPERTY(VisibleAnywhere)
	int Credits;

	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int getNumberOfCredits();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void addCredits(int Delta);
};
