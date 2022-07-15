// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemPotion.h"

// Sets default values
ASItemPotion::ASItemPotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void ASItemPotion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASItemPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASItemPotion::ResetPotionTimer()
{
	MeshComp->SetVisibility(true);
	GetWorldTimerManager().ClearTimer(TimerHandle_PotionCooldown);
}

void ASItemPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!TimerHandle_PotionCooldown.IsValid())
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent> (InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
		AttributeComp->ApplyHealthChange(50.0f);

		MeshComp->SetVisibility(false);

		// Wait 10 seconds
		GetWorldTimerManager().SetTimer(TimerHandle_PotionCooldown, this, &ASItemPotion::ResetPotionTimer, PotionCooldownTimerSeconds, false);
	}
}
