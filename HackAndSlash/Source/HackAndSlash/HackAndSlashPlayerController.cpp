#include "HackAndSlashPlayerController.h"

#include "HackAndSlashCharacter.h"

AHackAndSlashPlayerController::AHackAndSlashPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AHackAndSlashPlayerController::FindNormalAttackTarget()
{
	AHackAndSlashCharacter* HackAndSlashCharacter = Cast<AHackAndSlashCharacter>(GetPawn());
	if (!HackAndSlashCharacter)
	{
		return;
	}

	FHitResult TraceHitResult;
	GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);

	AHackAndSlashCharacter* Target = Cast<AHackAndSlashCharacter>(TraceHitResult.GetActor());
	if (HackAndSlashCharacter == Target)
	{
		return;
	}

	HackAndSlashCharacter->SetNormalAttackTarget(Target);
}

void AHackAndSlashPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("FindNormalAttackTarget", IE_Pressed, this, &AHackAndSlashPlayerController::FindNormalAttackTarget);
	InputComponent->BindAction("MoveToMouseCursor", IE_Pressed, this, &AHackAndSlashPlayerController::MoveToMouseCursor);
}

void AHackAndSlashPlayerController::MoveToMouseCursor()
{
	AHackAndSlashCharacter* HackAndSlashCharacter = Cast<AHackAndSlashCharacter>(GetPawn());
	if (!HackAndSlashCharacter)
	{
		return;
	}

	FHitResult TraceHitResult;
	GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);

	HackAndSlashCharacter->MoveToLocation(TraceHitResult.Location);
}
