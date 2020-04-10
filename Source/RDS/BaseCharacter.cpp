// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


float ABaseCharacter::GetCurrentHealth()
{
	return CurrentHealth;
}

float ABaseCharacter::GetMaxHealth()
{
	return MaxHealth;
}

float ABaseCharacter::GetCurrentExp()
{
	return CurrentExp;
}

float ABaseCharacter::GetCurrentMaxExp()
{
	return CurrentMaxExp;
}

float ABaseCharacter::GetBufferExp()
{
	return BufferExp;
}

float ABaseCharacter::GetCharacterLevel()
{
	return CharacterLevel;
}

float ABaseCharacter::GetCharacterLevelCap()
{
	return CharacterLevelCap;
}

float ABaseCharacter::AddExp(float AddedExp)
{
	return BufferExp = CurrentExp + AddedExp;
}

void ABaseCharacter::LevelUp()
{
	if (CharacterLevel <= CharacterLevelCap)
	{
		CharacterLevel++;

		float RemaingExp = BufferExp - CurrentMaxExp;
		CalculateMaxExp();
		BufferExp = 0.f;
		CurrentExp = 0.f;
		AddExp(RemaingExp);

	}
	else
	{
		BufferExp = CurrentMaxExp;
		CurrentExp = CurrentMaxExp;
	}
}



float ABaseCharacter::GetPerctentage(float CurrentValue, float MaxValue)
{
	return CurrentValue / MaxValue;
}

float ABaseCharacter::CalculateMaxExp()
{
	return CurrentMaxExp = CurrentMaxExp * MaxExpMultiplier;
}

bool ABaseCharacter::IsAlive()
{
	if (GetCurrentHealth() <= 0)
	{
		return false;
	}
	return true;
}