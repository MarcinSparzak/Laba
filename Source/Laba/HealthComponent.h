// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LABA_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();


	UFUNCTION(BlueprintPure)
	bool IsDead();
	UFUNCTION(BlueprintPure)
	float GetHealth();
	UFUNCTION(BlueprintPure)
	float GetMaxHealth();
	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float newValue);
	UFUNCTION(BlueprintCallable)
	void ApplyDamage(float damageValue);
	UFUNCTION(BlueprintCallable)
	void Heal(float healValue);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly)
	float CurrentHealth = 100;
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;
		
};
