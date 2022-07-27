// Fill out your copyright notice in the Description page of Project Settings.


#include "SCoin.h"
#include "SPlayerState.h"

// Sets default values
ASCoin::ASCoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(RootComponent);
	
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASCoin::OnActorOverlap);

}

// Called when the game starts or when spawned
void ASCoin::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASCoin::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (OtherActor == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		GetWorld()->GetFirstPlayerController()->GetPlayerState<ASPlayerState>()->addCredits(1);
	}
}

// Called every frame
void ASCoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

