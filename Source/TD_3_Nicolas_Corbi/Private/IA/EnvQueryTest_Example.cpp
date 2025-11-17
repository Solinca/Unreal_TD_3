#include "IA/EnvQueryTest_Example.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_VectorBase.h"

UEnvQueryTest_Example::UEnvQueryTest_Example()
{
	ValidItemType = UEnvQueryItemType_VectorBase::StaticClass();
}

void UEnvQueryTest_Example::RunTest(FEnvQueryInstance& QueryInstance) const
{
	TArray<FVector> ContextLocations;

	if (!QueryInstance.PrepareContext(Context, ContextLocations))
	{
		return;
	}

	for (FEnvQueryInstance::ItemIterator it(this, QueryInstance); it; ++it)
	{
		it.SetScore(TestPurpose,  FilterType, UKismetMathLibrary::RandomFloatInRange(0, 1), 0, 1);
	}
}

FText UEnvQueryTest_Example::GetDescriptionTitle() const
{
	return FText::FromString("Random");
}
