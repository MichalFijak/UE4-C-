// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickable.h"

APickable::APickable()
{

	state = true;
	CantCarryMore = false;
	bReplicates = true;
}
void APickable::Interact()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		state = !state;
		OnRep_Interact();
	}
}
void APickable::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APickable, state);
}

void APickable::OnRep_Interact()
{
	if (state)
	{
		Destroy();
		CantCarryMore = true; // should be in character if(CantCarryMore then ..)

	}

}
