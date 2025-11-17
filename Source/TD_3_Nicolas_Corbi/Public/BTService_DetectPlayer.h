#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_DetectPlayer.generated.h"

UCLASS()
class TD_3_NICOLAS_CORBI_API UBTService_DetectPlayer : public UBTService
{
	GENERATED_BODY()
	
protected:
	UBTService_DetectPlayer();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector TargetLocation;

	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector IsTargetSet;

	UPROPERTY(EditAnywhere, Category = "Keys")
	float SphereRadius = 500.f;
};
