// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactive_Parent.h"
#include "Net/UnrealNetwork.h"
#include "Components/SpotLightComponent.h"
#include "Light_obj.generated.h"

/**
 * 
 */
UCLASS()
class ZADANIE4_API ALight_obj : public AInteractive_Parent
{
	GENERATED_BODY()
public:
	virtual void Interact() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float intensivity{ 900000 };

	UPROPERTY(ReplicatedUsing= OnRep_Interact)
		bool state;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_Interact();

	UPROPERTY(EditAnywhere)
		USpotLightComponent* Light;
	ALight_obj();
};

