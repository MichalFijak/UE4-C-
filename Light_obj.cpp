// Fill out your copyright notice in the Description page of Project Settings.


#include "Light_obj.h"
#include "Net/UnrealNetwork.h"

ALight_obj::ALight_obj()
{
	state = true;
	intensivity = 9000000;
	Light = CreateDefaultSubobject<USpotLightComponent>(TEXT("Light"));
	Light->SetupAttachment(GetRootComponent());
	Light->SetIntensity(intensivity);
	bReplicates = true;
}
void ALight_obj::Interact()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		state = !state;
		OnRep_Interact();
	}
}
void ALight_obj::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALight_obj, state);
}

void ALight_obj::OnRep_Interact()
{
	if (state)
	{
		Light->SetIntensity(0);

	}
	else
		Light->SetIntensity(intensivity);
}