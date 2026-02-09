#include "Global/MyGameMode.h"
#include "Global/MyGameState.h"
#include "Global/MyGameInstanceSubsystem.h"
#include "Player/MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameSession.h"

void AMyGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	if (GameSession->AtCapacity(false))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "SESSION FULL");

		ErrorMessage = TEXT("SESSION FULL");
	}
}

void AMyGameMode::OnPostLogin(AController* Controller)
{
	Super::OnPostLogin(Controller);

	GetGameState<AMyGameState>()->PlayerJoined(Controller->GetName());
}

void AMyGameMode::Logout(AController* Controller)
{
	Super::Logout(Controller);

	GetGameState<AMyGameState>()->PlayerLeft(Controller->GetName());
}

void AMyGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	GameSession->MaxPlayers = GetGameInstance()->GetSubsystem<UMyGameInstanceSubsystem>()->MaxPlayers;
}

void AMyGameMode::DestroyGame()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		if (AMyPlayerController* PC = Cast<AMyPlayerController>(It->Get()))
		{
			PC->DestroySessionOnClient();
		}
	}
}
