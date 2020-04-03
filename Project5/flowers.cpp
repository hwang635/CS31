#pragma warning(disable:6262)
#define _CRT_SECURE_NO_DEPRECATE
#include "utilities.h"
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const char WORDFILENAME[] = "C:\\Users\\helen\\CS31\\Project5\\words.txt";

int playOneRound(const char words[][MAXWORDLEN +1], int nWords, int wordnum);
int findFlowers(const char words[][MAXWORDLEN + 1], int wordnum, char trialWord[MAXWORDLEN+1]);
int findBees(const char words[][MAXWORDLEN + 1], int wordnum, char trialWord[MAXWORDLEN+1], int numFlowers);

int numLetters(char words[][MAXWORDLEN + 1], int wordnum);
bool isLowercaseLetters(char word[MAXWORDLEN + 1]);
bool inWordList(const char wordList[][MAXWORDLEN + 1], int nWords, char trialWord[MAXWORDLEN + 1]);
bool containsChar(char arr[MAXWORDLEN + 1], char ch);

int main()
{
	const int WORDLISTMAX = 10000;

	//Can hold up to 10,000 CStrings w/ up to 6 letters (+1 for null char)
	char wordList[WORDLISTMAX][MAXWORDLEN + 1] = {0};
	//Holds the actual # of words in array, calls getWords() to fill the wordList from the file
	int numWords = getWords(wordList, WORDLISTMAX, WORDFILENAME);

	//Checks that the file contains the appropriate # of words to play the game
	if (numWords < 1)
		cout << "No words were loaded, so I can't play the game." << endl;
	else if (numWords > WORDLISTMAX)
		cout << "More than the max words were loaded, so I can't play the game." << endl;
	else {
		cout << "How many rounds do you want to play? ";
		int numRounds;
		cin >> numRounds;
		cin.ignore(10000, '\n'); //Because read in a number, will read in a string next

		double scores = 0;
		int minScore = 1;
		int maxScore = 1;

		if (numRounds <= 0)
			cout << "The number of rounds must be positive." << endl;
		else {
			for (int i = 1; i < numRounds + 1; i++) {
				//int wordnum = randInt(0, WORDLISTMAX - 1);
				int wordnum = 0;
				//If the randomly chosen word has 0 letters, it isn't a word ==> find another random index until a word is found
				while (numLetters(wordList, wordnum) == 0) {
					wordnum = randInt(0, WORDLISTMAX - 1);
				}

				cout << endl;
				cout << "Round " << i << endl;
				//cerr << "mystery word = " << wordList[wordnum] << endl;
				cout << "The mystery word is " << numLetters(wordList, wordnum) << " letters long." << endl;

				int currentScore = playOneRound(wordList, WORDLISTMAX, wordnum);
				scores += currentScore;

				if (currentScore == -1) {//If it returns -1 for a bad argument, terminate the program
					cout << "playOneRound() returned -1 for bad argument" << endl;
					return 0;
				}

				if (i == 1) { //Sets the min and max score if this is the first round
					minScore = currentScore;
					maxScore = currentScore;
				}

				//If the current score is less than the current min, set the minimum to the score
				if (minScore > currentScore)
					minScore = currentScore;
				//If the current score is greater than the current max, set the maximum to the score
				if (maxScore < currentScore)
					maxScore = currentScore;

				if (currentScore == 1)
					cout << "You got it in 1 try." << endl;
				else
					cout << "You got it in " << currentScore << " tries." << endl;

				//Outputs average score w/ 2 decimal points
				cout.setf(ios::fixed);
				cout.precision(2);
				cout << "Average: " << scores / i << ", minimum: " << minScore << ", maximum: " << maxScore << endl;
			}
		} //end of numRounds check
	}
}

/*Plays one round of finding flowers/bees, returns the score
  nWords = number of words in words array/wordList, words[wordNum] is the mystery word
  Returns -1 if nWords isn't positive, wordnum is less than 0, or wordnum >= nWords */
int playOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum) {
	if (nWords <= 0) 
		return -1;
	if (wordnum < 0 || wordnum >= nWords)
		return -1;
	
	int score = 0;
	char trialWord[101] = { 0 };

	//Loops until the words are the same
	while(strcmp(words[wordnum], trialWord) != 0) {
		cout << "Trial word: ";
		cin.getline(trialWord, 101);

		if (strlen(trialWord) < 4 || strlen(trialWord) > 6 || !isLowercaseLetters(trialWord))
			cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
		else if (!inWordList(words, nWords, trialWord)) //Inputted word not in wordlist/file
			cout << "I don't know that word." << endl;
		else { //If it is a valid known word, find the # of flowers and bees and increment the # rounds of the score
			if (strcmp(words[wordnum], trialWord) != 0) {
				int numFlowers = findFlowers(words, wordnum, trialWord);
				int numBees = findBees(words, wordnum, trialWord, numFlowers);
				score++;
				cout << "Flowers: " << numFlowers << ", Bees: " << numBees << endl;
			}
		}
	}
	score++; //Increment to account for the matching trial word

	return score;
}

//Returns # of flowers ==> pairing of letter in trial + mystery word at the same index
//Mystery word is words[wordnum], trialWord is the trial word the user entered
int findFlowers(const char words[][MAXWORDLEN + 1], int wordnum, char trialWord[MAXWORDLEN + 1]) {
	int flowerCount = 0;
	int i = 0;

	//Loops through until the shortest word reaches the end of the word
	while (words[wordnum][i] != '\0' && trialWord[i] != '\0') {
		if (words[wordnum][i] == trialWord[i])
			flowerCount++;
		i++;
	}

	return flowerCount;
}

//Returns the # of bees ==> pairing of letter in trial + mystery word not at the same index
//Mystery word is words[wordnum], trialWord is the trial word the user entered, numFlowers is the already found # flowers
int findBees(const char words[][MAXWORDLEN + 1], int wordnum, char trialWord[MAXWORDLEN + 1], int numFlowers) {
	//Stores char that have already been checked, to prevent overcounting repeated letters
	char foundChar[MAXWORDLEN + 1] = { 0 };
	int count = 0;

	int numBees = 0;
	
	int i = 0;
	while (words[wordnum][i] != '\0') {
		char temp = words[wordnum][i];
		
		if (!containsChar(foundChar, temp)) { //If the char hasn't already been checked
			//Finds how many times the current letter (temp) is in the mystery word
			int j = i + 1;
			int mysteryCharCount = 1;
			while (words[wordnum][j] != '\0') {
				if (temp == words[wordnum][j]) //If the char is the same, adds to the count of same char in mystery
					mysteryCharCount++;
				j++;	
			}

			//Finds how many times the current letter (temp) is in the trial word
			int k = 0;
			int trialCharCount = 0;
			while (trialWord[k] != '\0') {
				if (temp == trialWord[k]) //If the char is the same, adds to the count of same char in trial
					trialCharCount++;
				k++;
			}

			//Adds the current character to foundChar and increments count for next position
			foundChar[count] = temp;
			count++;

			//Adds the smaller of the letter counts to find the number of letter pairs
			if (mysteryCharCount <= trialCharCount)
				numBees += mysteryCharCount;
			else
				numBees += trialCharCount;
		}

		i++;
	} //end of big while loop

	return numBees - numFlowers; //Subtracts # of flowers to avoid double-counting flowers as bees
}

//Finds the number of alphabetic letters in the word
int numLetters(char words[][MAXWORDLEN + 1], int wordnum) {
	int count = 0;
	while (words[wordnum][count] != '\0') {
		count++;
	}
	return count;
}


//Returns true if the array arr contains char ch, false if it doesn't contain ch
bool containsChar(char arr[MAXWORDLEN + 1], char ch) {
	int i = 0;

	//Loops through array and returns true if the character is found
	while (arr[i] != '\0') {
		if (arr[i] == ch)
			return true;
		i++;
	}

	return false; //If the character hasn't been found, returns false
}

//Checks that all letters in the string are lowercase
bool isLowercaseLetters(char word[MAXWORDLEN + 1]) {
	int i = 0;
	//Loops through word until finds the null character (end of array)
	while (word[i] != '\0') {
		if (!islower(word[i]) || !isalpha(word[i])) //Returns false if finds a non-lowercase or non-letter
			return false;
		i++;
	}
	return true; //Returns true if the entire string has been checked and no uppercase/non-letter has been found
}

//Checks that the string is stored in the wordlist from the file
bool inWordList(const char wordList[][MAXWORDLEN + 1], int nWords, char trialWord[MAXWORDLEN + 1]) {
	for (int i = 0; i < nWords; i++) {
		//strcmp returns 0 if the strings are equal
		if (strcmp(wordList[i], trialWord) == 0)
			return true;
	}

	return false; //If no equal string has been found, then return false
}