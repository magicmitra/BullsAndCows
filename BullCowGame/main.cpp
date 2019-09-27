/* The console executable, that makes use of the BullCow class.
   Acts as the view in an MVC pattern, and is responsible for all
   user interaction. For game logic, see the FBullCowGame Class.
 */

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetGuess();
bool AskToPlayAgain();

FBullCowGame BCGame;

// the entry point for the application
int main()
{	
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0;
}

// print the intro
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram?\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	// loop for the number of turns asking for guesses
	for (int32 i = 1; i <= MaxTries; i++)
	{
		FText Guess = GetGuess(); // TODO: make loop checking  valid

		// submit the valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
		// print the number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;

		std::cout << std::endl;
	}
	
	// TODO: summarize game

	return;
}

// get the guess of the user.
FText GetGuess()
{
	int32 CurrentTry = BCGame.GetCurrentTry();
	std::cout << "Try " << CurrentTry << ". Enter your guess: ";
	FText Guess = "";
	std::getline(std::cin, Guess);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n) ? ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}