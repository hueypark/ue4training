#include "Sword.h"

#include "Misc/Timespan.h"

ASword::ASword()
{
	bReplicates = true;

	PrimaryActorTick.bCanEverTick = true;
}

void ASword::BeginPlay()
{
	Super::BeginPlay();

	DestroyTime = FDateTime::Now() + FTimespan::FromSeconds(1);
}

void ASword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DestroyTime <= FDateTime::Now())
	{
		Destroy();
	}
}
