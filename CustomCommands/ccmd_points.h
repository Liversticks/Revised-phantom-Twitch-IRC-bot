/*
ccmd_points.h
!points command for minigame points
Oliver X. (liversticks)
*/

#ifndef CCMD_POINTS_H
#define CCMD_POINTS_H

#include "CustomCommands.h"
#include "../Minigames/Exploration.h"

class Command_Points : public CustomCommand {

public:
	Command_Points() : CustomCommand() {

	}

	virtual ~Command_Points() {

	}

	virtual void Fire(string input) {
		string username, message;
		Lib::stripMessage(input, username, message);
		unsigned int score = Exploration::fetchInstance().userScoreIs(username);
		string chatMessage = Lib::formatChatMessage(username + ": You have " + to_string(score) + " points.");
		TwitchCommandLimit::fetchInstance().AddCommand(chatMessage);
	}

};
#endif