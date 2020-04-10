/*
ccmd_join.h
!join command for exploration minigame
Oliver X. (liversticks)
*/


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
				cout << "Username: " << username << ", Message: " << message << endl;
				Exploration::fetchInstance().addPlayingUser(username);
			}
			else {
				string chatMessage = Lib::formatChatMessage("Society of Explorers rules mandate that you can only join expeditions after successfully unscrambling the destination.");
				TwitchCommandLimit::fetchInstance().AddCommand(chatMessage);
			}
		}
		//ignore !join if the game has begun
	}
};



#endif