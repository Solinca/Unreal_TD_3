#include "BTDecorator_CheckBoolean.h"

UBTDecorator_CheckBoolean::UBTDecorator_CheckBoolean()
{
	NodeName = "Check Boolean";
}

bool UBTDecorator_CheckBoolean::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return 1 + 1 == 2;
}
