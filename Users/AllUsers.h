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
	map<string, unsigned int> dictionary;

public:

	AllUsers();

	~AllUsers();

	
	//returns score if user is in the system
	//otherwise, adds the user to the system with a score of 0
	unsigned int whatsMyScore(string name);

	//called when the bot loads
	bool addToDictionary(string name, unsigned int score);

	//called when the bot loads
	bool loadScores(string filename);

	//called every time scores are updated (after events)
	bool saveScores(string filename);

	//update a user's score
	bool updateScore(string name, unsigned int newScore);
};

#endif // !ALLUSERS_H
