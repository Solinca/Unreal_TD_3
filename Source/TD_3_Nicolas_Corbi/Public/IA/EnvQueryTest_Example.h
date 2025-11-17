#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_Example.generated.h"

UCLASS()
class TD_3_NICOLAS_CORBI_API UEnvQueryTest_Example : public UEnvQueryTest
{
	GENERATED_BODY()
	
protected:
	UEnvQueryTest_Example();

	UPROPERTY(EditAnywhere, Category = "Context")
	TSubclassOf<UEnvQueryContext> Context = nullptr;

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
	virtual FText GetDescriptionTitle() const override;
};
