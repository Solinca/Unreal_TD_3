#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

UCLASS()
class TD_3_NICOLAS_CORBI_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void OnPostLogin(AController* Controller) override;

	virtual void Logout(AController* Controller) override;
};
