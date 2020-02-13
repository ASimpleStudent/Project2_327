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
reference globalReferenceArray[100];

/*
 * variable to keep track of next available slot in array
 * variable to keep track of total number of references in the array
 */
int nextAvailSlot = 0;
int uniqueWords = 0;

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

/*loop through whole file, one line at a time
 * call processLine on each line
 * returns false: myfstream is not open
 *         true: otherwise*/
bool processFile(std::fstream &myfstream) {

}

/*take 1 line and extract all the tokens from it
feed each token to processToken for recording*/
void processLine(std::string &myString) {

}

/*Keep track of how many times each token seen*/
void processToken(std::string &token) {

}

/*if you are debugging the file must be in the project parent directory
  in this case Project2 with the .project and .cProject files*/
bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode) {

}
	//mode = std::ios_base::in;



/*iff myfile is open then close it*/
void closeFile(std::fstream& myfile) {

}

/* serializes all content in myEntryArray to file outputfilename
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writeArraytoFile(const std::string &outputfilename) {

}

/*
 * Sort myEntryArray based on so enum value.
 * The presence of the enum implies a switch statement
 */
void sortArray(constants::sortOrder so) {

}


// utilities.h useful functions

/*
 * Uppercase a string,
 */
void toUpper(std::string &myString) {

}

/*
 * Take an int return a string
 */
std::string intToString(int Number) {

}


void strip_char(std::string &s, char badchar) {

}

bool strip_unwanted_chars(std::string &mystring) {

}

