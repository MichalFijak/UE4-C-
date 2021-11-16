// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Net/UnrealNetwork.h"
#include "Interactive_Parent.generated.h"

UCLASS()
class ZADANIE4_API AInteractive_Parent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractive_Parent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() PURE_VIRTUAL(AInteractive_Parent::Interact, );

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USceneComponent* _RootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* Mesh;
};
