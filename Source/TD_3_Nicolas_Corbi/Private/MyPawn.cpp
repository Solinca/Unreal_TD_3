#include "MyPawn.h"
#include <Datas/ExampleDataAsset.h>

AMyPawn::AMyPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

	//FExampleStruct* DefaultRow = ExampleDataTable->FindRow<FExampleStruct>("Default", "Example Find Row");

	//TArray<FName> RowNames = ExampleDataTable->GetRowNames();
}

void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ETeam AMyPawn::GetTeam_Implementation()
{
	return ETeam::PLAYER;
}
