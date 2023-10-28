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
    size_t buffer_length = 0; // The number of bytes read in buffer[]
    size_t usize = strlen(userInput);

    /* Copy userInput to the heap */
    rawBuf = (char *)malloc(usize);
    memcpy(rawBuf, userInput, usize);
    
    /* Find the start of each msg inside the raw text */
    hffix::message_reader reader(rawBuf, strlen(rawBuf));
    for(; reader.is_complete(); reader = reader.next_message_reader())
    {
            msgLocs.push_back(reader.buffer_begin());
    }
 
    buffer_length = reader.buffer_end() - reader.buffer_begin();
    
    /* Store pointer to incomplete message separately for special handling */
    if (buffer_length > 0)
    {
        partialMsg = reader.buffer_begin(); 
    }

    return 0;
}