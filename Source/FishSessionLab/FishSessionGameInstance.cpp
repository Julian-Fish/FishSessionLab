// Fill out your copyright notice in the Description page of Project Settings.


#include "FishSessionGameInstance.h"
#include <OnlineSubsystem.h>
#include <OnlineSessionSettings.h>
#include "Helper/LogHelper.h"
#include "Engine/EngineBaseTypes.h"


UFishSessionGameInstance::UFishSessionGameInstance()
{
	//UE_LOG_FISH("new log marco test: %s", "fish");
}

void UFishSessionGameInstance::Init()
{
	UE_LOG_FISH("Init GameInstance");
	if (IOnlineSubsystem* _subsystem = IOnlineSubsystem::Get())
	{
		_session = _subsystem->GetSessionInterface();

		if (_session.IsValid())
		{
			_session->OnCreateSessionCompleteDelegates.AddUObject(this, &UFishSessionGameInstance::_onCreateSessionComplete);
			_session->OnFindSessionsCompleteDelegates.AddUObject(this, &UFishSessionGameInstance::_onFindSessionComplete);
			_session->OnJoinSessionCompleteDelegates.AddUObject(this, &UFishSessionGameInstance::_onJoinSessionComplete);
			_session->OnDestroySessionCompleteDelegates.AddUObject(this, &UFishSessionGameInstance::_onDestroySessionComplete);
		}
	}
	else
	{
		UE_LOG_SCREEN("init online subsystem failed");
	}

}

void UFishSessionGameInstance::CreateServer()
{
	FUniqueNetIdRepl userid = GetFirstGamePlayer()->GetPreferredUniqueNetId();

	FOnlineSessionSettings SessionSettings;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bIsLANMatch = true;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.NumPublicConnections = 4;

	if (_session->CreateSession(*userid, FName("Fish Test Session"), SessionSettings))
	{
		// create successed
		UE_LOG_SCREEN("create session succeeded");
	}
	else
	{
		// create failed
		UE_LOG_SCREEN("create session failed");
	}
}

void UFishSessionGameInstance::FindServer()
{
	FUniqueNetIdRepl userid = GetFirstGamePlayer()->GetPreferredUniqueNetId();
	//FOnlineSessionSearch SessionSearchSetting;
	_sessionSearch = MakeShareable(new FOnlineSessionSearch());

	_sessionSearch->bIsLanQuery = true;
	_sessionSearch->MaxSearchResults = 20;
	_sessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	if (_session->FindSessions(*userid, _sessionSearch.ToSharedRef()))
	{
		// found sessions
	}
	else
	{
		// cannot found sessions
		_onFindSessionComplete(false);
	}
}


bool UFishSessionGameInstance::JoinServer()
{
	bool succeeded = false;

	FUniqueNetIdRepl userid = GetFirstGamePlayer()->GetPreferredUniqueNetId();
	if (_session.IsValid() && userid.IsValid())
	{
		succeeded = _session->JoinSession(*userid, FName("Fish Test Session"), _sessionSearch->SearchResults[0]);
	}

	return succeeded;
}

void UFishSessionGameInstance::DestroyServer()
{
	_session->DestroySession(FName("Fish Test Session"));
}


void UFishSessionGameInstance::_onCreateSessionComplete(FName serverName, bool succeeded)
{
	if (succeeded)
	{
		UE_LOG_FISH("create session(%s) succeeded", *(serverName.ToString()));
		//UGameplayStatics::OpenLevel(GetWorld(), TEXT("FirstPersonExampleMap"), true, "listen");
		GetWorld()->ServerTravel("/Game/FirstPersonCPP/Maps/FirstPersonExampleMap?listen");
	}
}

void UFishSessionGameInstance::_onFindSessionComplete(bool succeeded)
{
	
	if (succeeded & _sessionSearch != NULL)
	{
		UE_LOG_FISH("find session succeeded");
		UE_LOG_SCREEN("Search Results Numbers: %d", _sessionSearch->SearchResults.Num())
		if (_sessionSearch->SearchResults.Num() > 0)
		{
			for (int i = 0; i < _sessionSearch->SearchResults.Num(); ++i)
			{
				UE_LOG_SCREEN("Session %d : %s", i + 1, *(_sessionSearch->SearchResults[i].Session.OwningUserName));
			}
		}
	}
	else
	{
		UE_LOG_FISH("cannot find session");
	}

	
}

void UFishSessionGameInstance::_onJoinSessionComplete(FName serverName, EOnJoinSessionCompleteResult::Type Result)
{
	
	switch (Result)
	{
		// success
		case 0: 
			UE_LOG_SCREEN("join session(%s) successed", *(serverName.ToString()));
			if (APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
			{
				FString JoinAddress = "";
				_session->GetResolvedConnectString(serverName, JoinAddress);
				if (JoinAddress != "")
				{
					UE_LOG_SCREEN("client trvel to %s", *JoinAddress);
					PController->ClientTravel(JoinAddress, ETravelType::TRAVEL_Absolute, true);
				}
			}
			break;
		// full
		case 1:
			UE_LOG_SCREEN("session(%s) is full", *(serverName.ToString()));
			break;
		// not exist
		case 2:
			UE_LOG_SCREEN("session(%s) is not exist", *(serverName.ToString()));
			break;
		//unknown error
		case 5:
			UE_LOG_SCREEN("join session(%s) failed: unknown error", *(serverName.ToString()));
			break;
	}
}

void UFishSessionGameInstance::_onDestroySessionComplete(FName serverName, bool succeeded)
{
	if (succeeded)	UE_LOG_FISH("destroy session(%s) succeeded", *(serverName.ToString()));
}
