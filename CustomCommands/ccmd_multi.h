/* 
ccmd_multi.h - contains links to kadgar/multistreams
Oliver X. (Liversticks)
*/


//needs to be hard-coded before every race
#ifndef CCMD_MULTI
#define CCMD_MULTI

#include "CustomCommands.h"

class Command_Multi : public CustomCommand {
	public:
		Command_Multi() : CustomCommand() {

		}

		virtual ~Command_Multi() {

		}

		virtual void Fire(string input) {
			string multiTwitch;
			if (true) {
				multiTwitch = Lib::formatChatMessage("Not in a race right now, but the multi-stream link is here when I would be.");
			}
			else {
				multiTwitch = Lib::formatChatMessage("https://kadgar.net/live/liversticks/MozzarellaCheez/wh0misDS/hgfin/rioynerisanidiot");
			}
			TwitchCommandLimit::fetchInstance().AddCommand(multiTwitch);
		}
};


#endif // !CCMD_MULTI

