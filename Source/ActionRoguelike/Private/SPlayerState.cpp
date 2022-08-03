// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

#include "SSaveGame.h"

ASPlayerState::ASPlayerState()
{
	UE_LOG(LogTemp, Log, TEXT("SPlayerState created successfully!"));
}

int ASPlayerState::getNumberOfCredits_Implementation()
{
	return Credits;
}

void ASPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void ASPlayerState::SavePlayerState_Implementation(USSaveGame* SaveObject)
{
	if (SaveObject)
	{
		SaveObject->Credits = Credits;
	}
}

void ASPlayerState::LoadPlayerState_Implementation(USSaveGame* SaveObject)
{
	if (SaveObject)
	{
		Credits = SaveObject->Credits;
	}
}

void ASPlayerState::AddCredits_Implementation(int Delta)
{
	Credits += Delta;
	
	OnCreditsChanged.Broadcast(Credits, GetPlayerController()->PlayerState);
}

void ASPlayerState::RemoveCredits_Implementation(int Delta)
{
	Credits -= Delta;
	
	OnCreditsChanged.Broadcast(Credits, GetPlayerController()->PlayerState);
}

