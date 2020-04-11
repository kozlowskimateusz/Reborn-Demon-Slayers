// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "PlayerCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine.h"

APlayerCharacter::APlayerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;


	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	/*
	WalkSpeed = GetCharacterMovement()->MaxWalkSpeed = 600.f;
	SprintSpeed = GetCharacterMovement()->MaxWalkSpeed = 1200.f;*/


	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	CurrentHealth = 0.5f;
	MaxHealth = 1.f;
	CurrentEnergy = 0.5f;
	MaxEnergy = 1.f;
	/*CurrentStamina = 0.5f;
	MaxStamina = 1.f;*/
	CurrentExp = 0;
	CurrentMaxExp = 200;
	BufferExp = 0;
	MaxExpMultiplier = 1.4f;
	CharacterLevel = 1;

	// Regeneration
	HealthRegenRate = 0.05f;
	StaminaRegenRate = 0.1f;
	EnergyRegenRate = 0.05f;

	//Move Speed
	bIsSprinting = false;
	StaminaSprintConsume = 1.f;
	WalkSpeed = 400.f;
	SprintSpeed = 2000.f;
}


//////////////////////////////////////////////////////////////////////////
// Input

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::StopSprint);
}



void APlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}



void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}


void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HealthRegeneration(DeltaTime);
	




	EnergyRegeneration(DeltaTime);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CalculateMaxExp();
}

float APlayerCharacter::GetCurrentEnergy()
{
	return CurrentEnergy;
}

float APlayerCharacter::GetMaxEnergy()
{
	return MaxEnergy;
}


float APlayerCharacter::GetDefensePower()
{
	return DefensePower;
}

float APlayerCharacter::GetAttackPower()
{
	return AttackPower;
}

float APlayerCharacter::SetHealth()
{
	return GetPerctentage(GetCurrentHealth(), GetMaxHealth());
}

float APlayerCharacter::SetEnergy()
{
	return GetPerctentage(GetCurrentEnergy(), GetMaxEnergy());
}

float APlayerCharacter::SetExp()
{
	return GetPerctentage(GetCurrentExp(), GetCurrentMaxExp());
}

float APlayerCharacter::HealthRegeneration(float deltaTime)
{
	return CurrentHealth = CurrentHealth + (deltaTime * HealthRegenRate);
}

float APlayerCharacter::EnergyRegeneration(float deltaTime)
{
	return CurrentEnergy = CurrentEnergy + (deltaTime * EnergyRegenRate);
}

void APlayerCharacter::StartSprint()
{

	if (bIsSprinting == false)
	{
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Start Sprint"));
	}

}

void APlayerCharacter::StopSprint()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Stop Sprint"));
}
