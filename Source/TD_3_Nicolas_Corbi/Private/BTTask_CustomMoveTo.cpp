#include "BTTask_CustomMoveTo.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"

UBTTask_CustomMoveTo::UBTTask_CustomMoveTo()
{
	NodeName = "Custom Move To";
}

EBTNodeResult::Type UBTTask_CustomMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	FVector TargetVector = Blackboard->GetValueAsVector(TargetLocation.SelectedKeyName);

	AAIController* Controller = OwnerComp.GetAIOwner();

	FAIMoveRequest Request;

	Request.SetGoalLocation(TargetVector);

	Request.SetAcceptanceRadius(AcceptanceRadius);

	FPathFollowingRequestResult Result = Controller->MoveTo(Request);

	// DO MOVE_TO IN BP SINCE IT SUCKS IN C++

	return EBTNodeResult::Succeeded;
}
