/*
ccmd_score.h
!score for exploration minigames
Oliver X. (liversticks)
*/

#ifndef CCMD_SCORE_H
#define CCMD_SCORE_H

#include "../Minigames/Exploration.h"
#include "CustomCommands.h"

class Command_Score : public CustomCommand {
	public:
		Command_Score() : CustomCommand() {

		}

		virtual ~Command_Score() {

		}
	
		virtual void Fire(string input) {
			string username, message;
			Lib::stripMessage(input, username, message);
			int score = Exploration::fetchInstance().userScoreIs(username);
			string chatMessage = Lib::formatChatMessage("The score of " + username + " is " + to_string(score));
			TwitchCommandLimit::fetchInstance().AddCommand(chatMessage);
		}


};


#endif // !CCMD_SCORE_H
