#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CheckBoolean.generated.h"

UCLASS()
class TD_3_NICOLAS_CORBI_API UBTDecorator_CheckBoolean : public UBTDecorator
{
	GENERATED_BODY()
	
protected:
	UBTDecorator_CheckBoolean();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
