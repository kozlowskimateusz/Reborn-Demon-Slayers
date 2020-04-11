// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RDS/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RDS_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	APlayerCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;


	UFUNCTION(BlueprintPure, Category = "CharacterRDS|Stats|Energy")
		float GetCurrentEnergy();

	UFUNCTION(BlueprintPure, Category = "CharacterRDS|Stats|Energy")
		float GetMaxEnergy();

	UFUNCTION(BlueprintPure, Category = "CharacterRDS|Stats|Defense")
		float GetDefensePower();

	UFUNCTION(BlueprintPure, Category = "CharacterRDS|Stats|Attack")
		float GetAttackPower();

	UFUNCTION(BlueprintCallable, Category = "CharacterRDS|Stats|Health")
		float SetHealth();

	UFUNCTION(BlueprintCallable, Category = "CharacterRDS|Stats|Energy")
		float SetEnergy();

	UFUNCTION(BlueprintCallable, Category = "CharacterRDS|Stats|Exp")
		float SetExp();

	UFUNCTION(BlueprintCallable, Category = "CharacterRDS|Stats|Regeneration")
		float HealthRegeneration(float deltaTime);

	UFUNCTION(BlueprintCallable, Category = "CharacterRDS|Stats|Regeneration")
		float EnergyRegeneration(float deltaTime);

	UFUNCTION(BlueprintCallable, Category = "CharacterRDS|Stats|MoveSpeed")
		void StartSprint();

	UFUNCTION(BlueprintCallable, Category = "CharacterRDS|Stats|MoveSpeed")
		void StopSprint();


protected:

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterRDS|Stats|Energy")
		float CurrentEnergy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterRDS|Stats|Energy")
		float MaxEnergy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterRDS|Stats|Defense")
		float DefensePower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterRDS|Stats|Attack")
		float AttackPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterRDS|Stats|Regeneration")
		float HealthRegenRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterRDS|Stats|Regeneration")
		float EnergyRegenRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterRDS|Stats|Regeneration")
		float StaminaRegenRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterRDS|Stats|MoveSpeed")
		float SprintSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterRDS|Stats|MoveSpeed")
		float WalkSpeed;

	bool bIsSprinting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterRDS|Stats|Regeneration")
		float StaminaSprintConsume;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
};

	

