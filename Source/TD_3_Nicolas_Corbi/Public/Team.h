#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Team.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTeam : public UInterface
{
	GENERATED_BODY()
};

UENUM(BlueprintType)
enum ETeam
{
	PLAYER,
	ENEMY
};

class TD_3_NICOLAS_CORBI_API ITeam
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	ETeam GetTeam();
};
