/*
ccmd_discord.h
Link to the PMD Speedrunning Discord (maybe my own soon?)
Oliver X. (Liversticks)
*/

#ifndef CCMD_DISCORD_H
#define CCMD_DISCORD_H

#include "CustomCommands.h"

class Command_Discord : public CustomCommand {
	public:
		Command_Discord() : CustomCommand() {

		}

		virtual ~Command_Discord() {

		}

		virtual void Fire(string input) {
			string discord = Lib::formatChatMessage("I think I have a Discord? https://discord.gg/2xHwDSg. Also, join the PMD Speedrunning Discord at https://discord.gg/010CVBJffLgZjVlBr.");
			TwitchCommandLimit::fetchInstance().AddCommand(discord);
		}
};
#endif

