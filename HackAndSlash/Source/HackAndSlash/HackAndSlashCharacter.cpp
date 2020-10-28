#include "HackAndSlashCharacter.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HackAndSlash/Sword.h"

AHackAndSlashCharacter::AHackAndSlashCharacter()
{
	// 매 틱마다 업데이트
	PrimaryActorTick.bCanEverTick = true;

	// 카메라 방향에 따라 캐릭터 회전하지 않음
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// 캐릭터 이동 설정
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// 카메라 붐
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	// 탑다운 카메라
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	static ConstructorHelpers::FClassFinder<ASword> SwordClass(TEXT("/Game/Character/BP_Sword"));
	if (SwordClass.Class != nullptr)
	{
		Sword = SwordClass.Class;
	}

	AttackCoolTime = 1000;
}

void AHackAndSlashCharacter::BeginPlay()
{
	Super::BeginPlay();

	NormalAttackTarget = nullptr;

	NextAttackableTime = FDateTime::Now();
}

void AHackAndSlashCharacter::MoveToLocation(const FVector Location)
{
	ServerMoveToLocation(Location);
}

void AHackAndSlashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ServerTryNormalAttack();
}

void AHackAndSlashCharacter::ServerMoveToLocation_Implementation(const FVector Location)
{
	float const Distance = FVector::Dist(Location, GetActorLocation());

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), Location);
}

void AHackAndSlashCharacter::ServerSetNormalAttackTarget_Implementation(AHackAndSlashCharacter* Target)
{
	NormalAttackTarget = Target;
}

void AHackAndSlashCharacter::ServerTryNormalAttack_Implementation()
{
	FDateTime Now = FDateTime::Now();

	AHackAndSlashCharacter* Target = NormalAttackTarget.Get();
	if (!Target)
		return;

	if (Now <= NextAttackableTime)
		return;

	NextAttackableTime = Now + FTimespan::FromMilliseconds(AttackCoolTime);

	FVector Dir = Target->GetActorLocation() - GetActorLocation();
	Dir.Normalize();

	GetWorld()->SpawnActor<ASword>(Sword, GetActorLocation() + (Dir * 100), Dir.Rotation());
}

void AHackAndSlashCharacter::SetNormalAttackTarget(AHackAndSlashCharacter* Target)
{
	ServerSetNormalAttackTarget(Target);
}

void AHackAndSlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
