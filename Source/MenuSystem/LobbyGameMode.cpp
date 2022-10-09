// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/GameModeBase.h"

void ALobbyGameMode::PostLogin(APlayerController* newPlayer)
{
	Super::PostLogin(newPlayer);

	if (GameState)
	{
		int32 playerCount = GameState.Get()->PlayerArray.Num();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				1,
				60.f,
				FColor::Yellow,
				FString::Printf(TEXT("Players: %d"), playerCount)
			);

			APlayerState* newPlayerState = newPlayer->GetPlayerState<APlayerState>();
			if (newPlayerState)
			{
				FString playerName = newPlayerState->GetPlayerName();
				GEngine->AddOnScreenDebugMessage(
					-1,
					60.f,
					FColor::Cyan,
					FString::Printf(TEXT("%s has joined the game!"), *playerName)
				);
			}
		}
	}
}

void ALobbyGameMode::Logout(AController* exiting)
{
	Super::Logout(exiting);

	APlayerState* exitingPlayerState = exiting->GetPlayerState<APlayerState>();
	if (exitingPlayerState)
	{
		int32 playerCount = GameState.Get()->PlayerArray.Num();
		GEngine->AddOnScreenDebugMessage(
			1,
			60.f,
			FColor::Yellow,
			FString::Printf(TEXT("Players: %d"), playerCount - 1)
		);

		FString playerName = exitingPlayerState->GetPlayerName();
		GEngine->AddOnScreenDebugMessage(
			-1,
			60.f,
			FColor::Red,
			FString::Printf(TEXT("%s has exited the game!"), *playerName)
		);
	}
}
