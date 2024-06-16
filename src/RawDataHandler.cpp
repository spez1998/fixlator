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

int RawDataHandler::StoreUserInput(const char *user_rawinput)
{
    size_t buffer_length = 0; // The number of bytes read in buffer[]
    size_t usize = strlen(user_rawinput);

    /* Delete current data before saving new data */
    if (user_data != nullptr)
        ClearStoredData();

    /* Copy userInput to heap */
    user_data = new char[usize];
    std::memcpy(user_data, user_rawinput, usize);

    /* Find the start of each msg inside the raw text */
    hffix::message_reader reader(user_data, strlen(user_data));
    while (reader.is_complete()) {
        msg_locs.push_back(reader.buffer_begin());
        reader = reader.next_message_reader();
    }

    buffer_length = reader.buffer_end() - reader.buffer_begin();
    
    /* Store pointer to incomplete message separately for special handling */
    if (buffer_length > 0)
        partial_msg = reader.buffer_begin();

    return 0;
}

void RawDataHandler::ClearStoredData()
{
    if (user_data != nullptr) {
        delete[] user_data;
        user_data = nullptr;
    }

    msg_locs.clear();

    if (partial_msg != nullptr)
        partial_msg = nullptr;
}