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

bool swapPair(const pair<string, unsigned int>& a, const pair<string, unsigned int>& b) {
	return a.second > b.second;
}

void AllUsers::top15Scores() {
	//linear search
	//assume that the vector is already sorted
	//if the last element is greater than the target new element, skip
	//else, push_back, sort, and remove the last element from the vector

	//if there are less than 15 elements in the target vector, add and sort
	//else, add/sort only if the element if bigger than the smallest element
	unsigned int tempscore;
	for (map<string, unsigned int>::iterator itr = dictionary.begin(); itr != dictionary.end(); itr++) {		
		tempscore = itr->second;
		if (topScorers.size() == 0) {
			topScorers.push_back(pair<string, unsigned int>(itr->first, itr->second));
		}
		else if (topScorers.size() < 15 || tempscore > topScorers.back().second) { 
			topScorers.push_back(pair<string, unsigned int>(itr->first, itr->second));
			sort(topScorers.begin(), topScorers.end(), swapPair);
			if (topScorers.size() > 15) {
				topScorers.pop_back();
			}
		}
	}
}

int AllUsers::sizeOfTopScore() {
	return topScorers.size();
}

vector<pair<string, unsigned int>>& AllUsers::returnVector() {
	vector<pair<string, unsigned int>>& myVector = topScorers;
	return myVector;
}