// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive_Parent.h"

// Sets default values
AInteractive_Parent::AInteractive_Parent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = _RootComponent;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractive_Parent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractive_Parent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

