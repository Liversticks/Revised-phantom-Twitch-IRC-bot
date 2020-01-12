/**
	PhantomBot.h
	PhantomBot Project
	By: Robert F. (Phantom139)
**/

#include "include.h"
#include "TwitchIRC/TwitchIRC.h"
#include "Minigames/Exploration.h"

#ifndef PHANTOM_BOT_H
#define PHANTOM_BOT_H

class PhantomBot {
	public:
		PhantomBot();
		~PhantomBot();

		static PhantomBot &fetchInstance();
		void init(vector<string> &config);

	private:
		void run();

		bool initialized;
		bool wantsQuit;

		TwitchIRC *irc;
		Exploration *myMinigame;
		
};

#endif //PHANTOM_BOT_H