#ifndef CCMD_JOIN_H
#define CCMD_JOIN_H

#include "CustomCommands.h"
#include "../Minigames/Exploration.h"

class Command_Join : public CustomCommand {
public:
	Command_Join() : CustomCommand() {

	}

	virtual ~Command_Join() {

	}

	virtual void Fire(string input) {
		if (!(Exploration::fetchInstance().inGame())) {
			if (Exploration::fetchInstance().inAccept()) {
				string username, message;
				Lib::stripMessage(input, username, message);
				Exploration::fetchInstance().addPlayingUser(username);
				//first user case handled in addPlayingUser
			}
			else {
				string chatMessage = Lib::formatChatMessage("Society of Explorers rules mandate that you wait " + to_string(Exploration::fetchInstance().nextGameIn()) + " seconds until the next party leaves.");
				TwitchCommandLimit::fetchInstance().AddCommand(chatMessage);
			}
		}
		//ignore !join if the game has begun
	}
};



#endif