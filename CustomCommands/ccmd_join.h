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
		if (Exploration::fetchInstance().inGame()) {
			string username, message;
			Lib::stripMessage(input, username, message);
			Exploration::fetchInstance().addPlayingUser(username);
		}
		else {
			string chatMessage = Lib::formatChatMessage("It is necessary to rest and get stocked up between expeditions. Please wait " + "seconds until the next party leaves.");
			TwitchCommandLimit::fetchInstance().AddCommand(chatMessage);
		}
	}
};



#endif