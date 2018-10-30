/* This is the main excutable, that makes use of the FBullCowGame class
This is responsible for all user interaction. 
For Game Logic see the FBullCowGame Class.
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//Making it more like Unreal's Coding standards for an easier transition (FText for user interaction) 
using FText = std::string;
using int32 = int;

void PrintIntro();
void StartGame();
FText GetValidGuess();
FText PrintBack(FText);
void PrintGameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game


int main() 
{
	do 
	{
		PrintIntro();
		StartGame();
	} while (AskToPlayAgain() == true);
	std::cout << std::endl;
	return 0;
}

void PrintIntro()
{
	const int32 WORD_LENGTH = BCGame.GetHiddenWordLength();
	std::cout << std::endl;
	std::cout << "Welcome to the Bulls and Cows word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << WORD_LENGTH << " letter isogram I'm thinking of? \n";
	std::cout << std::endl;
	std::cout << "If you get a bull that means there's a letter in the correct place \n";
	std::cout << "If you get a cow then there is a correct letter but it's in the wrong place.\n";
	std::cout << std::endl;
	return;
}

void StartGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	FText Guess = "";

	//loop to get the guesses while the game ISN"T won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl << std::endl;
	}
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess() 
{
	FText Guess = "";
	EWordStatus Status = EWordStatus::Invalid_Status;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		Guess = "";
		std::getline(std::cin, Guess);
	
		//check the status and give feedback
		Status = BCGame.ValidityOfGuess(Guess);
		switch (Status)
		{
		case EWordStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EWordStatus::Not_Isogram:
			std::cout << "Please enter an Isogram. (A word that dosn't repeat letters)\n";
			break;
		case EWordStatus::Not_Lowercase:
			std::cout << "Please enter your guess in lower case.\n";
			break;
		default:
			return Guess;
		}
		std::cout << std::endl;
	} while (Status != EWordStatus::OK); // keep looping till we get no errors 

	return Guess;
}

//repeat the guess back to them
FText PrintBack(FText guess)
{
	std::cout << "Your guess was: " << guess;
	std::cout << std::endl << std::endl;
	return guess;
}

void PrintGameSummary()
{

	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations you guessed the isogram! \n";
	}
	else
	{
		std::cout << "Bad luck, you ran out of attempts. \n";
	}
	return;
}

bool AskToPlayAgain()
{
	PrintGameSummary();
	std::cout << "Do you want to play again with the same isogram? Please input Yes or No: ";
	FText Response = "";
	std::getline(std::cin, Response);

	if (Response[0] == 'y' || Response[0] =='Y')
	{
		return true;
	}
	else if (Response[0] == 'n' || Response[0] == 'N')
	{
		return false;
	}

	std::cout << "Not a recognized responce.";
	std::cout << std::endl << std::endl;

	AskToPlayAgain();
	return false;
}
