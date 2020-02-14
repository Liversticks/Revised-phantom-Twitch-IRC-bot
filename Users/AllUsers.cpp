/*
AllUsers.cpp
implementations of methods in AllUsers.h
Oliver X. (Liversticks)
*/

#include "AllUsers.h"

AllUsers::AllUsers() {

}

AllUsers::~AllUsers() {

}

//only called during startup
bool AllUsers::addToDictionary(string name, unsigned int score) {
	dictionary.insert(pair<string, unsigned int>(name, score));
	return true;
}

unsigned int AllUsers::whatsMyScore(string name) {
	unsigned int myScore = 0;
	try {
		myScore = dictionary.at(name);
	}
	catch (exception & e) {
		dictionary.insert(pair<string, unsigned int>(name, 0));
	}
	return myScore;
}

bool AllUsers::loadScores(string filename) {
	ifstream f(filename.c_str());
	string username;
	unsigned int userScore;
	while (f>> username && f >> userScore) {
		addToDictionary(username, userScore);
	}
	return true;
}

//after every successful exploration, update scores
//change the file format to just contain names/scores in alphabetical order
bool AllUsers::saveScores(string filename) {
	ofstream f(filename.c_str());
	map<string, unsigned int>::iterator itr;
	for (itr = dictionary.begin(); itr != dictionary.end(); itr++) {
		f << itr->first << " " << itr->second << endl;
	}
	f.close();
	return true;
}

bool AllUsers::updateScore(string name, unsigned int newScore) {
	map<string, unsigned int>::iterator itr = dictionary.find(name);
	if (itr != dictionary.end()) {
		itr->second+=newScore;
		return true;
	}
	dictionary.insert(pair<string, unsigned int>(name, newScore));
	return true;
}


