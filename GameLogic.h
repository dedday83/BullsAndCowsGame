#pragma once
#include <iostream>
#include <string>

using FString = std::string;
using int32 = int;

// A struct to keep track of the number of bulls and cows the player has.
struct FBullsAndCows
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

// An enumeration containing the status for the player's guess.
enum EGuessStatus
{
	OK,
	NotIsogram,
	NotLetters,
	WrongLength,
	
};

// The possible statuses when the player is asked if he wants to play again.
enum EPlayAgainStatus
{
	Yes,
	No,
	Invalid
};

// The class for all the game logic.
class FGame 
{
public:
	FGame(); // The constructor
	FString GetHiddenWord() const;
	int32 GetMaxTries() const;
	int32 GetCurrentTurn() const;
	EGuessStatus CheckValidity(FString) const;	
	bool IsGameWon(FString) const;
	EPlayAgainStatus PlayAgain(FString) const;
	FBullsAndCows CheckBullsAndCows(FString);
	void Reset();
	void NextTurn();
	FString ToLowerCase(FString) const;

private:
	int32 MaxTries;
	int32 CurrentTurn;
	FString HiddenWord;

	bool IsIsogram(FString) const;
};

