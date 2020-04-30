/**
    TwitchPrivMsg.cpp
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#include "TwitchCommandProcess.h"
#include "../Minigames/Exploration.h"


//validateInput checks to see if a case-insensitive version of ans 
//is the start of a case-insensitive version of test (for the anagram unscrambler)

bool validateInput(string test, string ans) {
    int testLength = test.length();
    int ansLength = ans.length();
    //If test and ans contain the exact same letters and spaces (as visible to the user)
    //their length will differ by 2.
    //test will be longer by 2 newlines
    //Hence a simple length check is insufficient.

    int i, j;
    //make test string all lowercase
    for (i = 0; i < testLength; i++) {
        test[i] = tolower(test.at(i));
    }
    //Debugging code:
    //cout << testLength << ' ' << ansLength << endl;
    //cout << test << endl;
    //cout << ans << endl;


    //Linear search through ans
    //If char at index j does not match, return false (end checking)
    //If there is an exception, it means that we are out of bounds of test
    //Hence test is too short; return false
    try {
        for (j = 0; j < ansLength; j++) {
            ans[j] = tolower(ans.at(j));
            if (ans[j] != test.at(j)) {
                return false;
            }
        }
    }
    catch (exception& e) {
        return false;
    }
    //Here, ans and the first (ansLength) characters of test match
    //Check whether the next character is test is non-space; if it is not a space, tab, or newline,
    //then it is joined to another phrase and hence invalid.
    //This function should not throw because test must be at least (ansLength + 2), else it would have failed the previous check.
    //However, exception handling is used here in case of unexpected exceptions.
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
