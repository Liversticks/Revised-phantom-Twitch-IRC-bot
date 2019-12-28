/*
AllUsers.h
Uses a dictionary to store user data and info
*/

#ifndef ALLUSERS_H
#define ALLUSERS_H

#include "../Lib/lib.h"

//makes use of a dictionary structure (vector of pairs) to store all users and their associated scores

//file format:
//each line contains a username, whitespace, then a password

class AllUsers {
private:
	vector<pair<string, unsigned int>> dictionary;

public:

	AllUsers();

	~AllUsers();

	bool addToDictionary(string name, unsigned int score);

	bool isInDictionary(string check);

	unsigned int whatsMyScore(string name);

	bool loadScores(string filename);

	bool saveScores(string filename);

};

#endif // !ALLUSERS_H
