// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"
//#include "Dev/STUFireDamageType.h"
//#include "Dev/STUIceDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(HealthComponentLog, All, All);

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	// ...
	
	AActor* ComponentOwner = GetOwner();

	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
	}
}

void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || isDead()) return;

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

	if (isDead())
	{
		onDeath.Broadcast();
	}

	//Health -= Damage;

	UE_LOG(HealthComponentLog, Display, TEXT("Damage: %f"), Damage);

	/*if (DamageType->IsA<USTUFireDamageType>())
	{
		UE_LOG(HealthComponentLog, Display, TEXT("Fire"));
	}
	else if(DamageType->IsA<USTUIceDamageType>())
	{
		UE_LOG(HealthComponentLog, Display, TEXT("Ice"));
	}*/
}