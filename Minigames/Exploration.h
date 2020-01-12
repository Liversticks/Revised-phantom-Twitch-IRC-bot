/*
Exploration.h
Exploration minigame for stream chat
Oliver X. (Liversticks)
*/
#ifndef EXPLORATION_H
#define EXPLORATION_H

#include "../Users/AllUsers.h"

class Exploration {
private:
	//dictionary object
	AllUsers gameObject;

	//thread which runs the game
	thread* gameThread;

	//time when game was last concluded (interval between conclusion of game and start of next one)

	//game state - has the game begun yet? set to true after accepting is closed
	atomic<bool> gameHasBegun;

	//first accepting state - has a user issued a call to explore yet?
	atomic<bool> readyToAccept;

	//attached socket instance
	Socket* aSocket;

	//stores users participating in the current instance
	//note that the first explorer is located at index 0
	vector <string> whoIsPlaying;

	//stores dungeon names
	vector <string> dungeonNames;

	//for sending messages in chat
	string chatMessage;

	//dungeon name
	string whereGo;

	//file location of dungeon list
	string dungeonList;

	//file location of player list
	string playerList;

	//time_point corresponding to when the last game finished
	chrono::system_clock::time_point lastGameFinish;

public:

	//constructor
	Exploration();

	//set details (socket, dungeon names file, player names file)
	bool setSocketAndFiles(Socket* a, string dungeons, string players);

	//initialize (load) game structure
	bool prepareGame();

	//generate random dungeon, send chat message, and set accepting state to true
	bool setupGame();

	//check game state
	bool inGame();

	//check accepting state
	bool inAccept();

	//listen for users who type command
	void addPlayingUser(string username);

	//award points to participating users
	bool awardPoints();

	//fetch singleton instance
	static Exploration& fetchInstance();

	//game function, run within a separate thread
	void theGame();

	//flavour text for the game
	void flavourText();

	//tells how many seconds until the game is ready again
	int nextGameIn();

	//returns score of specified user
	int userScoreIs(string username);

};

#endif




