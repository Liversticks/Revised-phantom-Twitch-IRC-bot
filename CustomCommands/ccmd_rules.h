/*
ccmd_rules.h
Rules (basically link to Twitch Community Standards)
Oliver X. (Liversticks)
*/

#ifndef CCMD_RULES_H
#define CCMD_RULES_H

#include "CustomCommands.h"

class Command_Rules : public CustomCommand {
public:
	Command_Rules() : CustomCommand() {

	}

	virtual ~Command_Rules() {

	}

	virtual void Fire(string input) {
		string chatMessage = Lib::formatChatMessage("Please follow the Twitch Community Standards, available here: https://www.twitch.tv/p/legal/community-guidelines/. In addition, please be respectful of other users in chat.");
		TwitchCommandLimit::fetchInstance().AddCommand(chatMessage);
	}
};

#endif // !CCMD_RULES_H
