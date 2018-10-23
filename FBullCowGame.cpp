#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map //Making it more like Unreal's Coding standards for an easier transition 

using int32 = int; 

FBullCowGame::FBullCowGame(){ Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ {3, 4}, {4,7}, {5,10}, {6,10} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "amber"; //THIS MUST BE AN ISOGRAM
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bIsWon = false;
	
	return;
}

EWordStatus FBullCowGame::ValidityOfGuess(FString Guess) const
{
	if (!IsIsogram(Guess))	//if the guess isn't an isogram
	{
		return EWordStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))	// if the guess isn't all lowercase
	{
		return EWordStatus::Not_Lowercase;
	}
	else if (GetHiddenWordLength() != Guess.length())	// if world length is wrong
	{
		return EWordStatus::Wrong_Length;
	}
	else // otherwise return OK 
	{
		return EWordStatus::OK;
	}

}

// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;//increment turn number 

	//setup a return variable
	FBullCowCount BullCowCount;

	int32 HiddenWordLength = MyHiddenWord.length();

	// loop through all letters in the guess
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++) 
	{
		// compare letters against the correct word
		for (int32 GuessChar = 0; GuessChar < HiddenWordLength; GuessChar++) 
		{
			//if they match
			if (Guess[GuessChar] == MyHiddenWord[MHWChar])
			{
				//incriment bulls if they're in the same place
				if (GuessChar == MHWChar)
				{
					BullCowCount.Bulls++;
				}
				//incriment cows if not 
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == MyHiddenWord.length()) { bIsWon = true; }
	else { bIsWon = false; }
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const  //order O(n) hash table  
{
	//treat 0 and 1 letter strings as an isogram.
	if (Guess.length() <= 1) { return true; }
	
	TMap<char, bool> LetterSeen; //setup map
	for (char Letter : Guess)  // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed letters
		if (LetterSeen[Letter] == false) //taking the users guess this will start at the begining of the word moving one letter down at a time keeping track of each letter 
		{
			LetterSeen[Letter] = true;
		}
		else //once a letter is repeated (over count 1) return that it isn't an isogram
		{
			return false;
		}
	}
	
	return true; 
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	//Take in a guess, Look through the guesses characters, 
	for (char Letter : Guess)
	{
		//if any character is not lowercase inform the user. 
		if (Letter != tolower(Letter))
		{
			return false;
		}
		else 
		{ 
			return true; 
		}
	}
	return true;
}
