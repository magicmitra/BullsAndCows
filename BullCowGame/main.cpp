#include <iostream>
#include <string>
#include "FBullCowGame.h"

void PrintIntro();
void PlayGame();
std::string GetGuess();
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
	constexpr int WORD_LENGTH = 5;
	std::cout << "Welcome to Bulls and Cows.\n";
	std::cout << "Can you guess the " << WORD_LENGTH;
	std::cout << " letter isogram?\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int MaxTries = BCGame.GetMaxTries();
	// loop for the number of turns asking for guesses
	for (int i = 1; i <= MaxTries; i++)
	{
		std::string Guess = GetGuess(); // TODO: make loop checking  valid

		// submit the valid guess to the game
		// print the number of bulls and cows

		std::cout << "Your guess is: " << Guess << std::endl;
		std::cout << std::endl;
	}
	
	// TODO: summarize game

	return;
}

// get the guess of the user.
std::string GetGuess()
{
	int CurrentTry = BCGame.GetCurrentTry();
	std::cout << "Try " << CurrentTry << ". Enter your guess: ";
	std::string Guess = "";
	std::getline(std::cin, Guess);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n) ? ";
	std::string Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}