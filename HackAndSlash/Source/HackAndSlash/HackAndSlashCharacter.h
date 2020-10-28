#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "HackAndSlashCharacter.generated.h"

UCLASS()
class HACKANDSLASH_API AHackAndSlashCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHackAndSlashCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// 위치로 이동한다.
	void MoveToLocation(const FVector Location);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 서버에서 위치로 이동한다.
	UFUNCTION(Server, Reliable)
	void ServerMoveToLocation(const FVector Location);

	// 서버에서 일반 공격 대상을 설정한다.
	UFUNCTION(Server, Reliable)
	void ServerSetNormalAttackTarget(AHackAndSlashCharacter* Target);

	// 서버에서 일반 공격 대상 공격을 시도한다.
	UFUNCTION(Server, Reliable)
	void ServerTryNormalAttack();

	// 일반 공격 대상을 설정한다.
	void SetNormalAttackTarget(AHackAndSlashCharacter* Target);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	// 일반 공격 대상
	TWeakObjectPtr<class AHackAndSlashCharacter> NormalAttackTarget;

	// 검
	TSubclassOf<class ASword> Sword;

	// 공격속도
	float AttackCoolTime;

	// 다음 공격 가능시간
	FDateTime NextAttackableTime;
};
