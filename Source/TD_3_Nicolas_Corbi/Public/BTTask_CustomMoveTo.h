#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CustomMoveTo.generated.h"

UCLASS()
class TD_3_NICOLAS_CORBI_API UBTTask_CustomMoveTo : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_CustomMoveTo();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector TargetLocation;

	UPROPERTY(EditAnywhere, Category = "Properties")
	float AcceptanceRadius = 50.0f;
};
