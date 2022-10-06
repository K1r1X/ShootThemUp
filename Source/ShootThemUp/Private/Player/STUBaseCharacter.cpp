	// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/STUBaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUCharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
//ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& objectInit) : Super(objectInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName)) //ASTUBaseCharacter::ASTUBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArm);

	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");
	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(HealthComponent); //проверка на создание
	check(HealthTextComponent); //проверка на создание

	HealthComponent->onDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto Health = HealthComponent->getHealth();
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));

	//TakeDamage(0.1f, FDamageEvent{}, Controller, this);
}

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("OnStartRun", IE_Pressed, this, &ASTUBaseCharacter::OnStartRun);
	PlayerInputComponent->BindAction("OnStopRun", IE_Released, this, &ASTUBaseCharacter::OnStopRun);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::TurnAround);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);
}

bool ASTUBaseCharacter::isRunning() const
{
	return bWantToRun && bIsMovingForward && !GetVelocity().IsZero();
}

void ASTUBaseCharacter::MoveForward(float Value)
{
	bIsMovingForward = Value > 0;
	AddMovementInput(GetActorForwardVector(), Value);
}

void ASTUBaseCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ASTUBaseCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ASTUBaseCharacter::TurnAround(float Value)
{
	AddControllerYawInput(Value);
}

void ASTUBaseCharacter::OnStartRun()
{
	bWantToRun = true;
}

void ASTUBaseCharacter::OnStopRun()
{
	bWantToRun = false;
}

void ASTUBaseCharacter::OnDeath()
{
	UE_LOG(BaseCharacterLog, Display,TEXT("Player %s is dead"), *GetName());
}



