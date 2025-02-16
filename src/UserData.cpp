#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

#include <hffix.hpp>

#include "UserData.h"

/*
TODO:
1. Investigate using std::array for underlying storage container
2. Add copy assignment, copy constructor, move constructor, move assignment
*/

UserData::UserData()
{
    userinput_buf = std::make_unique<char[]>(userinput_buf_size);
}

void UserData::SaveData(std::istream& stream)
{
    stream.read(userinput_buf.get(), userinput_buf_size);

    FindMsgs(userinput_buf, msg_locs, partialmsg_buf);
}

void UserData::SaveData(const char *data)
{
    std::memcpy(userinput_buf.get(), data, strlen(data));

    FindMsgs(userinput_buf, msg_locs, partialmsg_buf);
}

void UserData::FindMsgs(std::unique_ptr<char[]>& userinput_buf, std::vector<const char *>& msg_locs,
                            std::unique_ptr<char[]>& partialmsg_buf)
{    
    /* Find the start of each msg inside the raw text */
    hffix::message_reader reader(userinput_buf.get(), strlen(userinput_buf.get()));
    while (reader.is_complete()) {
        msg_locs.push_back(reader.buffer_begin());
        reader = reader.next_message_reader();
    }

    std::cout << "Found " << msg_locs.size() << " messages" << std::endl;

    /* Store pointer to incomplete message separately for special handling */
    userdata_len = reader.buffer_end() - reader.buffer_begin();
    if (userdata_len > 0) {
        partialmsg_len = userdata_len;
        partialmsg_buf = std::make_unique<char[]>(userdata_len);
        std::memcpy(partialmsg_buf.get(), reader.buffer_begin(), userdata_len);
    }
}

void UserData::ClearStoredData()
{
    memset(userinput_buf.get(), 0, userdata_len);
    memset(partialmsg_buf.get(), 0, partialmsg_len);
    msg_locs.clear();
}