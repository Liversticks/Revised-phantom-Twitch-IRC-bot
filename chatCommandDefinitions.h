/**
    chatCommandDefinitions.h
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#ifndef _CCMDDEC_H
#define _CCMDDEC_H

//Generic Headers (Don't Touch)
#include "include.h"
#include "CustomCommands/CustomCommands.h"
//Headers to all of your custom commands (Insert the path(s) to your custom command files here)
#include "CustomCommands/ccmd_time.h"
#include "CustomCommands/ccmd_isadmin.h"
#include "CustomCommands/ccmd_adminonly.h"

#include "CustomCommands/ccmd_pmdseries.h"
#include "CustomCommands/ccmd_dadjoke.h"
#include "CustomCommands/ccmd_secret.h"
#include "CustomCommands/ccmd_join.h"
#include "CustomCommands/ccmd_score.h"
#include "CustomCommands/ccmd_rules.h"
#include "CustomCommands/ccmd_points.h"
#include "CustomCommands/ccmd_top.h"

/*
ChatCommandDecs Class
Handle class which contains and initalizes all of the custom chat command definitions
*/
class ChatCommandDecs {
	public:
		/* Public Class Methods */
		//Constructor
		ChatCommandDecs() : initialized(false) { }
		//Destructor
		~ChatCommandDecs() { }
		//Fetch the instance
		static ChatCommandDecs &fetchInstance() {
			if(managedSingleton<ChatCommandDecs>::instance() == NULL) {
				managedSingleton<ChatCommandDecs>::createInstance();
			}
			return *(managedSingleton<ChatCommandDecs>::instance());		
		}
		//Initalize the instance
		void init() {
			if(initialized == true) {
				return;
			}
			initialized = true;
			if (true) {
				CustomCommandManager::fetchInstance().AddCommand("!points", new Command_Points());
				CustomCommandManager::fetchInstance().AddCommand("!dadjoke", new Command_DadJoke());
				CustomCommandManager::fetchInstance().AddCommand("!secret", new Command_Secret());
				CustomCommandManager::fetchInstance().AddCommand("!join", new Command_Join());
				CustomCommandManager::fetchInstance().AddCommand("!score", new Command_Score());
				CustomCommandManager::fetchInstance().AddCommand("!rules", new Command_Rules());
				CustomCommandManager::fetchInstance().AddCommand("!top", new Command_Top());
			}
			//inactive commands belong below, they should not be loaded
			else {
				CustomCommandManager::fetchInstance().AddCommand("!time", new Command_Time());
				CustomCommandManager::fetchInstance().AddCommand("!isadmin", new Command_IsAdmin());
				CustomCommandManager::fetchInstance().AddCommand("!adminonly", new Command_AdminOnly());
				CustomCommandManager::fetchInstance().AddCommand("!pmdseries", new Command_PMDSeries());
			}
					
		}

	private:
		bool initialized;
};

#endif //_CCMDDEC_H
