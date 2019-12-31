/*
Exploration.h
Exploration minigame for stream chat
Oliver X. (Liversticks)
*/

#include "../Users/AllUsers.h"

class Exploration {
	private:
		//dictionary object
		AllUsers gameObject;

		//thread which runs the game
		thread* gameThread;

		//time when game was last concluded (interval between conclusion of game and start of next one)

		//game state - is it accepting (true) or resting (false)?
		bool gameState;

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

		
		//random number generation seed
		unsigned seed;

		//needs to contain some way of accessing the time until the game is ready again in seconds

	public:

		//constructor
		Exploration();

		//initialize (load) game structure
		bool prepareGame(string dungeonList, string playerList);

		//check game state
		bool inGame();

		//send chat message to indicate exploration start
		bool startExploration();

		//listen for users who type command
		void addPlayingUser(string username);

		//send chat message to indicate cooldown
		void concludeGame();

		//award points to participating users
		bool awardPoints();

		//clean up current game instance
		bool cleanupGame();

		//fetch singleton instance
		static Exploration& fetchInstance();

		//game function, run within a separate thread
		void theGame();

		//seeds the seed based on system time
		void seedRNG();


};