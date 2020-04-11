// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FName ItemName;
}; 




UCLASS()
class RDS_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	class USphereComponent* ItemCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	class UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	class UAudioComponent* ItemAudio;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	class UNiagaraComponent* ItemParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemData")
	FItemData ItemData;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
