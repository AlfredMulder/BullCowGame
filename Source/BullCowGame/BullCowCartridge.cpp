// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

auto UBullCowCartridge::BeginPlay() -> void// When the game starts
{
    Super::BeginPlay();

	Isograms = GetValidWords(GWords);
	
	SetupGame();
}

auto UBullCowCartridge::OnInput(const FString& PlayerInput) -> void // When the player hits enter
{
	if (bGameOver)
	{
		ClearScreen();
		SetupGame();
	}
	else 
	{
		ProcessGuess(PlayerInput, Lives);
	}
}

auto UBullCowCartridge::SetupGame() -> void
{
	// Welcoming the Player
	PrintLine(TEXT("Welcome to Bull Cows!"));
	HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
	Lives = HiddenWord.Len() * 2; // Set Lives
	bGameOver = false;
	
	PrintLine(TEXT("Guess the %i letter word!"),HiddenWord.Len());
	// PrintLine(TEXT("The HiddenWord is: %s\n"), *HiddenWord); // Debug Line
	PrintLine(TEXT("You have %i Lives."), Lives);
	PrintLine(TEXT("\nType in your guess and\n press enter to continue..."));
}

auto UBullCowCartridge::EndGame() -> void
{
	bGameOver = true;
	PrintLine(TEXT("\nPress enter to play again."));
}

auto UBullCowCartridge::ProcessGuess(const FString& Guess, int32 Counter) -> void
{
	if (Guess == HiddenWord)
	{
		PrintLine(TEXT("You have Won!"));
		EndGame();
		return;
	}
	
	if (Guess.Len() != HiddenWord.Len())
	{
		
		PrintLine(TEXT("The hidden word is %i letter long"), HiddenWord.Len());
		PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining"), Lives);
		return;
	}

	// Check if Isogram
	if (!IsIsogram(Guess))
	{
		PrintLine(TEXT("No repeating letters, guess again"));
		return;
	}
		
	PrintLine(TEXT("Lost a life!"));
	--Lives;
	if (Lives <= 0)
	{
		ClearScreen();
		PrintLine(TEXT("You have no lives left!"));
		PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
		EndGame();
		return;
	}

	const auto Score = GetBullCows(Guess);

	PrintLine(TEXT("You have %i bulls and %i Cows"), Score.Bulls, Score.Cows);
	
	PrintLine(TEXT("Guess again, you have %i lives left."), Lives);
}

auto UBullCowCartridge::IsIsogram(const FString& Word) -> bool
{
	for (auto Index = 0; Index < Word.Len(); ++Index)
    {
        for (auto Comparison = Index + 1; Comparison < Word.Len(); ++Comparison)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }   
    }
	
	return true;
}

auto UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) -> TArray<FString>
{
	TArray<FString> ValidWords;

	for (auto Word : WordList)
	{
		if ((Word.Len() >= 4) && (Word.Len() <= 8) && (IsIsogram(Word)))
		{
			ValidWords.Emplace(Word);
		}
	}

	return ValidWords;
}

auto UBullCowCartridge::GetBullCows(const FString& Guess) const -> FBullCowCount
{
	FBullCowCount Count;

	// If the index Guess is same as index Hidden, BullCount ++
	// If not a bull was it a cow? If yes CowCount ++

	for (auto GuessIndex = 0; GuessIndex < Guess.Len(); ++GuessIndex)
	{
		if (Guess[GuessIndex] == HiddenWord[GuessIndex])
		{
			Count.Bulls++;
			continue;
		}
		for (auto HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); ++HiddenIndex)
		{
			if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
			{
				Count.Cows++;
				break;
			}
		}
	}
	return Count;
}

