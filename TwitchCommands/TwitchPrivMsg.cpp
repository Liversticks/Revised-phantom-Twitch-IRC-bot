/**
    TwitchPrivMsg.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#include "TwitchCommandProcess.h"
#include "../Minigames/Exploration.h"

bool validateInput(string test, string ans) {
    int testLength = test.length();
    int ansLength = ans.length();
    int i, j;
    for (i = 0; i < testLength; i++) {
        test[i] = tolower(test.at(i));
    }
    cout << testLength << ' ' << ansLength << endl;
    cout << test << endl;
    cout << ans << endl;
    //messages have two newlines at the end: 1 from server, 1 from client
    try {
        for (j = 0; j < ansLength-2; j++) {
            ans[j] = tolower(ans.at(j));
            if (ans[j] != test.at(j)) {
                return false;
            }
        }
    }
    catch (exception& e) {
        return false;
    }
    try {
        //this character
        if (isgraph(test.at(ansLength))) {
            return false;
        }
    }
    catch (exception &e){
        return true;
    }
    return true;
    
}

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
        string correctAns = Exploration::fetchInstance().whereGoFetch();
        if (validateInput(message, correctAns)) {
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
    CustomCommandManager::fetchInstance().Process(incoming);

	return true;
}

TwitchPrivMsg &TwitchPrivMsg::fetchInstance() {
	if(managedSingleton<TwitchPrivMsg>::instance() == NULL) {
		managedSingleton<TwitchPrivMsg>::createInstance();
	}
	return *(managedSingleton<TwitchPrivMsg>::instance());
}
