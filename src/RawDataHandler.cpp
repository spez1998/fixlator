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
    ;
}

int RawDataHandler::StoreUserInput(const char *user_rawinput)
{
    size_t buffer_length = 0; // The number of bytes read in buffer[]
    size_t usize = strlen(user_rawinput);

    /* Delete current data before saving new data */
    if (user_data != nullptr)
        ClearStoredData();

    /* Copy user_rawinput to heap */
    //user_data = new char[usize];
    user_data = std::make_unique<char[]>(usize);
    //user_data(new char[usize]);
    std::memcpy(user_data.get(), user_rawinput, usize);

    /* Find the start of each msg inside the raw text */
    hffix::message_reader reader(user_data.get(), strlen(user_data.get()));
    while (reader.is_complete()) {
    hffix::message_reader reader(user_data.get(), strlen(user_data.get()));
    while (reader.is_complete()) {
        msg_locs.push_back(reader.buffer_begin());
        reader = reader.next_message_reader();
    }
        reader = reader.next_message_reader();
    }
    
    /* Store pointer to incomplete message separately for special handling */
    buffer_length = reader.buffer_end() - reader.buffer_begin();
    if (buffer_length > 0) {
        partial_msg = std::make_unique<char[]>(buffer_length);
        std::memcpy(partial_msg.get(), reader.buffer_begin(), buffer_length);
    }
    buffer_length = reader.buffer_end() - reader.buffer_begin();
    if (buffer_length > 0) {
        partial_msg = std::make_unique<char[]>(buffer_length);
        std::memcpy(partial_msg.get(), reader.buffer_begin(), buffer_length);
    }

    return 0;
}

void RawDataHandler::ClearStoredData()
{
    user_data.reset();
    msg_locs.clear();
    partial_msg.reset();
}