// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerup_HealthPotion.h"

#include "SAttributeComponent.h"
#include "SPlayerState.h"
#include "Kismet/GameplayStatics.h"

class USAttributeComponent;
// Sets default values
ASPowerup_HealthPotion::ASPowerup_HealthPotion()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);

	PotionHealthValue = 50.f;
}

void ASPowerup_HealthPotion::ResetPotionTimer()
{
	MeshComp->SetVisibility(true);
	GetWorldTimerManager().ClearTimer(TimerHandle_PotionCooldown);
}

void ASPowerup_HealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	USAttributeComponent* AttributeComp = Cast<USAttributeComponent> (InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
	ASPlayerState* MyPlayerState = Cast<ASPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(),0));
	if (ensure(AttributeComp) && !AttributeComp->IsFullHealth() && MyPlayerState->getNumberOfCredits() >= CreditCost)
	{
		if (AttributeComp->ApplyHealthChange(this, PotionHealthValue))
		{
			MyPlayerState->RemoveCredits(CreditCost);
			IsPowerupActivated = true;
			OnRep_HideAndCooldownPowerup();
		}
	}
}
