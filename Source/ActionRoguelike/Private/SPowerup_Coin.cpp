// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerup_Coin.h"

#include "SPlayerState.h"
#include "Kismet/GameplayStatics.h"

ASPowerup_Coin::ASPowerup_Coin()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(RootComponent);

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASPowerup_Coin::OnActorOverlap);

}

void ASPowerup_Coin::ResetCoinTimer()
{
	MeshComp->SetVisibility(true);
	GetWorldTimerManager().ClearTimer(TimerHandle_CoinCooldown);
}

void ASPowerup_Coin::OnActorOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
	UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult)
{
	ASPlayerState* MyPlayerState = Cast<ASPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(),0));
	if ( UGameplayStatics::GetPlayerPawn(GetWorld(), 0) == Actor )
	{
		Cast<ASPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(),0))->AddCredits(CreditsToAdd);
		IsPowerupActivated = true;
		OnRep_HideAndCooldownPowerup();
	}
	
}
