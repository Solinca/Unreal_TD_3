#include "Global/MyWorldSubsystem.h"
#include "Global/MyDeveloperSettings.h"

void UMyWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	TickDelegate = FTickerDelegate::CreateUObject(this, &UMyWorldSubsystem::Tick);

	TickHandle = FTSTicker::GetCoreTicker().AddTicker(TickDelegate);
}

void UMyWorldSubsystem::Deinitialize()
{
	Super::Deinitialize();

	FTSTicker::GetCoreTicker().RemoveTicker(TickHandle);
}

bool UMyWorldSubsystem::Tick(float DeltaTime)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Hello Worldo");

	return true;
}

bool UMyWorldSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	UWorld* World = Cast<UWorld>(Outer);

	FString MapName = World->GetMapName();

	MapName.RemoveFromStart(World->StreamingLevelsPrefix, ESearchCase::IgnoreCase);

	const UMyDeveloperSettings* MyDS = GetDefault<UMyDeveloperSettings>();

	return MyDS && MyDS->LevelToLoadSubsystem.Get() && MyDS->LevelToLoadSubsystem.Get()->GetMapName() == MapName;
}
