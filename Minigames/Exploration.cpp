/*
Exploration.cpp
Implementation of exploration minigame for stream chat
Oliver X. (Liversticks)
*/

#include "Exploration.h"

#define GAME_COOLDOWN 120

Exploration::Exploration(): gameObject(), gameThread(NULL), gameHasBegun(false), readyToAccept(false), parseAnagram(false), aSocket(NULL), chatMessage(""), whereGo(""), playerList(""), dungeonList(""), townList(""), specialList(""), scoreFactor(1), dungeonCounter(0), placeType(0)  {
	lastGameFinish = chrono::system_clock::now();
}

bool Exploration::setSocketAndFiles(Socket* a, string dungeons, string towns, string special, string players) {
	aSocket = a;
	dungeonList = dungeons;
	townList = towns; 
	specialList = special;
	playerList = players;
	return true;
}

bool Exploration::prepareGame() {
	//load names from filenames
	ifstream f(dungeonList.c_str());
	string input;
	while (!f.eof()) {
		getline(f, input);
		dungeonNames.push_back(input);
	}
	f.close();
	ifstream g(townList.c_str());
	while (!g.eof()) {
		getline(g, input);
		townNames.push_back(input);
	}
	g.close();
	ifstream h(specialList.c_str());
	while (!h.eof()) {
		getline(h, input);
		specialNames.push_back(input);
	}
	h.close();
	gameObject.loadScores(playerList);
	gameObject.top15Scores();
	//set up theGame thread
	//cout << "Loaded all data from files." << endl;
	shuffle(dungeonNames.begin(), dungeonNames.end(), mt19937(chrono::system_clock::now().time_since_epoch().count()));
	this_thread::sleep_for(chrono::seconds(30));
	gameThread = new thread(&Exploration::theGame, this);
	return true;
}

bool Exploration::inGame() {
	return gameHasBegun.load(memory_order_relaxed);
}

bool Exploration::inAccept() {
	return readyToAccept.load(memory_order_relaxed);
}

bool Exploration::inAnagram() {
	return parseAnagram.load(memory_order_relaxed);
}

void Exploration::addPlayingUser(string username) {
	//mutex for data races
	mtx.lock();
	whoIsPlaying.insert(username);
	mtx.unlock();
}

bool Exploration::setupGame() {
	//once the entire dungeon names have been loaded into a vector, shuffle that vector
	//proceed linearly through vector
	//if the end of the vector is reached, reshuffle vector
	if (dungeonCounter == dungeonList.size()) {
		shuffle(dungeonNames.begin(), dungeonNames.end(), mt19937(chrono::system_clock::now().time_since_epoch().count()));
		dungeonCounter == 0;
	}
	mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
	placeType = 0;
	switch (rng() % 50) {
	case 0:
		placeType = 2;
		break;
	case 1:
	case 2:
		placeType = 1;
		break;
	default:
		break;
	}
	if (placeType == 0) {
		whereGo = dungeonNames.at(dungeonCounter);
		dungeonCounter++;
	}
	//for non-dungeon locations, use random generation to choose an index (as before)
	else if (placeType == 1) {
		whereGo = townNames.at(rng() % townNames.size());
	}
	else {
		whereGo = specialNames.at(rng() % specialNames.size());
	}

	//different categories of locations
	//towns - Square, TTown, HS Village, Shaymin Village, Post Town, Paradise, Super towns
	//Dungeons
	//Illusory Grotto, Mystery House, Uncharted Road, Gilded Hall, Secret Bazaar
	//cout << whereGo << endl;
	return true;
}

void Exploration::makeAnagram() {
	string result = whereGo;
	//make all letters lowercase
	int length = result.length();
	for (int i = 0; i < length; i++) {
		result[i] = tolower(result.at(i));
	}

	//break down the string into tokens
	vector<string> tokens;
	size_t size = result.size() + 1;
	char* buffer = new char[size];
	memcpy(buffer, result.c_str(), size);
	//rsize_t strmax = sizeof(buffer);
	char* word = NULL;
	char delim[] = " ";
	char* next_word = NULL;
	word = strtok_s(buffer, delim, &next_word);
	while (word != NULL) {
		tokens.push_back(word);
		word = strtok_s(NULL, delim, &next_word);
	}

	//shuffle each token
	length = tokens.size();
	string resultMessage;
	for (int i = 0; i < length; i++) {
		shuffle(tokens.at(i).begin(), tokens.at(i).end(), mt19937(chrono::system_clock::now().time_since_epoch().count()));
		resultMessage += tokens.at(i);
		resultMessage += " ";
	}

	string resultType;
	if (placeType == 0) {
		resultType = "dungeon";
	}
	else if (placeType == 1) {
		resultType = "town or village";
	}
	else {
		resultType = "mysterious location";
	}

	chatMessage = Lib::formatChatMessage("Unscramble the following " + resultType + ":");
	TwitchCommandLimit::fetchInstance().AddCommand(chatMessage);
	chatMessage = Lib::formatChatMessage(to_string(length) + " words: " + resultMessage);
	TwitchCommandLimit::fetchInstance().AddCommand(chatMessage);
}

void Exploration::flavourText() {
	mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

	if (placeType == 0) {
		chatMessage = Lib::formatChatMessage("All prepared and well-fed, the exploration party heads into " + whereGo + ", not knowing what to expect.");
		TwitchCommandLimit::fetchInstance().AddCommand(chatMessage);
		switch (rng() % 12) {
		case 0:
			chatMessage = Lib::formatChatMessage("While exploring, the party chances upon a Monster House! Fighting valiantly, the explorers defeat the horde!");
			scoreFactor = 1.5;
			break;
		case 1:
		case 2:
			chatMessage = Lib::formatChatMessage("While exploring, the party ambushes a S-Rank outlaw about to perform a nefarious deed! They calmly escort the crook to justice!");
			scoreFactor = 1.5;
			break;
		case 3:
		case 4:
			chatMessage = Lib::formatChatMessage("While exploring, the party wanders into a mysterious room filled with gadgets. After fiddling with all of them, the floor collapses! Luckily, everyone made it out of the pitfall trap without getting hurt.");
			break;
		default:
			chatMessage = Lib::formatChatMessage("While exploring, the party reaches the clearing after the final stairs and the exploration concludes succesfully.");
			break;
		}
	}
	else if (placeType == 1) {
		chatMessage = Lib::formatChatMessage("With cargoes of treasure and ample Poke, the exploration party heads to " + whereGo + " to restock and replenish resources.");
		TwitchCommandLimit::fetchInstance().AddCommand(chatMessage);
		switch (rng() % 8) {
		case 0:
			chatMessage = Lib::formatChatMessage("Checking the Kecleon shop, the party discovers that Perfect Apples are now in stock! Everyone rushes madly to solve their Belly problem once and for all!");
			scoreFactor = 1.25;
			break;
		case 1:
			chatMessage = Lib::formatChatMessage("At an inn, the party provides some food for a hungry travelling Pokemon, who leaves gifts for the group the next morning as thanks!");
			scoreFactor = 1.1;
			break;
		default:
			chatMessage = Lib::formatChatMessage("In town, the party sells surplus treasure, acquires some shiny new equipment, and eats well in preparation for the next adventure.");
			break;
		}
	}
	else {
		//second character is unique
		char key = whereGo[1];
		switch (key) {
		case 'e':
			//Secret Bazaar
			chatMessage = Lib::formatChatMessage("While exploring, the party discovers some Hidden Stairs! They clean their items and get some grab-bags at the Secret Bazaar.");
			scoreFactor = 2;
			break;
		case 'n':
			//Uncharted Road
			chatMessage = Lib::formatChatMessage("While exploring, the mysteriosity spikes! All of a sudden, everyone finds themselves in a strange new dungeon with sparkling tiles everywhere!");
			scoreFactor = 2;
			break;
		case 'i':
			//Gilded Hall
			chatMessage = Lib::formatChatMessage("While exploring, the party chances upon a Gilded Hall! It's so shiny that everyone almost missed the treasure: a great cache of Gold Bars!");
			scoreFactor = 6;
			break;
		case 'l':
			//Illusory Grotto
			chatMessage = Lib::formatChatMessage("While exploring, the party notices the copious amounts of healing items and Revives lying around. It seems like an illusory grotto no one has ever encountered before!");
			scoreFactor = 3;
			break;
		case 'y':
			//Mystery House
			chatMessage = Lib::formatChatMessage("While exploring, the party chances upon a locked door! They successfully force the door open... There's a trove of treasure and a Riolu!");
			scoreFactor = 5;
			break;
		case 'o':
			//Golden Chamber
			chatMessage = Lib::formatChatMessage("While exploring, the party chances upon a Golden Chamber! Unlocking it reveals exclusive items for everyone!");
			scoreFactor = 4;
			break;
		default:
			//idk, how'd you get here?
			chatMessage = Lib::formatChatMessage("While exploring, the party successfully skips a cutscene! Wait, this is supposed to be a debug line! Let the bot developer know that something broke ;(");
			scoreFactor = 100;
			break;
		}

	}
	TwitchCommandLimit::fetchInstance().AddCommand(chatMessage);
}

bool Exploration::awardPoints() {
	//iterate all members of whoIsPlaying and update their scores in gameObject
	//concurrently, update the chat message
	if (placeType == 0) {
		chatMessage = "After a long, hard day in " + whereGo + ", here are the explorers' spoils: ";
	}
	else if (placeType == 1) {
		chatMessage = "After a long night in " + whereGo + ", here are the explorers' profits: ";
	}
	else {
		chatMessage = "After an exciting journey to the " + whereGo + ", here are the explorers' loot: ";
	}

	//the mean of the score distribution should reflect the number of players and the special event, if any
	//the variance of the score distribution should be fairly tight

	normal_distribution<double> distribution((scoreFactor * 30 * (log(whoIsPlaying.size()) + 1)), (whoIsPlaying.size()) / (scoreFactor + 1));
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
	//for the next round
	scoreFactor = 1;
	return true;
}

Exploration& Exploration::fetchInstance() {
	if (managedSingleton<Exploration>::instance() == NULL) {
		managedSingleton<Exploration>::createInstance();
	}
	return *(managedSingleton<Exploration>::instance());
}

int Exploration::nextGameIn() {
	//find the amount of time elapsed between timeNow and lastGameFinish as a duration object
	return GAME_COOLDOWN + (chrono::duration_cast<chrono::duration<double>>(lastGameFinish - chrono::system_clock::now())).count();
}

string Exploration::whereGoFetch() {
	return whereGo;
}

void Exploration::whoWon(const string winner) {
	correctGuesser = winner;
}

void Exploration::setAnagramFalse() {
	parseAnagram.store(false, memory_order_relaxed);
}

void Exploration::theGame() {
	while (aSocket) {
		
		setupGame();
		
		makeAnagram();
		parseAnagram.store(true, memory_order_relaxed);

		//set TwitchIRC modules to filter for correct answer
		
		
		while (inAnagram()) {
			//wait before checking again
			this_thread::sleep_for(chrono::seconds(2));
		}
		//break out of loop when someone guesses the correct location
		
		//award points to first player
		//points scale according to the length of the word
		unsigned int tempScore = 3 * whereGo.length() + 10;
		gameObject.updateScore(correctGuesser,tempScore);
		gameObject.saveScores(playerList);

		if (placeType == 0) {
			chatMessage = Lib::formatChatMessage("Ready to explore? " + correctGuesser + " is leading a group headed to " + whereGo + "! Type !join to join the expedition party!");
		}
		else if (placeType == 1) {
			chatMessage = Lib::formatChatMessage("That was a nice day of exploring! " + correctGuesser + " is leading a group headed back to " + whereGo + " for a well-deserved rest. Type !join to join the group!");
		}
		else {
			chatMessage = Lib::formatChatMessage("Oh? " + correctGuesser + " has found a mysterious place! Type !join for a share of the loot!");
		}
		TwitchCommandLimit::fetchInstance().AddCommand(chatMessage);
		//add winner of unscrambling, it's only fair ;)
		addPlayingUser(correctGuesser);
		correctGuesser = "";
		
		//update the acceptState to true;
		readyToAccept.store(true, memory_order_relaxed);
		//here, !join will add players to whoIsPlaying

				

		//wait a minute or however many seconds for people to !join
		this_thread::sleep_for(chrono::seconds(75));

		//when game starts:
		//ignore commands to join (as !join calls inGame())
		gameHasBegun.store(true, memory_order_relaxed);
		readyToAccept.store(false, memory_order_relaxed);
		
		flavourText();
		//flavour text here and set scale factor for scoring
		
		//calculate score for users and display info in chat message (flavor text)
		awardPoints();
		gameObject.top15Scores();
		
		//update gameHasBegun now that the current game is over and wait for cooldown
		gameHasBegun.store(false, memory_order_relaxed);
		lastGameFinish = chrono::system_clock::now();
		this_thread::sleep_for(chrono::seconds(GAME_COOLDOWN));
		
	}
	gameThread->join();
}

int Exploration::topScoreSize() {
	return gameObject.sizeOfTopScore();
}

void Exploration::fillTopScore() {
	//call function in AllUsers
	gameObject.top15Scores();
}

unsigned int Exploration::userScoreIs(string username) {
	return gameObject.whatsMyScore(username);
}

vector<pair<string, unsigned int>>& Exploration::top15Vector() {
	return gameObject.returnVector();
}