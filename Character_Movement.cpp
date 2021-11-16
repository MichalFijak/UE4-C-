// Fill out your copyright notice in the Description page of Project Settings.

#include "Character_Movement.h"
#include "TPProjectible.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "Interactive_Parent.h"
#include "Pickable.h"
#include "Blueprint/UserWidget.h"

#include "TimerManager.h"

// Sets default values
ACharacter_Movement::ACharacter_Movement()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Capsule Size
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	//Player cant rotate
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Character Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	//Camera attachment
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	//Camera attachment behind player

	//CameraBoom->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(-120.0f,-120.0f,0)); // camera offset
	CameraBoom->TargetArmLength = 300.0f;

	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	FollowCamera->bUsePawnControlRotation = false;

	//Projectiles
	ProjectileClass = ATPProjectible::StaticClass();

	FireRate = 0.25f;



}


// Called when the game starts or when spawned
void ACharacter_Movement::BeginPlay()
{
	Super::BeginPlay();

	bIsDead = false;
	CurrentHealth = MaxHealth;


	bIsFiringWeapon = false;

	Player_Power_Widget = CreateWidget(GetWorld(), Player_Power_Widget_Class);
	Player_Power_Widget->AddToViewport();



}



// Called every frame
void ACharacter_Movement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentHealth <= 0)
	{
		bIsDead = true;
		Destroy();
	}

}

// Called to bind functionality to input
void ACharacter_Movement::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Camera
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	//Action
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &ACharacter_Movement::Interact);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACharacter_Movement::StartFire);

	//Moving
	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacter_Movement::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacter_Movement::MoveRight);


}
void ACharacter_Movement::MoveForward(float Axis)
{
	if (!bIsDead) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}
void ACharacter_Movement::MoveRight(float Axis)
{
	if (!bIsDead) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}
void ACharacter_Movement::Interact()
{
	FHitResult itemHit;
	FVector rayLocation = GetActorLocation();
	FRotator rayRotation = GetControlRotation();
	FVector endTrace = (rayLocation + (rayRotation.Vector()) * 400);
	
	

	if (GetWorld()->LineTraceSingleByChannel(itemHit, rayLocation, endTrace, ECC_Visibility))
	{
		AInteractive_Parent* obj = Cast<AInteractive_Parent>(itemHit.Actor);
		if (obj)
		{
			if (GetLocalRole() == ROLE_Authority)
			{
				obj->Interact();
				
			}
			else
			{
				Server_Interact();
			}
		}

		// if hited actor has tag "Pickable" set CantCarryMore = true
	}
	
}
bool ACharacter_Movement::Server_Interact_Validate()
{
	return true;
}
void ACharacter_Movement::Server_Interact_Implementation()
{
	Interact();
}

void ACharacter_Movement::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//If something is needed to replicate, write it here


	//Replicate current health
	DOREPLIFETIME(ACharacter_Movement, CurrentHealth);


}
void ACharacter_Movement::OnHealthUpdate()
{
	//Client functionality
	/*if (IsLocallyControlled())
	{
		String healthMessage = FString::Printf(TEXT("You now have %f health remaining."), CurrentHealth);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, healthMessage);

		if (CurrentHealth <= 0)
		{
			//FString deathMessage = FString::Printf(TEXT("You died"));
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, deathMessage);
		}

	}

	if (GetLocalRole() == ROLE_Authority)
	{
		FString healthMessage = FString::Printf(TEXT("%s now has %f health remaining."), *GetFName().ToString(), CurrentHealth);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);


	}
	//Function dat occurs on all machines

	//Any special functionality after damage and death should be here
	*/
}
void ACharacter_Movement::OnRep_CurrentHealth()
{
	OnHealthUpdate();

}

void ACharacter_Movement::SetCurrentHealth(float HealthValue)
{
	if (GetLocalRole() == ROLE_Authority)
	{

		CurrentHealth = FMath::Clamp(HealthValue, 0.f, MaxHealth);
		OnHealthUpdate();
	}
}

float ACharacter_Movement::TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damageApplied = CurrentHealth - DamageTaken;
	SetCurrentHealth(damageApplied);
	ActualHealth = CurrentHealth - DamageTaken; //To delete later
	return damageApplied;
}
void ACharacter_Movement::StartFire()
{
	if (!bIsFiringWeapon)
	{
		bIsFiringWeapon = true;
		UWorld* World = GetWorld();
		World->GetTimerManager().SetTimer(FiringTimer, this, &ACharacter_Movement::StopFire, FireRate, false);
		HandleFire();

	}
}

void ACharacter_Movement::StopFire()
{
	bIsFiringWeapon = false;
}

void ACharacter_Movement::HandleFire_Implementation()
{
	FVector spawnLocation = GetActorLocation() + (GetControlRotation().Vector() * 100.0f) + (GetActorUpVector() * 50.0f); // Gdzie spawni sie pocisk
	FRotator spawnRotation = GetControlRotation();

	FActorSpawnParameters spawnParameters;
	spawnParameters.Instigator = GetInstigator();
	spawnParameters.Owner = this;

	ATPProjectible* spawnedProjectile = GetWorld()->SpawnActor<ATPProjectible>(spawnLocation, spawnRotation, spawnParameters);

}
