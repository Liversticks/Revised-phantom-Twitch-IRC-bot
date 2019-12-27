/*
ccmd_dadjoke.h
please no kill me xD
Oliver X. (Liversticks)

*/

#ifndef CCMD_DADJOKE_H
#define CCMD_DADJOKE_H

#include "CustomCommands.h"

class Command_DadJoke : public CustomCommand {
	public:

		Command_DadJoke() : CustomCommand() {

		}

		virtual ~Command_DadJoke() {

		}

		virtual void Fire(string input) {
			string chatMessage;
			//random number generalization
			mt19937 seed(chrono::system_clock::now().time_since_epoch().count());
				switch (seed() % 25) {
				case 0:
					chatMessage = Lib::formatChatMessage("What do prisoners use to call each other? Cell phones.");
					break;
				case 1:
					chatMessage = Lib::formatChatMessage("Did you hear about the shoes I bought from the drug-dealer? I don't know what they've been laced with; I was tripping all day!");
					break;
				case 2:
					chatMessage = Lib::formatChatMessage("Where were the first French fries cooked? Not in France, I've been told, but in Greece.");
					break;
				case 3:
					chatMessage = Lib::formatChatMessage("Don't take legal advice from me, but I think a child who doesn't sleep during nap time is resisting a rest.");
					break;
				case 4:
					chatMessage = Lib::formatChatMessage("I've been reading this book about black holes all day. It has really sucked me in.");
					break;
				case 5:
					chatMessage = Lib::formatChatMessage("What's the least spoken language globally? Sign language.");
					break;
				case 6:
					chatMessage = Lib::formatChatMessage("The graveyard must be a really popular place. People are literally dying to get in!");
					break;
				case 7:
					chatMessage = Lib::formatChatMessage("Justice is a dish best served cold; if it were serve warm, it would be justwater.");
					break;
				case 8:
					chatMessage = Lib::formatChatMessage("Don't trust atoms! They make up everything.");
					break;
				case 9:
					chatMessage = Lib::formatChatMessage("If you need more reasons to move to Switzerland, I heard that the flag is a big plus.");
					break;
				case 10:
					chatMessage = Lib::formatChatMessage("Why did the bike fall down? It was two tired.");
					break;
				case 11:
					chatMessage = Lib::formatChatMessage("To the thieves who stole my calendar: I hope you get six months each.");
					break;
				case 12:
					chatMessage = Lib::formatChatMessage("How many tickles does it take to make a squid laugh? Ten.");
					break;
				case 13: 
					chatMessage = Lib::formatChatMessage("A tuna wrap walks into a bar. It left because the bartender said they didn't serve food there.");
					break;
				case 14:
					chatMessage = Lib::formatChatMessage("Why do Clamperl never share? Because they're shellfish.");
					break;
				case 15:
					chatMessage = Lib::formatChatMessage("The best dam special episode is Bidoof's Wish, obviously.");
					break;
				case 16:
					chatMessage = Lib::formatChatMessage("Did you get a haircut? No, I got all of them cut!");
					break;
				case 17:
					chatMessage = Lib::formatChatMessage("I wasn't happy with the velcro I bought. It was a total rip-off.");
					break;
				case 18:
					chatMessage = Lib::formatChatMessage("Did you hear about the campground fire? It was in tents.");
					break;
				case 19:
					chatMessage = Lib::formatChatMessage("I don't have any puns about paper. They're all so tearable.");
					break;
				case 20:
					chatMessage = Lib::formatChatMessage("Fortnite isn't the best name for a battle royale, it's just too weak.");
					break;
				case 21:
					chatMessage = Lib::formatChatMessage("A panda pulls out a gun and fires toward the ceiling in a busy restaurant. He thinks that's okay because he eats bamboo shoots and leaves.");
					break;
				case 22:
					chatMessage = Lib::formatChatMessage("What do runners eat before a race? Nothing, they fast.");
					break;
				case 23:
					chatMessage = Lib::formatChatMessage("How many Perfect Apples grow on a tree? All of them.");
					break;
				case 24:
					chatMessage = Lib::formatChatMessage("Want to hear a construction joke? Too bad, I'm still working on it.");
					break;
				}
			TwitchCommandLimit::fetchInstance().AddCommand(chatMessage);
				


		}

	private:


};


#endif