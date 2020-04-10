// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class RDS_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UFUNCTION(BlueprintPure, Category = "CharacterRDS|Stats|Health")
		float GetCurrentHealth();

	UFUNCTION(BlueprintPure, Category = "CharacterRDS|Stats|Health")
		float GetMaxHealth();

	UFUNCTION(BlueprintPure, Category = "CharacterRDS|Stats|Exp")
		float GetCurrentExp();

	UFUNCTION(BlueprintPure, Category = "CharacterRDS|Stats|Exp")
		float GetCurrentMaxExp();

	UFUNCTION(BlueprintPure, Category = "CharacterRDS|Stats|Exp")
		float GetBufferExp();

	UFUNCTION(BlueprintPure, Category = "CharacterRDS|Stats|Exp")
		float GetCharacterLevel();

	UFUNCTION(BlueprintPure, Category = "CharacterRDS|Stats|Exp")
		float GetCharacterLevelCap();

	UFUNCTION(BlueprintCallable, Category = "CharacterRDS|Stats|Exp")
		float AddExp(float AddedExp);

	UFUNCTION(BlueprintCallable, Category = "CharacterRDS|Stats|Exp")
		void LevelUp();

	UFUNCTION(BlueprintCallable, Category = "CharacterRDS|Stats|Health")
		float GetPerctentage(float CurrentValue, float MaxValue);

	UFUNCTION(BlueprintCallable, Category = "CharacterRDS|Stats|Exp")
		float CalculateMaxExp();

	UFUNCTION(BlueprintPure, Category = "CharacterRDS|Health")
		bool IsAlive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterRDS|Stats|Health")
		float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterRDS|Stats|Health")
		float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterRDS|Stats|Exp")
		float CurrentExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterRDS|Stats|Exp")
		float CurrentMaxExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterRDS|Stats|Exp")
		float BufferExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterRDS|Stats|Exp")
		float MaxExpMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterRDS|Stats|Level")
		int32 CharacterLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterRDS|Stats|Level")
		int32 CharacterLevelCap;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
