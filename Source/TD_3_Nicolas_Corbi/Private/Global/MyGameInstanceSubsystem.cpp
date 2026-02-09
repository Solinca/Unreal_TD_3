#include "Global/MyGameInstanceSubsystem.h"
#include "Online/OnlineSessionNames.h"
#include "OnlineSubsystemUtils.h"

void UMyGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Session = Online::GetSessionInterface(GetWorld());
}

void UMyGameInstanceSubsystem::OnCreateSessionCompleted(FName SessionName, bool IsSuccessful)
{
	if (Session)
	{
		Session->ClearOnCreateSessionCompleteDelegate_Handle(CreateHandle);
	}

	if (!IsSuccessful)
	{
		return;
	}

	GetWorld()->ServerTravel("/Game/Levels/TestNetworkGame?Listen");
}

void UMyGameInstanceSubsystem::OnFindSessionCompleted(bool IsSuccessful)
{
	if (Session)
	{
		Session->ClearOnFindSessionsCompleteDelegate_Handle(FindHandle);
	}

	SearchResults = LastSessionSearch->SearchResults;

	if (SearchResults.IsEmpty())
	{
		OnFindGameSessionComplete.Broadcast(TArray<FCustomSessionInfo>(), IsSuccessful);

		return;
	}

	TArray<FCustomSessionInfo> SessionsInfo;

	for (int i = 0; i < SearchResults.Num(); i++)
	{
		FOnlineSessionSearchResult Result = SearchResults[i];

		FCustomSessionInfo SessionInfo;

		FString SessionName;

		Result.Session.SessionSettings.Get("SETTING_SESSIONNAME", SessionName);

		SessionInfo.SessionName = SessionName;

		SessionInfo.MaxPlayers = Result.Session.SessionSettings.NumPublicConnections;

		SessionInfo.CurrentPlayers = Result.Session.SessionSettings.NumPublicConnections - Result.Session.NumOpenPublicConnections;

		SessionInfo.Ping = Result.PingInMs;

		SessionInfo.SessionSearchResultIndex = i;

		SessionsInfo.Add(SessionInfo);
	}

	OnFindGameSessionComplete.Broadcast(SessionsInfo, IsSuccessful);
}

void UMyGameInstanceSubsystem::OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	FString ConnectString;

	if (Session)
	{
		Session->ClearOnJoinSessionCompleteDelegate_Handle(JoinHandle);
	}

	if (Result != EOnJoinSessionCompleteResult::Success || !Session->GetResolvedConnectString(NAME_GameSession, ConnectString))
	{
		// Do something like broadcast to display join error

		return;
	}

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	PlayerController->ClientTravel(ConnectString, TRAVEL_Absolute);
}

void UMyGameInstanceSubsystem::OnDestroySessionCompleted(FName SessionName, bool IsSuccessful)
{
	if (Session)
	{
		Session->ClearOnDestroySessionCompleteDelegate_Handle(DestroyHandle);
	}
}

void UMyGameInstanceSubsystem::JoinGameSession(const FOnlineSessionSearchResult& SessionResult)
{
	if (!Session.IsValid())
	{
		return;
	}

	JoinHandle = Session->AddOnJoinSessionCompleteDelegate_Handle(FOnJoinSessionCompleteDelegate::CreateUObject(this, &UMyGameInstanceSubsystem::OnJoinSessionCompleted));

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();

	if (!Session->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, SessionResult))
	{
		Session->ClearOnJoinSessionCompleteDelegate_Handle(JoinHandle);

		return;
	}
}

void UMyGameInstanceSubsystem::CreateSession(const FString& SessionName, int32 NumPublicConnections, bool IsLanMatch)
{
	if (!Session.IsValid())
	{
		return;
	}

	MaxPlayers = NumPublicConnections;
	
	LastSessionSettings = MakeShareable(new FOnlineSessionSettings());

	LastSessionSettings->NumPublicConnections = NumPublicConnections;

	LastSessionSettings->bAllowJoinInProgress = true;

	LastSessionSettings->bAllowJoinViaPresence = true;

	LastSessionSettings->bIsDedicated = false;

	LastSessionSettings->bUsesPresence = true;

	LastSessionSettings->bIsLANMatch = IsLanMatch;

	LastSessionSettings->bShouldAdvertise = true;

	LastSessionSettings->Set("SETTING_SESSIONNAME", SessionName, EOnlineDataAdvertisementType::ViaOnlineService);

	CreateHandle = Session->AddOnCreateSessionCompleteDelegate_Handle(FOnCreateSessionCompleteDelegate::CreateUObject(this, &UMyGameInstanceSubsystem::OnCreateSessionCompleted));

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();

	if (!Session->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *LastSessionSettings))
	{
		Session->ClearOnCreateSessionCompleteDelegate_Handle(CreateHandle);

		return;
	}
}

void UMyGameInstanceSubsystem::FindSession(int32 MaxSearchResults, bool IsLanQuery)
{
	if (!Session.IsValid())
	{
		return;
	}

	FindHandle = Session->AddOnFindSessionsCompleteDelegate_Handle(FOnFindSessionsCompleteDelegate::CreateUObject(this, &UMyGameInstanceSubsystem::OnFindSessionCompleted));

	LastSessionSearch = MakeShareable(new FOnlineSessionSearch());

	LastSessionSearch->MaxSearchResults = MaxSearchResults;

	LastSessionSearch->bIsLanQuery = IsLanQuery;

	LastSessionSearch->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();

	if (!Session->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), LastSessionSearch.ToSharedRef()))
	{
		Session->ClearOnFindSessionsCompleteDelegate_Handle(FindHandle);

		return;
	}
}

void UMyGameInstanceSubsystem::CustomJoinSession(int32 SessionIndex)
{
	JoinGameSession(SearchResults[SessionIndex]);
}

void UMyGameInstanceSubsystem::DestroySession()
{
	if (!Session.IsValid())
	{
		return;
	}

	DestroyHandle = Session->AddOnDestroySessionCompleteDelegate_Handle(FOnDestroySessionCompleteDelegate::CreateUObject(this, &UMyGameInstanceSubsystem::OnDestroySessionCompleted));

	if (!Session->DestroySession(NAME_GameSession))
	{
		Session->ClearOnDestroySessionCompleteDelegate_Handle(DestroyHandle);

		return;
	}
}
