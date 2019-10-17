// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

auto UBullCowCartridge::BeginPlay() -> void// When the game starts
{
    Super::BeginPlay();

	SetupGame();
	PrintLine(FString::Printf(TEXT("The HiddenWord is: %s\nIt is %i characters long\n"),
		*HiddenWord, HiddenWord.Len())); // Debug Line
}

auto UBullCowCartridge::OnInput(const FString& Input) -> void // When the player hits enter
{
	if (bGameOver)
	{
		ClearScreen();
		SetupGame();
	}
	else 
	{
		ProcessGuess(Input, Lives);
	}
}

auto UBullCowCartridge::SetupGame() -> void
{
	// Welcoming the Player
	PrintLine(TEXT("Welcome to Bull Cows!"));

	HiddenWord = TEXT("cake"); // Set the HiddenWord
	Lives = HiddenWord.Len(); // Set Lives
	bGameOver = false;
	
	PrintLine(TEXT("Guess the %i letter word!"),HiddenWord.Len());
	PrintLine(TEXT("You have %i Lives."), Lives);
	PrintLine(TEXT("\nType in your guess and\n press enter to continue..."));
}

auto UBullCowCartridge::EndGame() -> void
{
	bGameOver = true;
	PrintLine(TEXT("\nPress enter to play again."));
}

auto UBullCowCartridge::ProcessGuess(const FString Guess, int64 Counter) -> void
{
	if (Guess == HiddenWord)
	{
		PrintLine(TEXT("You have Won!"));
		EndGame();
		return;
	}

	// if (!IsIsogram)
	// {
	// 	PrintLine(TEXT("No repeating letters, guess again"));
	// }
	
	if (Guess.Len() != HiddenWord.Len())
	{
		
		PrintLine(TEXT("The hidden word is %i letter long"), HiddenWord.Len());
		PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining"), Lives);
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
	PrintLine(TEXT("Guess again, you have %i lives left."), Lives);
	
}