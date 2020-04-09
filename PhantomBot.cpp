/**
    PhantomBot.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#include "PhantomBot.h"


/*
 PhantomBot Class
*/
PhantomBot::PhantomBot() : irc(NULL) {
	initialized = false;
	wantsQuit = false;
}

PhantomBot::~PhantomBot() {

}

PhantomBot &PhantomBot::fetchInstance() {
	if (managedSingleton<PhantomBot>::instance() == NULL) {
		managedSingleton<PhantomBot>::createInstance();
	}
	return *(managedSingleton<PhantomBot>::instance());
}


void PhantomBot::init(vector<string> &conf) {
	if (initialized) {
		return;
	}
	//Initialize IRC Module and Input Module
	irc = new TwitchIRC(conf[0].c_str(), conf[0].c_str(), conf[4].c_str(), conf[1].c_str(), (U32)atoi(conf[2].c_str()), conf[3].c_str());
	initialized = true;
	//initialized minigame
	myMinigame = new Exploration();
	myMinigame->fetchInstance().setSocketAndFiles(irc->fetchSocket(), "Minigames/Dungeon Names/Global Dungeon Locations.txt", "Minigames/Dungeon Names/Global Town Locations.txt", "Minigames/Dungeon Names/Special Locations.txt", "Users/userdata.txt");
	
	//to-do: add the file names for the minigame into botconfig.txt
	
	run();
}

void PhantomBot::run() {
	myMinigame->fetchInstance().prepareGame();
	while (irc->SocketActive()) {
		irc->Update();
	}
}

/*

 MAIN METHOD
 ENTRY POINT

*/

int main(void) {
	srand((U32)time(NULL));
	//read the config
	ACHAR line[512];
	vector<string> config;
	fstream f("botconfig.txt", ios::in);
	while(!f.eof()) {
		f.getline(line, 512);
		config.push_back(line);
		memset(&line[0], 0, sizeof(line));
	}
	//Set stuff up... requires EXACTLY 5 parameters
	if(config.size() == 5) {
		PhantomBot::fetchInstance().init(config);
	}
	else {
		cout << "There was an error in your 'botconfig.txt' file, contact Phantom139 for support" << endl;
	}
	cout << "Closing program..." << endl;
	return 0;
}
