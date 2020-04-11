// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "NiagaraComponent.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Item Collision"));
	ItemCollision->SetupAttachment(GetRootComponent());

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	ItemMesh->SetupAttachment(ItemCollision);

	ItemAudio = CreateDefaultSubobject<UAudioComponent>("Item Audio");

	ItemParticleSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Item Parcticle System"));
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

