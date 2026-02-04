#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MyGameState.generated.h"

UCLASS()
class TD_3_NICOLAS_CORBI_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()

private:
	UPROPERTY(ReplicatedUsing = DisplayEveryPlayer)
	TArray<FString> PlayerNameList;

	UFUNCTION()
	void DisplayEveryPlayer();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	UFUNCTION(Server, Reliable)
	void PlayerJoined(const FString& PlayerName);

	UFUNCTION(Server, Reliable)
	void PlayerLeft(const FString& PlayerName);
};
