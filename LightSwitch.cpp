// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSwitch.h"


// Sets default values
ALightSwitch::ALightSwitch()
{
	state = true;
	intensivity = 100000;
	Light = CreateDefaultSubobject<USpotLightComponent>(TEXT("Light"));
	Light->SetupAttachment(GetRootComponent());
	Light->SetIntensity(intensivity);
}

void ALightSwitch::Interact()
{
	if (state)
	{
		Light->SetIntensity(0);

	}
	else
		Light->SetIntensity(intensivity);
	state = !state;
}

