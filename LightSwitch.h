// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactive_Parent.h"
#include "Components/SpotLightComponent.h"
#include "LightSwitch.generated.h"

UCLASS()
class ZADANIE4_API ALightSwitch : public AInteractive_Parent
{
	GENERATED_BODY()

public:

	virtual void Interact() override;
	UPROPERTY()// SERVER !
		bool state;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float intensivity{ 5000 };

	UPROPERTY(EditAnywhere)
		USpotLightComponent* Light;
	ALightSwitch();

};
