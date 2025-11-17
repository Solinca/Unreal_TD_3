#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Team.h"
#include <Engine/DataTable.h>
#include "MyPawn.generated.h"

UCLASS()
class TD_3_NICOLAS_CORBI_API AMyPawn : public APawn, public ITeam
{
	GENERATED_BODY()

protected:
	AMyPawn();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual ETeam GetTeam_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VALUE")
	TObjectPtr<UDataTable> ExampleDataTable = nullptr;
};
