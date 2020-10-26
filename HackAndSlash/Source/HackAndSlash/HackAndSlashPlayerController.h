#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "HackAndSlashPlayerController.generated.h"

UCLASS()
class HACKANDSLASH_API AHackAndSlashPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AHackAndSlashPlayerController();

protected:
	virtual void SetupInputComponent() override;

	// 일반 공격 대상 찾기
	void FindNormalAttackTarget();

	// 마우스 커서 위치로 이동
	void MoveToMouseCursor();
};
