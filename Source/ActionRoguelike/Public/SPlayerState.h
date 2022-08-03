// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

class USSaveGame;
class USaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCreditsChanged, int, Credits, APlayerState*, PlayerState);

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
	void AddCredits(int Delta);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RemoveCredits(int Delta);

	UPROPERTY(BlueprintAssignable)
	FOnCreditsChanged OnCreditsChanged;

	UFUNCTION(BlueprintNativeEvent)
	void SavePlayerState(USSaveGame* SaveObject);
	
	UFUNCTION(BlueprintNativeEvent)
	void LoadPlayerState(USSaveGame* SaveObject);
};
