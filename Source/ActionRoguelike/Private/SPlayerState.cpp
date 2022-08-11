// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

#include "SSaveGame.h"
#include "Net/UnrealNetwork.h"

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
		// Credits = SaveObject->Credits;
		// Makes sure we trigger credits changed event
		AddCredits(SaveObject->Credits);
	}
}

void ASPlayerState::OnRep_Credits(int OldCredits)
{
	OnCreditsChanged.Broadcast(this, Credits, Credits - OldCredits);
}

void ASPlayerState::AddCredits_Implementation(int Delta)
{
	Credits += Delta;
	
	OnCreditsChanged.Broadcast(this, Credits, Delta);
}

void ASPlayerState::RemoveCredits_Implementation(int Delta)
{
	Credits -= Delta;
	
	OnCreditsChanged.Broadcast(this, Credits, Delta);
}

void ASPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASPlayerState, Credits);
}