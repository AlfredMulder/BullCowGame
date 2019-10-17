// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge final : public UCartridge
{
	GENERATED_BODY()

	public:
		virtual void BeginPlay() override;
		virtual void OnInput(const FString& Input) override;
		void SetupGame();
		void EndGame();
		void ProcessGuess(FString Guess, int64 Counter);

	// Your declarations go below!
	private:
		FString HiddenWord;
		int64 Lives;
		bool bGameOver;
};
