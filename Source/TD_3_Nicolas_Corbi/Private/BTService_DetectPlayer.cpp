#include "BTService_DetectPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Team.h"

UBTService_DetectPlayer::UBTService_DetectPlayer()
{
	NodeName = "Search For Player And Set Location";

	Interval = 0.2f;

	RandomDeviation = 0.f;
}

void UBTService_DetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* Controller = OwnerComp.GetAIOwner();

	if (!Controller)
	{
		return;
	}

	APawn* Pawn = Controller->GetPawn();

	if (!Pawn)
	{
		return;
	}

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{ UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn) };

	TArray<AActor*> ToIgnore{ Pawn };

	TArray<AActor*> OutActors;

	if (UKismetSystemLibrary::SphereOverlapActors(GetWorld(), Pawn->GetActorLocation(), SphereRadius, ObjectTypes, APawn::StaticClass(), ToIgnore, OutActors))
	{
		for (AActor* Actor : OutActors)
		{
			if (Actor->Implements<UTeam>())
			{
				if (ITeam::Execute_GetTeam(Actor) == ETeam::PLAYER)
				{
					Blackboard->SetValueAsVector(TargetLocation.SelectedKeyName, Actor->GetActorLocation());
					Blackboard->SetValueAsBool(IsTargetSet.SelectedKeyName, true);
				}
			}

			return;
		}
	}

	Blackboard->ClearValue(IsTargetSet.SelectedKeyName);
}
