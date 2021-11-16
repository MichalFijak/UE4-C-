// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactive_Parent.h"
#include "Net/UnrealNetwork.h"
#include "Pickable.generated.h"

/**
 * 
 */
UCLASS()
class ZADANIE4_API APickable : public AInteractive_Parent
{
	GENERATED_BODY()
public:
	virtual void Interact() override;

	UPROPERTY(ReplicatedUsing = OnRep_Interact)
		bool state;

	UPROPERTY()
		bool CantCarryMore;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
		void OnRep_Interact();


	APickable();
};
