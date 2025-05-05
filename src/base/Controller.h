#pragma once

#include <iostream>
#include <memory>

#include "UserData.h"

namespace Fixlator {

/**
 * \brief The main controller to mediate low-level <---> GUI interactions
 * 
 * This class owns and manages the UserData class.
 *
 * Most of the methods in this class should just call the corresponding method
 * in the underlying UserData class.
*/

class Controller {
    public:
        Controller() {
            userdata = std::make_unique<UserData>();
        }

        ~Controller() {}

        int SortUserData(int tag) {
            return userdata->Sort(tag);
        }

        bool SavedUserDataExists() {
            return userdata->HasStoredData();
        }

        int GetNumSavedMsgs() {
            return userdata->GetNumSavedMessages();
        }

        const char* GetMsg(int index) {
            return userdata->GetMsg(index);
        } 

        void SaveUserData(const char *input) {
            return userdata->SaveData(input);
        }

        void SaveUserData(std::istream& istream) {
            return userdata->SaveData(istream);
        }

        void ClearUserSavedData() {
            return userdata->ClearStoredData();
        }

    private:
        /**
		 * \brief The UserData object.
		 */
        std::unique_ptr<UserData> userdata;
};

} // namespace Fixlator::GUI
