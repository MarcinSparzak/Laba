// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UHealthComponent::IsDead()
{
	return CurrentHealth <= 0;;
}

float UHealthComponent::GetHealth()
{
	return CurrentHealth;
}

float UHealthComponent::GetMaxHealth()
{
	return MaxHealth;
}

void UHealthComponent::SetMaxHealth(float newValue)
{
	MaxHealth = newValue;
}

void UHealthComponent::ApplyDamage(float damageValue)
{
	CurrentHealth-= damageValue;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);
}

void UHealthComponent::Heal(float healValue)
{
	CurrentHealth+= healValue;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

