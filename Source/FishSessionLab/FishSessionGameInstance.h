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
	virtual void JoinServer();

private:
	IOnlineSessionPtr _sessionInterface;

	// complete event
	void _onCreateSessionComplete(FName serverName, bool succeeded);
	
};
