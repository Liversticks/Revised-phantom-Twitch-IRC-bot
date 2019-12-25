/**
    CustomCommands.h
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#ifndef _CUSTOMCOMMANDS_H
#define _CUSTOMCOMMANDS_H

#include "../include.h"
#include "../Lib/lib.h"
#include "../TwitchIRC/TwitchCommandLimit.h"

/*
CustomCommand Class
Class instance inherited by others, used to define a custom command instance
*/
class CustomCommand {
	public:
		/* Public Class Methods */
		//Constructor
		CustomCommand() { }
		//Destructor
		virtual ~CustomCommand() { }
		//Run the command
		virtual void Fire(string input) = 0;
};

/*
CustomCommandManager Class
Class instance that manages the entire collection of custom commands
*/
class CustomCommandManager {
    //Forward Dec for CCMD
    struct CCMD;

	public:
		/* Public Class Methods */
		//Constructor
		CustomCommandManager();
		//Destructor
		~CustomCommandManager();
		//Add a command to the IRC Bot
		void AddCommand(string trigger, CustomCommand *cmd);
		//Process the input message
		void Process(string input);
		
		//Fetch the singleton instance
		static CustomCommandManager &fetchInstance();

		//lists the commands loaded as a string (to put in chat)
		string listCommands();
		
	private:
		/* Private Class Members */
		//CCMD Structure: Double type-defs the command and trigger
		struct CCMD {
			CCMD(string t, CustomCommand *i) : trigger(t), instance(i) { }
		
			//The chat message that triggers the command
			string trigger;
			//The command itself
			CustomCommand *instance;
		};
		//Vector instance of Commands
		vector<CCMD> commandList;
};
	
#endif //_CUSTOMCOMMANDS_H
