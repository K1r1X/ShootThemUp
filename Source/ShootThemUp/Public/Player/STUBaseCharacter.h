// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USTUHealthComponent;
class UTextRenderComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTUBaseCharacter(const FObjectInitializer& objectInit); /*const FObjectInitializer& objectInit*/

protected:
	// Called when the game starts or when spawned
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
		UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
		USTUHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
		UTextRenderComponent* HealthTextComponent;

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool isRunning() const;

private:

	bool bWantToRun = false;

	bool bIsMovingForward = false;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void LookUp(float Value);

	void TurnAround(float Value);

	void OnStartRun();

	void OnStopRun();

	void OnDeath();
};
