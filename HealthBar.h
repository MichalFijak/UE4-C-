// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Character_Movement.h"
#include "HealthBar.generated.h"
/**
 * 
 */
UCLASS( Abstract)
class ZADANIE4_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()

	
	
protected:
	
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

};
