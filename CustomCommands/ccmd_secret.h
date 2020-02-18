/*
secret.h
kudos to you for finding this!
Oliver X. (liversticks)
*/

#ifndef CCMD_SECRET_H
#define CCMD_SECRET_H

#include "CustomCommands.h"

class Command_Secret : public CustomCommand {
	public:
		Command_Secret() : CustomCommand() {

		}

		virtual ~Command_Secret() {

		}

		virtual void Fire(string input) {
			string link;
			mt19937 seed(chrono::system_clock::now().time_since_epoch().count());
			//find more secrets xD
			switch (seed() % 25) {
				case 0:
					link = Lib::formatChatMessage("https://www.youtube.com/watch?v=dQw4w9WgXcQ");
					break;
				case 1:
					link = Lib::formatChatMessage("https://www.youtube.com/watch?v=EjkGGMxyxiA");
					break;
				case 2:
					link = Lib::formatChatMessage("https://www.youtube.com/watch?v=9B8mRKc0GQA");
					break;
				case 3:
					link = Lib::formatChatMessage("https://www.youtube.com/watch?v=wZZ7oFKsKzY");
					break;
				default:
					link = Lib::formatChatMessage("No secret today!");
					break;
			}
			TwitchCommandLimit::fetchInstance().AddCommand(link);
		}


};

#endif // !CCMD_SECRET_H
