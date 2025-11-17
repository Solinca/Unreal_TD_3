#include "IA/EnvQueryContext_Player.h"
#include "Kismet/GameplayStatics.h"
#include "Team.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"

void UEnvQueryContext_Player::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	TArray<AActor*> Actors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawn::StaticClass(), Actors);

	if (Actors.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("NO PAWN DETECTED"));

		return;
	}

	AActor* Player = nullptr;

	float NearestDistance = TNumericLimits<float>().Max();

	for (AActor* Actor : Actors)
	{
		if (Actor->Implements<UTeam>())
		{
			if (ITeam::Execute_GetTeam(Actor) == PLAYER)
			{
				FVector ActorLocation = Cast<AActor>(QueryInstance.Owner)->GetActorLocation();

				float Distance = FVector::Distance(ActorLocation, Actor->GetActorLocation());

				if (Distance >= NearestDistance)
				{
					continue;
				}

				Player = Actor;
				NearestDistance = Distance;
			}
		}
	}

	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("NO PLAYER DETECTED"));

		UEnvQueryItemType_Point::SetContextHelper(ContextData, FVector::ZeroVector);

		return;
	}

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, Player);
}
