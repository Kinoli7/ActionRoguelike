// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

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

	Credits = 0;
}

void ASPlayerState::AddCredits_Implementation(int Delta)
{
	Credits += Delta;
	
	OnCreditsChanged.Broadcast(Credits);
}

void ASPlayerState::RemoveCredits_Implementation(int Delta)
{
	Credits -= Delta;
	
	OnCreditsChanged.Broadcast(Credits);
}

