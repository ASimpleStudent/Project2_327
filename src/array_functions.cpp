/*
 * array_functions.cpp
 *
 *
 *      Author: Adam Stillabower
 */

//============================================================================
//	Necessary includes here
//============================================================================
#define ARRAY_FUNCTIONS_H_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "array_functions.h"
#include "utilities.h"
#include "constants.h"
using namespace constants;
using namespace std;


//============================================================================
// Functions
//============================================================================

/*
 * define a structure to track words and number of times they occur
 */
struct reference {
	string word;
	int num_instances;
};

/*
 * add a global array of entry structs (global to this file)
 */
reference globalReferenceArray[150];

/*
 * variable to keep track of next available slot in array
 * variable to keep track of how many entries in globalReferenceArray
 * variable to determine whether or not a token is correct
 * boolean function success indicator
 * boolean function failure indicator
 * two temporary reference structs for comparison
 * two temporary string for comparison
 */
int nextAvailSlot = 0;
int uniqueWords = 0;
bool isCorrectToken = false;
bool BOOL_SUCCESS = true;
bool BOOL_FAILURE = false;
reference tempRef1;
reference tempRef2;
string tempWord1 = "";
string tempWord2 = "";


/*
 * zero out array that tracks words and their occurrences
 */
void clearArray() {
	for (int i = 0; i < nextAvailSlot; i++) {
		globalReferenceArray[i].word = "";
		globalReferenceArray[i].num_instances = 0;
	}
	nextAvailSlot = 0;
	uniqueWords = 0;
}

/*
 * how many unique words are in array
 */
int getArraySize() {
	return uniqueWords;
}

/*
 * Gets the word at a given location
 */
std::string getArrayWordAt(int i) {
	return globalReferenceArray[i].word;
}

/*
 * Gets the number of instances of the word at the given location
 */
int getArrayWord_NumbOccur_At(int i) {
	return globalReferenceArray[i].num_instances;
}

/*
 * Keep track of how many times each token seen
 */
void processToken(std::string &token) {
	strip_unwanted_chars(token);
	if (token != " " && token != "") {
		isCorrectToken = false;

		for (int i = 0; i < nextAvailSlot; i++) {
			tempWord1 = token;
			tempWord2 = globalReferenceArray[i].word;
			toUpper(tempWord1); toUpper(tempWord2);
			if (globalReferenceArray[i].word == token || globalReferenceArray[i].word == tempWord1 || tempWord1 == tempWord2) {
				globalReferenceArray[i].num_instances++;
				isCorrectToken = true;
			}
		}
		tempWord1 = "";
		tempWord2 = "";

		if (isCorrectToken == false) {
			globalReferenceArray[nextAvailSlot].word = token;
			globalReferenceArray[nextAvailSlot].num_instances = 1;
			nextAvailSlot++;
			uniqueWords++;
		}
	}
}

/*
 * This function takes myString and searches for tokens separated by
 * constants::CHAR_TO_SEARCH_FOR (a space). This constant is defined in file
 * constants.h. For each token it finds it calls ProcessToken( tempToken).
 */
void extractTokensFromLine(std::string &myString) {
	stringstream ss(myString);
	string tempToken;
	while (getline(ss, tempToken, CHAR_TO_SEARCH_FOR)) {
		processToken(tempToken);
	}
}

/*
 * take 1 line and extract all the tokens from it
 *  feed each token to processToken for recording
 */
void processLine(std::string &myString) {
	extractTokensFromLine(myString);
}

/*
 * loop through whole file, one line at a time
 * call processLine on each line
 * returns false: myfstream is not open
 *         true: otherwise
 */
bool processFile(std::fstream &myfstream) {
	if (!myfstream.is_open()) {
		return BOOL_FAILURE;
	}
	else {
		string input;
		while (!myfstream.eof()) {
			getline(myfstream, input);
			processLine(input);
		}
		return BOOL_SUCCESS;
	}
}

/*
 * a function to open a file to read from or write to
 */
bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode) {
	myfile.open(myFileName);
	if (myfile.is_open()) {
		return BOOL_SUCCESS;
	}
	else {
		return BOOL_FAILURE;
	}
}

/*
 * if myfile is open then close it
 */
void closeFile(std::fstream& myfile) {
	if (myfile.is_open()) {
		myfile.close();
	}
}

/*
 * serializes all content in myEntryArray to file outputfilename
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 * 			SUCCESS if all data is written and outputfilename closes OK
 */
int writeArraytoFile(const std::string &outputfilename) {
	ofstream output;
	output.open(outputfilename);
	if (uniqueWords == 0 || nextAvailSlot == 0) {
		return FAIL_NO_ARRAY_DATA;
	}
	else if (!output.is_open()) {
		return FAIL_FILE_DID_NOT_OPEN;
	}
	for (int i = 0; i < nextAvailSlot; i++) {
		output << "" + globalReferenceArray[i].word + " " + to_string(globalReferenceArray[i].num_instances) + "\n";
	}
	output.close();
	return SUCCESS;
}

/*
 * Sort globalReferenceArray based on the sortOrder enum value.
 * The presence of the enum implies a switch statement
 */
void sortArray(constants::sortOrder so) {
	switch(so) {
	case NONE:
		break;
	case NUMBER_OCCURRENCES:
		for (int i = 0; i < nextAvailSlot; i++) {
			for (int j = 0; j < nextAvailSlot; j++) {
				if (globalReferenceArray[j].num_instances < globalReferenceArray[j + 1].num_instances) {
					tempRef1 = globalReferenceArray[j];
					tempRef2 = globalReferenceArray[j + 1];
					globalReferenceArray[j] = tempRef2;
					globalReferenceArray[j + 1] = tempRef1;
				}
			}
		}
		break;
	case DESCENDING:
		for (int i = 0; i < nextAvailSlot; i++) {
			for (int j = 0; j < nextAvailSlot - 1; j++) {
				tempWord1 = globalReferenceArray[j].word;
				tempWord2 = globalReferenceArray[j + 1].word;
				toUpper(tempWord1); toUpper(tempWord2);
				if (tempWord1 < tempWord2) {
						tempRef1 = globalReferenceArray[j];
						tempRef2 = globalReferenceArray[j + 1];
						globalReferenceArray[j] = tempRef2;
						globalReferenceArray[j + 1] = tempRef1;
					}
				}
		}
		break;
	case ASCENDING:
		for (int i = 0; i < nextAvailSlot; i++) {
				for (int j = 0; j < nextAvailSlot - 1; j++) {
					tempWord1 = globalReferenceArray[j].word;
					tempWord2 = globalReferenceArray[j + 1].word;
					toUpper(tempWord1); toUpper(tempWord2);
					if (tempWord1 > tempWord2) {
						tempRef1 = globalReferenceArray[j];
						tempRef2 = globalReferenceArray[j + 1];
						globalReferenceArray[j] = tempRef2;
						globalReferenceArray[j + 1] = tempRef1;
					}
				}
		}
		break;
	}
}


