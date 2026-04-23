// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include <EnhancedInputSubsystems.h>
#include "InputMappingContext.h"

void AMyPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
    UE_LOG(LogTemp, Warning, TEXT("IsLocal: %d"), IsLocalController());

    if (!IsLocalController()) return;

    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        UE_LOG(LogTemp, Warning, TEXT("LocalPlayer OK"));
        if (UEnhancedInputLocalPlayerSubsystem* InputSystem =
            LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            UE_LOG(LogTemp, Warning, TEXT("InputSystem OK"));
            if (!InputMapping.IsNull())
            {
                UE_LOG(LogTemp, Warning, TEXT("InputMapping OK"));
                InputSystem->ClearAllMappings();
                InputSystem->AddMappingContext(InputMapping.LoadSynchronous(), 0);
            }
        }
    }
}
