// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPProjectible.generated.h"

UCLASS()
class ZADANIE4_API ATPProjectible : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ATPProjectible();

	//Sphere component 4 testing collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USphereComponent* SphereComponent;

	//Static Mesh 4 visual presentation of missile
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* StaticMesh;

	//Movement component 4 missile movement
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UProjectileMovementComponent* ProjectileMovementComponent;

	//Damage type and damage done
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
		TSubclassOf<class UDamageType> DamageType;

	//Explosion Effect
	UPROPERTY(VisibleAnywhere, Category = "Explosion")
		class UParticleSystem* ExplosionEffect;

	//Explosion Effect Sound
	UPROPERTY(VisibleAnywhere, Category = "ExplosionS")
		class USoundBase* SBexplosion;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
		float Damage;

	UFUNCTION(Category = "Projectile")
		void OnProjectibleImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
