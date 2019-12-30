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

		//game state - is it running or resting?
		bool gameState;

		//attached socket instance
		Socket* aSocket;

		//stores users participating in the current instance
		vector <string> whoIsPlaying;


	public:

		//constructor
		Exploration();

		//initialize (load) game structure
		bool prepareGame(string filename);

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

		//update dictionary
		bool updateScores();

		//fetch singleton instance
		static Exploration& fetchInstance();


};