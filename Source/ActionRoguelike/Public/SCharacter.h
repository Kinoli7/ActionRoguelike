// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../Plugins/Developer/RiderLink/Source/RD/src/rd_core_cpp/src/main/types/Void.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class UAnimMontage;
class USAttributeComponent;
class UParticleSystem;
class USActionComponent;

static TAutoConsoleVariable<bool> CVarDebugDrawAttack(TEXT("su.AttackDebugDraw"), false, TEXT("Enable Debug Lines for Attack Component."), ECVF_Cheat);

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();
	
protected:

	UPROPERTY(VisibleAnywhere);
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere);
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere);
	USInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components");
	USAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components");
	USActionComponent* ActionComp;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float value);

	void MoveRight(float value);

	void SprintStart();

	void SprintStop();

	void PrimaryAttack();

	void DashProjectile();
	
	void BlackHoleAttack();

	void PrimaryInteract();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;

	virtual FVector GetPawnViewLocation() const override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Exec)
	void HealSelf(float Amount = 100);
};
