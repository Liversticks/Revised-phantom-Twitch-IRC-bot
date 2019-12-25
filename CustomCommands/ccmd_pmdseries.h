/*
ccmd_pmdseries.h
Liversticks (enhanced Phantom) bot
By Oliver X. (liversticks)
*/

#ifndef _CCMD_PMDSERIES_H
#define _CCMD_PMDSERIES_H

#include "CustomCommands.h"

class Command_PMDSeries : public CustomCommand {
	public:
		Command_PMDSeries() : CustomCommand() {

		}

		virtual ~Command_PMDSeries() {

		}

		virtual void Fire(string input) {
			string response = Lib::formatChatMessage("The PMD Series Race will be on January 18-19, 2020. Super, Sky, Gates, and BRT will be run, in that order. More details available at https://pastebin.com/NGA2CF0S");
			TwtichCommandLimit::fetchInstance().AddCommand(response);
		}


};




#endif