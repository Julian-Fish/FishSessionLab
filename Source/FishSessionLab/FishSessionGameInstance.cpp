// Fill out your copyright notice in the Description page of Project Settings.


#include "FishSessionGameInstance.h"
#include <OnlineSubsystem.h>
#include <OnlineSessionSettings.h>
#include "Helper/LogHelper.h"

UFishSessionGameInstance::UFishSessionGameInstance()
{
	//UE_LOG_FISH("new log marco test: %s", "fish");
}

void UFishSessionGameInstance::Init()
{
	UE_LOG_FISH("Init GameInstance");
	
	if (IOnlineSubsystem* subsystem = IOnlineSubsystem::Get())
	{
		_sessionInterface = subsystem->GetSessionInterface();

		if (_sessionInterface.IsValid())
		{
			_sessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UFishSessionGameInstance::_onCreateSessionComplete);
		}
	}

}

void UFishSessionGameInstance::CreateServer()
{
	UE_LOG_FISH("Create Server");
	FOnlineSessionSettings SessionSettings;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bIsLANMatch = true;
	SessionSettings.NumPublicConnections = 4;

	_sessionInterface->CreateSession(0, FName("Fish Test Session"), SessionSettings);
}

void UFishSessionGameInstance::JoinServer()
{

}


void UFishSessionGameInstance::_onCreateSessionComplete(FName serverName, bool succeeded)
{
	UE_LOG_FISH("create session succeeded");
}
