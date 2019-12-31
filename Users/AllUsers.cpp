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

bool AllUsers::addToDictionary(string name, unsigned int score) {
	pair<string, unsigned int> newUser(name, score);
	dictionary.push_back(newUser);
	return true;
}

int AllUsers::isInDictionary(string check) {
	//check all values of string (dictionary.at(i)).first
	for (int i = 0; i < dictionary.size(); i++) {
		if ((dictionary.at(i).first).compare(check) == 0) {
			return i;
		}
	}
	return -1;
}

unsigned int AllUsers::whatsMyScore(string name) {
	int index = isInDictionary(name);
	if (index != -1) {
		return dictionary.at(index).second;
	}
	return 0;
}

bool AllUsers::loadScores(string filename) {
	ifstream f(filename.c_str());
	string username;
	unsigned int userScore;
	int size;
	f >> size;
	for (int i = 0; i < size; i++) {
		f >> username;
		f >> userScore;
		addToDictionary(username, userScore);
	}
	return true;
}

//after every successful exploration, update scores

bool AllUsers::saveScores(string filename) {
	ofstream f(filename.c_str());
	f << (dictionary.size() + 1) << endl;
	for (int i = 0; i < dictionary.size(); i++) {
		f << dictionary.at(i).first << " " << dictionary.at(i).second << endl;
	}
	f.close();
	return true;
}

bool AllUsers::updateScore(string name, unsigned int newScore) {
	int a = isInDictionary(name);
	if (a >= 0 && a < dictionary.size()) {
		dictionary.at(a).second += newScore;
	}
	else {
		addToDictionary(name, newScore);
	}
	return true;
}

bool AllUsers::comparison(pair<string, unsigned int> &a, pair<string, unsigned int> &b) {
	return a.second > b.second;
}

bool AllUsers::sortByScore() {
	std::sort(dictionary.begin(), dictionary.end(), &comparison);
	return true;
}

