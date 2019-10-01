#pragma once
#include "FBullCowGame.h"
#include <map>

// make syntax Unreal Engine friendly
#define TMap std::map
using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries
	{
		{3, 4},
		{4, 7},
		{5, 10},
		{6, 12},
		{7, 20}
	};
	// return the value based on the key(length) of the hidden word.
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";	// this MUST be an ISOGRAM
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!bIsIsogram(Guess)) // if the guess isnt an isogram, return an error
	{
		return EGuessStatus::Not_Isogram; 
	}
	else if (!bIsLowerCase(Guess)) // if the guess isnt all lowercase, return error
	{
		return EGuessStatus::Not_Lowecase; 
	}
	else if (GetHiddenWordLength() != Guess.length()) // if guess length is wrong, return error
	{
		return EGuessStatus::Wrong_Length;
	}
	else // otherwise, return OK
	{
		return EGuessStatus::OK;
	}
}

// receives a valid guess, increments turn, and returns count 
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 GuessWordLength = Guess.length();
	// loop through all letters in guess
	for (int32 GChar = 0; GChar < GuessWordLength; GChar++)
	{
		// loop through all the letters in the hidden word
		for (int32 MHWChar = 0; MHWChar < GetHiddenWordLength(); MHWChar++)
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (GChar == MHWChar)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == GetHiddenWordLength())
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::bIsIsogram(FString Guess) const
{
	/*
	 -> treat 0 and 1 letter-Guess as isograms
	 -> setup the map
	 -> loop through all the letters of the Guess
	 -> if the letter is in the map
		-> no isogram
	-> otherwise, 
		-> add the letter to the map as seen
	 */
	if (Guess.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (auto Letter : Guess)	// range based for loop
	{
		Letter = tolower(Letter);	// handle mixed cases
		if (LetterSeen[Letter] == true)
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true;	// for example in cases where /0 is entered.
}

bool FBullCowGame::bIsLowerCase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}


