#include "ParserEngine.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#include <vector>
#include <tuple>
#include <format>

ParserEngine::ParserEngine()
{
    partialMsg = nullptr;
}

int ParserEngine::TextToHffixMsgs(const char *userInput)
{
    std::map<int, std::string> field_dictionary;
    hffix::dictionary_init_field(field_dictionary);
    std::map<std::string, std::string> message_dictionary;
    hffix::dictionary_init_message(message_dictionary);
    size_t buffer_length = 0; // The number of bytes read in buffer[]
    enum {chunksize = 4096}; // Choose a preferred I/O chunk size
    size_t usize = strlen(userInput);

    /* Copy userInput to the heap */
    rawBuf = (char *)malloc(usize);
    memcpy(rawBuf, userInput, usize);
    
    /* Find the start of each msg inside the raw text */
    hffix::message_reader reader(rawBuf, strlen(rawBuf));
    for(; reader.is_complete(); reader = reader.next_message_reader())
    {
        if (reader.is_valid())
        {
            msgLocs.push_back(reader.buffer_begin());
        }
        else
        {
            ; // Corrupt FIX message, don't handle for now
        }
    }
 
    buffer_length = reader.buffer_end() - reader.buffer_begin();
    
    /* Store pointer to incomplete message separately for special handling */
    if (buffer_length > 0)
    {
        partialMsg = reader.buffer_begin(); 
    }

    return 0;
}