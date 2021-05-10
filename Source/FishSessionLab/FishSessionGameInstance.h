// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <Interfaces/OnlineSessionInterface.h>
#include "FishSessionGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FISHSESSIONLAB_API UFishSessionGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UFishSessionGameInstance();

protected:
	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	virtual void CreateServer();

	UFUNCTION(BlueprintCallable)
	virtual bool JoinServer();

	UFUNCTION(BlueprintCallable)
	virtual void FindServer();

	UFUNCTION(BlueprintCallable)
	virtual void DestroyServer();

	IOnlineSessionPtr _session;
	TSharedPtr<FOnlineSessionSearch> _sessionSearch;

	// complete event
	void _onCreateSessionComplete(FName serverName, bool succeeded);
	void _onFindSessionComplete(bool succeeded);
	void _onJoinSessionComplete(FName serverName, EOnJoinSessionCompleteResult::Type Result);
	void _onDestroySessionComplete(FName serverName, bool succeeded);
};
