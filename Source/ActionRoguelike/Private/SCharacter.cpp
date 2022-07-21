// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "DrawDebugHelpers.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "SInteractionComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PlayerController.h"
#include "SAttributeComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bApplyGravityWhileJumping = true;

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

	bUseControllerRotationYaw = false;
}


void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &ASCharacter::OnHealthChanged);
}


// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
// This is entirely optional, it draws two arrows to visualize rotations of the player
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// -- Rotation Visualization -- //
	const float DrawScale = 100.0f;
	const float Thickness = 5.0f;

	FVector LineStart = GetActorLocation();
	// Offset to the right of pawn
	LineStart += GetActorRightVector() * 100.0f;
	// Set line end in direction of the actor's forward
	FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
	// Draw Actor's Direction
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);

	FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
	// Draw 'Controller' Rotation ('PlayerController' that 'possessed' this character)
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("DashProjectile", IE_Pressed, this, &ASCharacter::DashProjectile);
}

void ASCharacter::HealSelf(float Amount /* = 100 */)
{
	AttributeComp->ApplyHealthChange(this, Amount);
}


void ASCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), Value);
}

void ASCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
}

void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnimMagicProjectile);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.2f);

	// If the character dies
	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	
	FHitResult OutHit;
	FVector EyeLocation;
	FRotator EyeRotation;
	FTransform SpawnTM;
	CameraComp->GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(EyeLocation, EyeRotation);
	FVector End = EyeLocation + (EyeRotation.Vector() * 10000);
	//ECollisionChannel TraceChannel;
	bool bRayCollided = GetWorld()->LineTraceSingleByObjectType(OutHit, EyeLocation, End, ObjectQueryParams);
	if (bRayCollided)
	{
		DrawDebugLine(GetWorld(), EyeLocation, End, FColor::Red, false, 2.0f, 0, 2.0f);
		
		FVector HitLocation = OutHit.ImpactPoint;
		FRotator MissileRotation = UKismetMathLibrary::FindLookAtRotation(HandLocation, HitLocation);

		DrawDebugSphere(GetWorld(), HitLocation, 10.0f, 16, FColor::Red, false, 2);
		
		SpawnTM = FTransform(MissileRotation, HandLocation);
	}
	else
	{
		SpawnTM = FTransform(GetControlRotation(), HandLocation);
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	MoveIgnoreActorAdd(GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams));
}

void ASCharacter::DashProjectile()
{
	PlayAnimMontage(AttackAnimDashProjectile);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::DashProjectile_TimeElapsed, 0.2f);
}

void ASCharacter::DashProjectile_TimeElapsed()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_02");
	
	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(DashProjectileClass, SpawnTM, SpawnParams);
}

void ASCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
	if (NewHealth <= 0.0f && Delta < 0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}
