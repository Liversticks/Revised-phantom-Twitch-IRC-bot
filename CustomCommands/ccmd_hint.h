/*
ccmd_hint.h
For those who need a Wonder Map or Expedition Gadget
Oliver X. (Liversticks)
*/

#ifndef CCMD_HINT_H
#define CCMD_HINT_H

#include "CustomCommands.h"

class Command_Hint : public CustomCommand {
public:
	Command_Hint() : CustomCommand() {

	}

	virtual ~Command_Hint() {

	}

	virtual void Fire(string input) {
		string hint = Lib::formatChatMessage("Need a Wonder Map or Expedition Gadget? Check out https://bulbapedia.bulbagarden.net/wiki/Category:Pok%C3%A9mon_Mystery_Dungeon and find the locations for each game.");
		TwitchCommandLimit::fetchInstance().AddCommand(hint);
	}

};

#endif // CCMD_HINT_H