/* Header file for FBullCowGame
The game is a simple guess the word game based on Mastermind
*/

#pragma once
#include <string>

//Making it more like Unreal's Coding standards for an easier transition (FString is a mutable (Something we can change and minipulate) so we dont want user interaction with them)
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EWordStatus
{
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	Invalid_Status
};

class FBullCowGame 
{
public:
	FBullCowGame(); 

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EWordStatus ValidityOfGuess(FString) const;

	void Reset(); 
	FBullCowCount SubmitValidGuess(FString);

private:
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

	int32 MyCurrentTry;
	bool bIsWon;
	FString MyHiddenWord;

};