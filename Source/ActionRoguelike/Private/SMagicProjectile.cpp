// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"

#include "SAction.h"
#include "SActionComponent.h"
#include "SAttributeComponent.h"
#include "SGameplayFunctionLibrary.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);

	InitialLifeSpan = 10.0f;
}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// Other way of doing tag comparison
	//static FGameplayTag Tag = FGameplayTag::RequestGameplayTag("Status.Parrying");
	
	USActionComponent* ActionComp = Cast<USActionComponent>(OtherActor->GetComponentByClass(USActionComponent::StaticClass()));
	if (ActionComp && ActionComp->ActiveGameplayTags.HasTag(ParryTag))
	{
		MovementComp->Velocity = -MovementComp->Velocity;

		SetInstigator(Cast<APawn>(OtherActor));
		return;
	}
	
	AActor* AInstigator = GetInstigator();
	if ((OtherActor && OtherActor != AInstigator) && USGameplayFunctionLibrary::ApplyDirectionalDamage(AInstigator, OtherActor, Damage, SweepResult))
	{
		Explode();

		if (ActionComp && HasAuthority())
		{
			ActionComp->AddAction(GetInstigator(), BurningActionClass);
		}
	}
}


// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

