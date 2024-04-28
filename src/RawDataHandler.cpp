#include "RawDataHandler.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

#include "hffix.hpp"

RawDataHandler::RawDataHandler()
{
    ;
}

RawDataHandler::~RawDataHandler()
{
    delete[] user_data;
}

int RawDataHandler::StoreUserInput(const char *userInput)
{
    size_t buffer_length = 0; // The number of bytes read in buffer[]
    size_t usize = strlen(userInput);

    /* Delete current data before saving new data */
    if (user_data != nullptr)
        ClearStoredData();

    /* Copy userInput to heap */
    user_data = new char[usize];
    std::memcpy(user_data, userInput, usize);

    /* Find the start of each msg inside the raw text */
    hffix::message_reader reader(user_data, strlen(user_data));
    for(; reader.is_complete(); reader = reader.next_message_reader())
        msg_locs.push_back(reader.buffer_begin());

    buffer_length = reader.buffer_end() - reader.buffer_begin();
    
    /* Store pointer to incomplete message separately for special handling */
    if (buffer_length > 0)
        partial_msg = reader.buffer_begin();

    return 0;
}

void RawDataHandler::ClearStoredData()
{
    delete[] user_data;
    user_data = nullptr;
    msg_locs.clear();
    partial_msg = nullptr;
}

int RawDataHandler::GetUserDataFillStatus()
{
    if (user_data == nullptr)
        return 0;
    else
        return 1;
}

const char *RawDataHandler::GetMsgLoc(int msgIdx)
{
    if (msgIdx < msg_locs.size())
        return msg_locs[msgIdx];
    else
        return nullptr;
}