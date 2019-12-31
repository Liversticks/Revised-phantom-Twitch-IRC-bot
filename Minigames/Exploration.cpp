/*
Exploration.cpp
Implementation of exploration minigame for stream chat
Oliver X. (Liversticks)
*/

#include "Exploration.h"

Exploration::Exploration(): gameObject(), gameThread(NULL), gameState(false), aSocket(NULL), chatMessage(""), whereGo("")  {

}

bool Exploration::prepareGame(string dungeonList, string playerList) {
	ifstream f(dungeonList.c_str());
	string input;
	while (!f.eof()) {
		getline(f, input);
		dungeonNames.push_back(input);
	}
	f.close();
	gameObject.loadScores(playerList);
	//seed RNG
	seedRNG();
	//set up theGame thread
	gameThread = new thread(&Exploration::theGame, this);
	return true;
}

bool Exploration::inGame() {
	return gameState;
}

//intended to be called from outside (by a command)
bool Exploration::startExploration() {
	if (!inGame()) {
		//chat message needs to indicate how much time is left on cooldown
		return false;
	}
}

void Exploration::addPlayingUser(string username) {
	whoIsPlaying.push_back(username);
}

bool Exploration::awardPoints() {
	//iterate all members of whoIsPlaying and update their scores in gameObject
	//concurrently, update the chat message
	chatMessage = "After a long, hard day in the" + whereGo + ", here are the explorers' spoils: ";
	normal_distribution<double> distribution(50, 10);
	mt19937 generator(seed);
	int temp;
	while (!whoIsPlaying.empty()) {
		temp = (int)distribution(generator);
		chatMessage = chatMessage + whoIsPlaying.back() + "(" + to_string(temp) + ")";
		if (whoIsPlaying.size() > 1) {
			chatMessage += ", ";
		}
		gameObject.updateScore(whoIsPlaying.back(), temp);
		whoIsPlaying.pop_back();
	}
	chatMessage = Lib::formatChatMessage(chatMessage);
	TwitchCommandLimit::fetchInstance().AddCommand(chatMessage);
	return true;
}

Exploration& Exploration::fetchInstance() {
	if (managedSingleton<Exploration>::instance() == NULL) {
		managedSingleton<Exploration>::createInstance();
	}
	return *(managedSingleton<Exploration>::instance());
}

void Exploration::seedRNG() {
	seed = chrono::system_clock::now().time_since_epoch().count();
}

void Exploration::theGame() {
	while (aSocket) {
		//generate random dungeon
		mt19937 rng(seed);
		//dungeonNames contains at least one element, else will crash
		whereGo = dungeonNames.at(rng() % dungeonNames.size());

		//send chat message to indicate that the game is ready
		chatMessage = Lib::formatChatMessage("Are you ready to embark on another exploration? Type !join to join the party of explorers headed to " + whereGo + "!");
		TwitchCommandLimit::fetchInstance().AddCommand(chatMessage);

		//update the gameState to true;
		gameState = true;

		//listen for a valid command to begin game
		//send out a chat message to indicate the start of the game

		//when game starts:
		
		
		//call addPlayingUser when a user types the command
		//wait x seconds until the game begins

		//when game begins:
		//ignore commands to join

		//calculate score for users
		//display info in chat message (flavor text)
		awardPoints();

		
		//update gameState to false;
		gameState = false;


		//wait for x seconds until the cooldown period is over

		
	}

}