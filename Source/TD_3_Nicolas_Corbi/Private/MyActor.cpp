#include "MyActor.h"
#include <Kismet/GameplayStatics.h>

AMyActor::AMyActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> OutActors;

	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UDamageable::StaticClass(), OutActors);

	for (AActor* Actor : OutActors)
	{
		if (Actor->Implements<UDamageable>())
		{
			IDamageable::Execute_TakeDamage(Actor, 0);
		}
	}
}

void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyActor::TakeDamage_Implementation(float Amount)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Hello");
}
