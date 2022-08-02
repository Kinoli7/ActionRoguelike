// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

#include <algorithm>

#include "SGameModeBase.h"
#include "Net/UnrealNetwork.h"

static TAutoConsoleVariable<float> CVarDamageMultiplayer(TEXT("su.DamageMultiplier"), 1.0f, TEXT("Global Damage Modifier for Attribute Component"), ECVF_Cheat);

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	SetIsReplicatedByDefault(true);
}

bool USAttributeComponent::IsFullHealth() const
{
	return HealthMax == Health;
}

float USAttributeComponent::GetHealthMax() const
{
	return HealthMax;
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged() && Delta < 0.0f)
	{
		return false;
	}

	if (Delta < 0.0f)
	{
		float DamageMultiplier = CVarDamageMultiplayer.GetValueOnGameThread();

		Delta *= DamageMultiplier;

		ApplyRageChange(Delta);
	}
	
	float OldHealth = Health;

	Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);

	float ActualDelta = Health - OldHealth;
	if (ActualDelta != 0.f)
	{
		MulticastHealthChanged(InstigatorActor, Health, ActualDelta);
	}
	// OnHealthChanged.Broadcast(nullptr, this, Health, Delta);
	

	// Died
	if (ActualDelta < 0.0f && Health == 0.0f)
	{
		ASGameModeBase* GM = GetWorld()->GetAuthGameMode<ASGameModeBase>();
		if(GM)
		{
			GM->OnActorKilled(GetOwner(), InstigatorActor);
		}
	}
	
	return ActualDelta != 0;
}

USAttributeComponent* USAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	}

	return nullptr;
}

bool USAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -GetHealthMax());
}


bool USAttributeComponent::IsActorAlive(AActor* Actor)
{
	USAttributeComponent* AttributeComp = GetAttributes(Actor);
	if (AttributeComp)
	{
		return AttributeComp->IsAlive();
	}

	return false;
}

void USAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = HealthMax;

	Rage = 0.f;
	bIsRageFull = false;
}

float USAttributeComponent::GetActualHealth()
{
	return Health;
}

bool USAttributeComponent::ApplyRageChange(float Delta)
{
	Rage += abs(Delta) + FMath::RandRange(0.0f, 10.0f);
	Rage = std::clamp(Rage, 0.f, MaxRage);

	FString DebugMsg = "RageValue: " + FString::SanitizeFloat(Rage);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, DebugMsg);

	OnRageChanged.Broadcast(nullptr, this, Rage, Delta);

	return true;
}

bool USAttributeComponent::UseAmountRage_Implementation(float AmountRage)
{
	if (Rage >= AmountRage)
	{
		Rage -= AmountRage;
		OnRageChanged.Broadcast(nullptr, this, Rage, -AmountRage);
		return true;
	}

	return false;
}

void USAttributeComponent::MulticastHealthChanged_Implementation(AActor* InstigatorActor, float NewHealth, float Delta)
{
	OnHealthChanged.Broadcast(InstigatorActor, this, NewHealth, Delta);
}

void USAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USAttributeComponent, Health);
	DOREPLIFETIME(USAttributeComponent, HealthMax);
	// DOREPLIFETIME_CONDITION(USAttributeComponent, HealthMax, COND_OwnerOnly);
}