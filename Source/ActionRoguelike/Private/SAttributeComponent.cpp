// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	Health = 100;
}

bool USAttributeComponent::IsFullHealth() const
{
	return HealthMax == Health;
}

float USAttributeComponent::GetHealthMax() const
{
	return HealthMax;
}

bool USAttributeComponent::ApplyHealthChange(float Delta)
{
		float OldHealth = Health;

		Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);

		float ActualDelta = Health - OldHealth;
		OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

		return ActualDelta != 0;
}
