/**
    TwitchPrivMsg.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#include "TwitchCommandProcess.h"
#include "../Minigames/Exploration.h"

bool TwitchPrivMsg::Process(const string incoming) {
    string name, message;
    //Strip the username and their message
	Lib::stripMessage(incoming, name, message);
    //Push to log / console
    cout << "Chat: " << name << ": " << message << endl;
    Lib::writeToLog("PhantomBotLog.txt", "{Chat} " + name + ": " + message);	    
    
    //do not filter text if not in anagram-accepting state!
    if (Exploration::fetchInstance().inAnagram()) {
        cout << "Checking for anagram status." << endl;
        int messageLength = message.length();
        for (int i = 0; i < messageLength; i++) {
            message[i] = tolower(message.at(i));
        }
        bool localbool = true;
        bool rangeCheck = true;
        string correctAns = Exploration::fetchInstance().whereGoFetch();
        int ansLength = correctAns.length();
        

        for (int i = 0; i < ansLength; i++) {
            correctAns[i] = tolower(correctAns.at(i));
            try {
                rangeCheck = (correctAns[i] == message.at(i));
            }
            catch (exception& e) {
                goto ENDLOOP;
            }
            if (correctAns[i] != message[i]) {
                localbool = false;
            }
        }
        //cout << message << "a" << endl;
        //cout << correctAns << "a" << endl;
        //correct answer
        
        
        if (localbool) {
            Exploration::fetchInstance().whoWon(name);
            Exploration::fetchInstance().setAnagramFalse();
        }
    }

    //Process commands here, but check if we're only doing it for admin users
	//REPLACE WITH PROPER ADMIN MODE CHECK LATER
    /*if(TwitchCommandLimit::fetchInstance().AdminOnlyMode()) {
    	if(!Admin::fetchInstance().CheckAdminStatus(name)) {
    		//Out of luck, kill here...
    		return true;
    	}
		
    }
	*/
    ENDLOOP: CustomCommandManager::fetchInstance().Process(incoming);

	return true;
}

TwitchPrivMsg &TwitchPrivMsg::fetchInstance() {
	if(managedSingleton<TwitchPrivMsg>::instance() == NULL) {
		managedSingleton<TwitchPrivMsg>::createInstance();
	}
	return *(managedSingleton<TwitchPrivMsg>::instance());
}
