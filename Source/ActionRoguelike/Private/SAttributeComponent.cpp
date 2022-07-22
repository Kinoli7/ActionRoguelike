// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	HealthMax = Health = 100;
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
	if (!GetOwner()->CanBeDamaged())
	{
		return false;
	}
	
	float OldHealth = Health;

	Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);

	float ActualDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

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

float USAttributeComponent::GetActualHealth()
{
	return Health;
}
