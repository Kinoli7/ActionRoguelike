// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComp, float, NewHealth, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnRageChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComp, float, NewRage, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComponent();

	UFUNCTION(BlueprintCallable, Category="Attribute")
	static USAttributeComponent* GetAttributes(AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category="Attribute", meta=(DisplayName="IsAlive"))
	static bool IsActorAlive(AActor* Actor);

	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly, Meta = (ExposeOnSpawn = true), Replicated, Category="Attributes")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category="Attributes")
	float HealthMax = 1.0f;

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	float Rage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	float MaxRage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	bool bIsRageFull;

	UFUNCTION(NetMulticast, Reliable) // @FIXME: mark as unreliable once we moved the 'state' out of scharacter
	void MulticastHealthChanged(AActor* InstigatorActor, float NewHealth, float Delta);
	
public:

	UFUNCTION(BlueprintCallable)
	bool Kill(AActor* InstigatorActor);
	
	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnRageChanged OnRageChanged;

	bool IsFullHealth() const;
	
	float GetHealthMax() const;
	
	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor, float Delta);

	UFUNCTION()
	float GetActualHealth();

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool ApplyRageChange(float Delta);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool UseAmountRage(float AmountRage);

};
