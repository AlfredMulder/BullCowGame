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
		if (Input == HiddenWord)
		{
			PrintLine(TEXT("You have Won!"));
			EndGame();
		}
		else
		{
			Input.Len() != HiddenWord.Len() ?
				PrintLine(TEXT("The Hidden Word if %i characters long.\nYou have Lost!"), HiddenWord.Len()), EndGame() :
				PrintLine("You have Lost!"), EndGame();
		}
	}
}

auto UBullCowCartridge::SetupGame() -> void
{
	// Welcoming the Player
	PrintLine(TEXT("Welcome to Bull Cows!"));

	HiddenWord = TEXT("cake"); // Set the HiddenWord
	Lives = 4; // Set Lives
	bGameOver = false;
	
	PrintLine(TEXT("Guess the %i letter word!\nType in your guess and press enter to continue..."),
		HiddenWord.Len());
}

auto UBullCowCartridge::EndGame() -> void
{
	bGameOver = true;
	PrintLine(TEXT("Press enter to play again."));
}