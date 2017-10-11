#include "GameLogic.h"

using FText = std::string;
using int32 = int;

FGame BCGame;
int32 MaxTries = BCGame.GetMaxTries();
FText HiddenWord = BCGame.GetHiddenWord();

void PrintIntro();
void PlayGame();
EPlayAgainStatus WantToPlayAgain();
FText GetValidGuess();
void PrintGameSummary(FText);

int main() 
{
	EPlayAgainStatus PlayAgain;
	
	PrintIntro();	
	// The game loop.	
	do {
		PlayGame();
		PlayAgain = WantToPlayAgain();
		if (PlayAgain == EPlayAgainStatus::Yes) { 
			BCGame.Reset(); }			
	} while (PlayAgain != EPlayAgainStatus::No);
	std::cout << "Thanks for playing the game!";
	std::cin.get();
	return 0;
}

// Prints an introduction text to the console.
void PrintIntro() 
{
	std::cout << "Welcome to Bulls & Cows!\n\n";
	std::cout << "A game where your goal is to guess the isogram\n";
	std::cout << "picked by the computer. You have a limited number\n";
	std::cout << "of tries to guess the hidden word.\n";
	std::cout << "After each guess some information is printed to the console:\n\n";
	std::cout << "Bulls = A letter is correct and in the right spot.\n";
	std::cout << "Cows = A letter is correct but at the wrong spot.\n\n";
	std::cout << "Good luck!\n\n";
	return;
}

void PlayGame() {	
	bool bGameIsWon = false;
	FBullsAndCows BullCowCount;
	FText PlayerGuess;

	// Keep asking for guesses while the game is not won and there are still tries remaining.
	while (!bGameIsWon && BCGame.GetCurrentTurn() <= MaxTries) 
	{
		PlayerGuess = GetValidGuess();
		BullCowCount = BCGame.CheckBullsAndCows(PlayerGuess);

		std::cout << "Bulls = " << BullCowCount.Bulls << std::endl;
		std::cout << "Cows = " << BullCowCount.Cows << "\n\n";
		if (BCGame.IsGameWon(PlayerGuess)) { 
			bGameIsWon = true; }
		BCGame.NextTurn(); }
	PrintGameSummary(PlayerGuess);
}

// Continually asks the player if he wants to play again until the answer is valid.
EPlayAgainStatus WantToPlayAgain() 
{
	EPlayAgainStatus PlayAgainStatus;
	FText Answer;

	do {
		std::cout << "Do you want to play again? y/n: ";
		std::getline(std::cin, Answer);
		PlayAgainStatus = BCGame.PlayAgain(Answer);
		std::cout << std::endl;
	} while (PlayAgainStatus == EPlayAgainStatus::Invalid);
	return PlayAgainStatus;
}

// Continually asks the player for a guess until the guess is valid.
FText GetValidGuess() {
	FText PlayerGuess;
	EGuessStatus GuessStatus;

	// Keep looping until a valid input is entered.
	do {
		// Get a guess from the player.
		std::cout << "Try " << BCGame.GetCurrentTurn() << " of " << MaxTries;
		std::cout << " (" << HiddenWord.length() << " letters)" << std::endl;
		std::cout << "Enter your guess: ";
		std::getline(std::cin, PlayerGuess);
		PlayerGuess = BCGame.ToLowerCase(PlayerGuess); // Convert the guess to lowercase letters.

		// Check status and give feedback.
		GuessStatus = BCGame.CheckValidity(PlayerGuess);
		switch (GuessStatus) {
			case EGuessStatus::WrongLength:
				std::cout << "You need to enter a word containing " << HiddenWord.length() << " letters." << "\n"; 
				break;
			case EGuessStatus::NotLetters:
				std::cout << "The word must only contain letters." << "\n";
				break;
			case EGuessStatus::NotIsogram:
				std::cout << "The word you enter must be an isogram (no duplicate letters). " << "\n"; 
				break; }
		std::cout << std::endl;
	} while (GuessStatus != EGuessStatus::OK);
	return PlayerGuess;
}

// Prints the game summary.
void PrintGameSummary(FText PlayerWord) 
{
	if (PlayerWord == HiddenWord) {
		std::cout << "Good job! You guessed the correct word.\n\n"; } 
	else {
		std::cout << "Too bad! You ran out of tries. The correct word was: " << HiddenWord << "\n\n"; }
}