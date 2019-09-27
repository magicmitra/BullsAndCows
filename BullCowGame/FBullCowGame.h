#pragma once
#include <string>

class FBullCowGame
{
public:
	FBullCowGame();
	int GetMaxTries() const;
	int GetCurrentTry() const;
	bool IsGameWon() const;

	void Reset(); // TODO: make a more rich return value
	bool CheckGuessValidity(std::string);
	// provide a method for counting bulls and cows, and increasing try number
private:

	// see constructor for initialization
	int MyCurrentTry;
	int MyMaxTries;
};