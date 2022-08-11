// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

class USSaveGame;
class USaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged, ASPlayerState*, PlayerState, int, Credits, int, Delta);

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
	UPROPERTY(VisibleAnywhere, ReplicatedUsing="OnRep_Credits")
	int Credits;

	virtual void BeginPlay() override;

	// OnRep_ can use a parameter containing the 'old value' of the variable it is bound to. Very useful in this case to figure the 'delta'.
	UFUNCTION()
	void OnRep_Credits(int OldCredits);
	
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
