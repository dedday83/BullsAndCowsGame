#include <map>
#include "GameLogic.h"
#define TMap std::map

using FString = std::string;
using int32 = int;

FBullsAndCows BullCowCount;

FString FGame::GetHiddenWord() const { return HiddenWord; }
int32 FGame::GetMaxTries() const { return MaxTries; }
int32 FGame::GetCurrentTurn() const { return CurrentTurn; }
bool FGame::IsGameWon(FString PlayerGuess) const { return BullCowCount.Bulls == HiddenWord.length(); } 

// Creates a new instance of the Game class and initializes the values.
FGame::FGame()
{ 
	Reset(); 
}

// Resets the game to the default values.
void FGame::Reset()
{
	MaxTries = 5;
	CurrentTurn = 1;
	HiddenWord = "train";
}

// Checks if the given string is an isogram.
bool FGame::IsIsogram(FString Word) const
{
	TMap<char, bool> Letters;
	for (char l : Word) {
		if (Letters[l] != true) {
			Letters[l] = true;
		}
		else { 
			return false; }
	}
	return true;
}

// Converts a given string to lowercase letters.
FString FGame::ToLowerCase(FString Word) const
{
	FString LowerCaseString = "";

	for (char c : Word) {
		if (c >= 65 && c < 92) {
			LowerCaseString += c + 32; // If in uppercase - convert to lowercase.
		} else {
			LowerCaseString += c; // If in lowercase - stay the same.
		}
	}
	return LowerCaseString;
}

// Checks whether the player's word is valid or not.
EGuessStatus FGame::CheckValidity(FString Word) const
{
	if (Word.length() != HiddenWord.length()) { 
		return EGuessStatus::WrongLength; }
	else if (Word.find_first_not_of("abcdefghijklmnopqrstuvwxyz") != FString::npos) { 
		return EGuessStatus::NotLetters; }
	else if (!IsIsogram(Word)) {
		return EGuessStatus::NotIsogram; }
	else { 
		return EGuessStatus::OK; }
}

// Returns the status of the player's answer.
EPlayAgainStatus FGame::PlayAgain(FString Answer) const
{
	if (Answer[0] == 'y' || Answer[0] == 'Y') {
		return EPlayAgainStatus::Yes;
	} else if (Answer[0] == 'n' || Answer[0] == 'N') {
		return EPlayAgainStatus::No;
	} else {
		std::cout << "You need to enter 'y' for yes or 'n' for no." << std::endl;
		return EPlayAgainStatus::Invalid;
	}
}

// Checks for bulls and cows in the player's word and increments bulls and cows count.
FBullsAndCows FGame::CheckBullsAndCows(FString Word) 
{
	int WordLength = Word.length(); // Assuming the length of the player's word is the same 
								    // as the length of the hidden word.

	// Loop through all letters in the player's word and the hidden word.
	for (int32 i = 0; i < WordLength; i++) 
	{	
		// Compare letters against the hidden word.
		for (int32 j = 0; j < WordLength; j++) 
		{	
			// If the letters match.
			if (Word[i] == HiddenWord[j]) 
			{
				// The letters are in the same place.
				if (i == j) {
					BullCowCount.Bulls++; }
				else {
					BullCowCount.Cows++; } 
			}
		}
	}
	return BullCowCount;
}

// Moves to the next turn.
void FGame::NextTurn() 
{ 
	BullCowCount.Bulls = 0;
	BullCowCount.Cows = 0;
	CurrentTurn++; 
}