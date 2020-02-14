/*
Exploration.cpp
Implementation of exploration minigame for stream chat
Oliver X. (Liversticks)
*/

#include "Exploration.h"

Exploration::Exploration(): gameObject(), gameThread(NULL), gameHasBegun(false), readyToAccept(false), aSocket(NULL), chatMessage(""), whereGo(""), playerList(""), dungeonList("")  {
	lastGameFinish = chrono::system_clock::now();
}

bool Exploration::setSocketAndFiles(Socket* a, string dungeons, string players) {
	aSocket = a;
	dungeonList = dungeons;
	playerList = players;
	return true;
}

bool Exploration::prepareGame() {
	ifstream f(dungeonList.c_str());
	string input;
	while (!f.eof()) {
		getline(f, input);
		dungeonNames.push_back(input);
	}
	f.close();
	gameObject.loadScores(playerList);
	//set up theGame thread
	gameThread = new thread(&Exploration::theGame, this);
	return true;
}

bool Exploration::inGame() {
	return gameHasBegun.load(memory_order_relaxed);
}

bool Exploration::inAccept() {
	return readyToAccept.load(memory_order_relaxed);
}

void Exploration::addPlayingUser(string username) {
	if (whoIsPlaying.empty()) {
		chatMessage = Lib::formatChatMessage(username + " calls the Society of Explorers to seek treasure in " + whereGo + "! Type !join to join the exploration party!");
		TwitchCommandLimit::fetchInstance().AddCommand(chatMessage);
	}
	//check to make sure usernames are not already in whoIsPlaying
	//use a set to avoid duplicates

	//to add: way of preventing data races!
	mtx.lock();
	whoIsPlaying.insert(username);
	mtx.unlock();
}

bool Exploration::awardPoints() {
	//iterate all members of whoIsPlaying and update their scores in gameObject
	//concurrently, update the chat message
	chatMessage = "After a long, hard day in the " + whereGo + ", here are the explorers' spoils: ";
	normal_distribution<double> distribution(50, 10);
	mt19937 generator(chrono::system_clock::now().time_since_epoch().count());
	unsigned int temp;
	int size = whoIsPlaying.size();
	for (set<string>::iterator itr = whoIsPlaying.begin(); itr != whoIsPlaying.end(); itr++) {
		temp = (unsigned int)distribution(generator);
		chatMessage = chatMessage + *itr + "(" + to_string(temp) + ")";
		if (size > 1) {
			chatMessage += ", ";
		}
		size--;
		gameObject.updateScore(*itr, temp);
	}
	whoIsPlaying.clear();
	chatMessage = Lib::formatChatMessage(chatMessage);
	TwitchCommandLimit::fetchInstance().AddCommand(chatMessage);
	gameObject.saveScores(playerList);
	return true;
}

Exploration& Exploration::fetchInstance() {
	if (managedSingleton<Exploration>::instance() == NULL) {
		managedSingleton<Exploration>::createInstance();
	}
	return *(managedSingleton<Exploration>::instance());
}

bool Exploration::setupGame() {
	//generate random dungeon
	mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
	//dungeonNames contains at least one element, else will crash
	whereGo = dungeonNames.at(rng() % dungeonNames.size());

	//send chat message to indicate that the game is ready
	//may move this to a separate thread
	chatMessage = Lib::formatChatMessage("Ready to embark on another exploration? Type !join to join the party of explorers headed to " + whereGo + "!");
	TwitchCommandLimit::fetchInstance().AddCommand(chatMessage);

	//update the acceptState to true;
	readyToAccept.store(true, memory_order_relaxed);
	return true;
}

unsigned int Exploration::userScoreIs(string username) {
	return gameObject.whatsMyScore(username);
}


void Exploration::flavourText() {
	chatMessage = Lib::formatChatMessage("All prepared and well-fed, the exploration party heads into the " + whereGo + ", not knowing what to expect.");
	TwitchCommandLimit::fetchInstance().AddCommand(chatMessage);
	
	mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
	switch (rng()%15) {
		case 0:
			chatMessage = Lib::formatChatMessage("While exploring, the party chances upon a Monster House! Fighting valiantly, the explorers defeat the horde and secure a vast trove of loot!");
			break;
		case 1:
			chatMessage = Lib::formatChatMessage("While exploring, the party chances upon a Golden Chamber! But they have no key... That's alright, the rest of the dungeon had some pretty sweet treasure.");
			break;
		case 2: 
			chatMessage = Lib::formatChatMessage("While exploring, the party chances upon a locked door! They successfully force the door open...but it appears that the treasure has been looted by someone else! Oh well, the rest of the dungeon had some good spoils.");
			break;
		case 3:
			chatMessage = Lib::formatChatMessage("While exploring, the party catches a glimpse of a S-Rank outlaw! However, it disappears into the shadows a second later...");
			break;
		case 4:
			chatMessage = Lib::formatChatMessage("While exploring, the party wanders into a mysterious room filled with gadgets. After fiddling with all of them, the floor collapses! Luckily, everyone made it out of the pitfall trap without getting hurt.");
			break;
		case 5:
			chatMessage = Lib::formatChatMessage("While exploring, the party discovers some Hidden Stairs! They clean their items and go for a few grab-bags at the Hidden Bazaar.");
			break;
		default:
			chatMessage = Lib::formatChatMessage("While exploring, the party doesn't encounter anything out of the ordinary and the exploration concludes without incident.");
			break;
	}
	TwitchCommandLimit::fetchInstance().AddCommand(chatMessage);
}

int Exploration::nextGameIn() {
	time_t presentTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
	time_t gameEndTime = chrono::system_clock::to_time_t(lastGameFinish);
	//find the amount of time elapsed between timeNow and lastGameFinish
	//convert to time_t
	return gameEndTime + 240 - presentTime;
}

void Exploration::theGame() {
	while (aSocket) {
		
		setupGame();
		
		//listen for a valid command to begin game
		//here, !join will add players to whoIsPlaying
		while (whoIsPlaying.empty()) {

		}		

		//wait a minute or however many seconds for people to !join
		this_thread::sleep_for(chrono::seconds(60));

		//HANDLED IN CCMD_JOIN_H
		//call addPlayingUser when a user types the command
		//send out a chat message to indicate the start of the game

		//when game starts:
		//ignore commands to join (as !join calls inGame())
		//turn off accepting state
		gameHasBegun.store(true, memory_order_relaxed);
		readyToAccept.store(false, memory_order_relaxed);
		
		flavourText();
		//flavour text here
		//sleep_for to prevent instantaneous execution
		//this_thread::sleep_for(chrono::seconds(4));
		
		//calculate score for users
		//display info in chat message (flavor text)
		awardPoints();
		
		//update gameHasBegun now that the current game is over;
		gameHasBegun.store(false, memory_order_relaxed);
		lastGameFinish = chrono::system_clock::now();
		this_thread::sleep_for(chrono::seconds(240));
		//wait for x seconds until the cooldown period is over

		
	}
	gameThread->join();

}