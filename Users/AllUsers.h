/*
AllUsers.h
Uses a dictionary to store user data and info
*/

#ifndef ALLUSERS_H
#define ALLUSERS_H

#include "../Lib/lib.h"

//makes use of a dictionary structure (vector of pairs) to store all users and their associated scores

//file format:
//first line contains the number of users in the file
//each line contains a username, whitespace, then that user's score

class AllUsers {
private:
	vector<pair<string, unsigned int>> dictionary;

public:

	AllUsers();

	~AllUsers();

	//adds a new user to the system with a score of 0 (making sure that the user is not in the system already)
	bool addToDictionary(string name);

	//overloaded addToDictionary for use with file loading
	bool addToDictionary(string name, unsigned int score);

	//returns -1 if the user is not in the dictionary and the index otherwise
	int isInDictionary(string check);

	//returns score if user is in the system, 0 otherwise
	unsigned int whatsMyScore(string name);

	//called when the bot loads
	bool loadScores(string filename);

	//called every time scores are updated (after events)
	bool saveScores(string filename);

	//to add: some sorting algorithm which puts more frequent users near the front of the vector

};

#endif // !ALLUSERS_H
