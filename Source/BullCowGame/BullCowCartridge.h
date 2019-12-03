// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

USTRUCT()
struct FBullCowCount
{
	GENERATED_BODY()
	
	UPROPERTY()
		int32 Bulls = 0;
	UPROPERTY()
		int32 Cows = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge final : public UCartridge
{
	GENERATED_BODY()

public:
	auto BeginPlay() -> void override;
	auto OnInput(const FString& PlayerInput) -> void override;
	auto SetupGame() -> void;
	auto EndGame() -> void;
	auto ProcessGuess(const FString& Guess, int32 Counter) -> void;
	static auto IsIsogram(const FString& Word) -> bool;
	static auto GetValidWords(const TArray<FString>& WordList) -> TArray<FString>;
	auto GetBullCows(const FString& Guess) const -> FBullCowCount;

	// Your declarations go below!
private:
	UPROPERTY()
		FString HiddenWord;
	UPROPERTY()
		int64 Lives;
	UPROPERTY()
		bool bGameOver;
	UPROPERTY()
		TArray<FString> Isograms;
};
