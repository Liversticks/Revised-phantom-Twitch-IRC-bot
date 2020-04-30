/*
top.h
Displays the top (up to 15) scorers
Oliver X. (liversticks)
*/

#ifndef CCMD_TOP_H
#define CCMD_TOP_H

#include "CustomCommands.h"
#include "../Minigames/Exploration.h"

class Command_Top : public CustomCommand {
	public:
		Command_Top(): CustomCommand() {
			
		}
		
		virtual ~Command_Top() {
			
		}
		
		virtual void Fire(string input) {
			string topList = "The top scorers are: ";
			//fillTopScore tells the AllUsers object within the Exploration minigame to generate the list of top-scorers
			Exploration::fetchInstance().fillTopScore();
			//Up to 15 names will be displayed
			int sizeOfList = (Exploration::fetchInstance().topScoreSize() < 15) ? Exploration::fetchInstance().topScoreSize() : 15;
			//Top scorers stored in a vector generated each time via fillTopScore()
			vector<pair<string, unsigned int>> listOfTop = Exploration::fetchInstance().top15Vector();
			//chat format: (ranking) playerName: playerScore
			for (int i = 0; i < sizeOfList; i++) {
				topList += "(" + to_string(i + 1) + ") " + listOfTop.at(i).first + ": " + to_string(listOfTop.at(i).second);
				if (i < sizeOfList - 1) {
					topList += ", ";
				}
			}
			string sendTopList = Lib::formatChatMessage(topList);
			TwitchCommandLimit::fetchInstance().AddCommand(sendTopList);
			
		}

};

//algorithm for top scorers:
//define a container for the top scorers
//on loading and any time scores are updated: update the container
//when someone calls !top, return a reference to the container





#endif