// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUDevDamageActor.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUDevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUDevDamageActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* sceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float radius = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FColor sphereColor = FColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool doFullDamage = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UDamageType> damageType;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
