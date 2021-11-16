// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LightSwitch.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

#include "Blueprint/UserWidget.h"
#include "Character_Movement.generated.h"

UCLASS()
class ZADANIE4_API ACharacter_Movement : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_Movement();

	//Property Replication
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;



	UPROPERTY(BlueprintReadOnly, Category = "Camera")
		USpringArmComponent* CameraBoom;

	UPROPERTY(BlueprintReadOnly, Category = "Camera")
		UCameraComponent* FollowCamera;

	//Movement
	void MoveForward(float Axis);
	void MoveRight(float Axis);

	//Status
	bool bIsDead;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
		TSubclassOf<class ATPProjectible> ProjectileClass;

	//Cooldown on shooting
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
		float FireRate;

	// If true we are firing
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
		bool bIsFiringWeapon;

	//Start shooting
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void StartFire();

	//Stop shooting
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void StopFire();

	/** Server function for spawning projectiles.*/
	UFUNCTION(Server, Reliable)
		void HandleFire();

	// A timer 4 fire rate delay.
	FTimerHandle FiringTimer;

	//Light
	class ALightSwitch* CurrentLightSwitch;

	//Health 4 UI
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float ActualHealth;

	//Getter 4 max health
	UFUNCTION(BlueprintPure, Category = "Health")
		FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	//Getter 4 current Health
	UFUNCTION(BlueprintPure, Category = "Health")
		FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }

	//Setter 4 current Health. Clamps 0 - MaxHealth
	UFUNCTION(BlueprintCallable, Category = "Health")
		void SetCurrentHealth(float healthValue);

	//Event 4 takin damage
	UFUNCTION(BlueprintCallable, Category = "Health")
		float TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UUserWidget> Player_Power_Widget_Class;
	UUserWidget* Player_Power_Widget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<UUserWidget> Player_Health_Widget_Class;
	UUserWidget* Player_Health_Widget;

	//Player max health
	UPROPERTY(EditDefaultsOnly, Category = "Health")
		float MaxHealth{ 100 };

	//Player current health
	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth, BlueprintReadOnly) //BP
		float CurrentHealth;

	//Notify for changes made to current health
	UFUNCTION()
		void OnRep_CurrentHealth();

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_Interact();

	//Response to health being update
	void OnHealthUpdate();

	void Interact();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
