// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Damageable.generated.h"


UCLASS()
class ZADANIE4_API ADamageable : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ADamageable();

	


	void Damage(UPrimitiveComponent* HitComponent,AActor* OtherActor,UPrimitiveComponent*OtherComp,FVector NormalImpulse, const FHitResult& Hit);
	void Destroy();

	// status
	UPROPERTY(EditAnyWhere, Category = "Attack")
		bool isDemegeable{ true };
	UPROPERTY(EditAnyWhere, Category = "Destructible")
		bool isDestructible{ true };
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Destructible")
		bool isDestroyed{ false };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Destructible")
		class UDestructibleComponent* DestructibleComponent;

	//health
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Destructible")
		float maxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Destructible")
		float currentHealth;

	//Damage//
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Destructible")
		float damage;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Destructible")
		float impulse;

	//UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Particle")
	//UNiagaraSystem* NS_Destructible;

	//UFUNCTION()
		//void OnRep_ReplicatedHits();



	float latestDamageTimestamp = 0.0f;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

