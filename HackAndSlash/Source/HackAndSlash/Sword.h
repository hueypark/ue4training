#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Sword.generated.h"

UCLASS()
class HACKANDSLASH_API ASword : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASword();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// 소멸 시간
	FDateTime DestroyTime;
};
