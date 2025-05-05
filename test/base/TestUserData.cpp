#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <gtest/gtest.h>

#include "src/base/UserData.h"

TEST(UserData, TestHasStoredData)
{
    Fixlator::UserData uut;
    
    std::string path {"../data/complete_fix_msg.txt"};
    std::ifstream f{path};
    if (!f.is_open()) {
        std::cerr << "Could not open test file" << std::endl;
    }

    uut.SaveData(f);
    ASSERT_EQ(uut.HasStoredData(), true); 
}
