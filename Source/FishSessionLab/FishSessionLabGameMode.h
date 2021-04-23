// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FishSessionLabGameMode.generated.h"

UCLASS(minimalapi)
class AFishSessionLabGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFishSessionLabGameMode();

	void PostLogin(APlayerController *newPlayer);
};



