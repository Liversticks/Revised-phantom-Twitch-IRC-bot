/*
ccmd_help.h
List of commands and descriptions
Oliver X. (Liversticks)
*/

#ifndef CCMD_HELP_H
#define CCMD_HELP_H

#include "CustomCommands.h"

class Command_Help : public CustomCommand {
	public:
		Command_Help() : CustomCommand() {

		}

		virtual ~Command_Help() {

		}

		virtual void Fire(string input) {
			string help = Lib::formatChatMessage("Commands: !dadjoke, !discord, !join, !hint, !multi, !points, !rules, !top. Most are self-explanatory.");
			TwitchCommandLimit::fetchInstance().AddCommand(help);
		}
};

#endif // !CCMD_HELP_H


