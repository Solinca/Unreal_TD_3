#include "Global/MyGameMode.h"
#include "Global/MyGameState.h"
#include "Kismet/GameplayStatics.h"

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
