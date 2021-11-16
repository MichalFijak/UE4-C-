// Fill out your copyright notice in the Description page of Project Settings.


#include "Damageable.h"

// Sets default values
ADamageable::ADamageable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Destructible Component"));
	DestructibleComponent->SetupAttachment(RootComponent);
	DestructibleComponent->SetNotifyRigidBodyCollision(true);

	isDestroyed = false;
	bReplicates = true;
	maxHealth = 10.0f;
	damage = 5.0f;
	impulse = 2.0f;
	DestructibleComponent->OnComponentHit.AddDynamic(this, &ADamageable::Damage);
}


// Called when the game starts or when spawned
void ADamageable::BeginPlay()
{
	Super::BeginPlay();
	currentHealth = maxHealth;

	
}

// Called every frame
void ADamageable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADamageable::Damage(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FVector particleLocation = DestructibleComponent->GetComponentLocation();
	if (!isDestroyed)
	{

		currentHealth -= damage;



		if (currentHealth <= 0)
		{
			int overKill = 20;

			UE_LOG(LogTemp, Warning, TEXT("Dead"));
			DestructibleComponent->ApplyDamage(overKill, DestructibleComponent->GetComponentLocation(), DestructibleComponent->GetForwardVector(), impulse);


			isDestroyed = true;
		}
		UE_LOG(LogTemp, Warning, TEXT("hit!"));

	}


}

