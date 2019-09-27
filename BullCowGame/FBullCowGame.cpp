#include "FBullCowGame.h"

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (false) // if the guess isnt an isogram, return an error
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (false) // if the guess isnt all lowercase, return error
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


