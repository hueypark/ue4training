#include "HackAndSlashPlayerController.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"

AHackAndSlashPlayerController::AHackAndSlashPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AHackAndSlashPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("MoveToMouseCursor", IE_Pressed, this, &AHackAndSlashPlayerController::MoveToMouseCursor);
}

void AHackAndSlashPlayerController::MoveToMouseCursor()
{
	FHitResult TraceHitResult;
	GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, TraceHitResult.Location);
}
