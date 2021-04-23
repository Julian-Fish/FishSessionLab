// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "FishSessionLabGameMode.h"
#include "FishSessionLabHUD.h"
#include "FishSessionLabCharacter.h"
#include "UObject/ConstructorHelpers.h"


AFishSessionLabGameMode::AFishSessionLabGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFishSessionLabHUD::StaticClass();
}

void AFishSessionLabGameMode::PostLogin(APlayerController* newPlayer)
{
	//UELogHelper::LOG_FISH("post login");
	
}
