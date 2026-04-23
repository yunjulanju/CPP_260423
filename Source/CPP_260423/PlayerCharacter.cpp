// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetRelativeLocation(FVector(0, 0, 40));
	SpringArm->SocketOffset = FVector(0, 0, 40);


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UE_LOG(LogTemp, Warning, TEXT("SetupPlayerInputComponent called"));

	UEnhancedInputComponent* UIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UIC)
	{
		UE_LOG(LogTemp, Warning, TEXT("UIC Cast OK"));
		UIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		UIC->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &APlayerCharacter::Turn);
		UIC->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
		UIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &APlayerCharacter::StopJumping);
		UIC->BindAction(IA_Jump, ETriggerEvent::Canceled, this, &APlayerCharacter::StopJumping);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UIC Cast FAILED"));
	}
	
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("APlayerCharacter::Turn"));
	FVector2D Direction = Value.Get<FVector2D>();

	FRotator CameraRotation = GetControlRotation();

	FRotator CameraRotaitionInFloor = FRotator(0, CameraRotation.Yaw, 0);

	FVector CameraForwardInFloor = UKismetMathLibrary::GetForwardVector(CameraRotaitionInFloor);

	FVector CameraRightInFloor = UKismetMathLibrary::GetRightVector(CameraRotaitionInFloor);

	AddMovementInput(CameraForwardInFloor * Direction.X);

	AddMovementInput(CameraRightInFloor * Direction.Y);
}

void APlayerCharacter::Turn(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("APlayerCharacter::Turn"));
	FVector2D RotationDirection = Value.Get<FVector2D>();

	AddControllerPitchInput(RotationDirection.Y);
	AddControllerYawInput(RotationDirection.X);
}

