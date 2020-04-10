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
	//for sending messages in chat
	string chatMessage;

	//dictionary object
	AllUsers gameObject;

	//file location of dungeon list
	string dungeonList;

	//file location of town list
	string townList;

	//file location of special locations
	string specialList;

	//file location of player list
	string playerList;

	//thread which runs the game
	thread* gameThread;

	//mutex object to lock thread
	mutex mtx;

	//game state - has the game begun yet? set to true after accepting is closed
	atomic<bool> gameHasBegun;

	//first accepting state - has a user issued a call to explore yet?
	atomic<bool> readyToAccept;

	//whether incoming messages need to be parsed for anagram matching
	atomic<bool> parseAnagram;

	//attached socket instance
	Socket* aSocket;

	//stores dungeon names
	vector <string> dungeonNames;

	//array counter for dungeonNames
	int dungeonCounter;

	//0 == dungeon, 1 == town, 2 == Illusory Grotto/Mystery House/Uncharted Road etc.
	int placeType;

	//stores town names
	vector <string> townNames;

	//stores special names
	vector <string> specialNames;

	//dungeon, town, or special name
	string whereGo;

	//anagram - scrambled
	string anagram;

	//player which guessed anagram correctly
	string correctGuesser;

	//stores users participating in the current instance
	set <string> whoIsPlaying;

	//scaling factor for scoring
	double scoreFactor;

	//time_point corresponding to when the last game finished
	chrono::system_clock::time_point lastGameFinish;

	//flavour text for the game
	void flavourText();

	//award points to participating users
	bool awardPoints();

	//creates an anagram from the placeNames and returns it 
	void makeAnagram();

public:

	//constructor
	Exploration();

	//set details (socket, dungeon names file, player names file)
	bool setSocketAndFiles(Socket* a, string dungeons, string towns, string special, string players);

	//initialize (load) game structure, called from main bot
	bool prepareGame();

	//generate random dungeon, send chat message, and set accepting state to true
	bool setupGame();

	//game function, run within a separate thread
	void theGame();

	//fetch singleton instance
	static Exploration& fetchInstance();
	
	//check game state
	bool inGame();

	//check accepting state
	bool inAccept();

	//check anagram state
	bool inAnagram();

	//listen for users who type command
	void addPlayingUser(string username);

	//tells how many seconds until the game is ready again
	int nextGameIn();

	//fetch whereGo (for external use)
	string whereGoFetch();

	//used by TwitchPrivMsg to pass the player's name back
	void whoWon(const string winner);

	//used by TwitchPrivMsg to set atomic isAnagram to false
	void setAnagramFalse();

	//returns score of specified user
	unsigned int userScoreIs(string username);

	//returns size of topScorers container
	int topScoreSize();

	//linear search for top scorers
	void fillTopScore();

	//returns a reference to the topScorers vector in the gameObject
	vector<pair<string, unsigned int>>& top15Vector();

};

#endif




