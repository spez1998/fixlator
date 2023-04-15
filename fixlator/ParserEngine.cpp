#include "ParserEngine.h"

void ParserEngine::testEngine(std::istream& in_stream)
{
    std::cout << "Entered testEngine";
    std::map<int, std::string> field_dictionary;
    hffix::dictionary_init_field(field_dictionary);
    std::map<std::string, std::string> message_dictionary;
    hffix::dictionary_init_message(message_dictionary);

    size_t buffer_length = 0; // The number of bytes read in buffer[].

    // Read chunks from stdin until 0 is read or the buffer fills up without finding a complete message.
    while (in_stream.read(buffer + buffer_length, std::min(sizeof(buffer) - buffer_length, size_t(chunksize))))
    {
        buffer_length += in_stream.gcount();
        hffix::message_reader reader(buffer, buffer + buffer_length);
        buffer_length = reader.buffer_end() - reader.buffer_begin();
        if (buffer_length > 0) // Then there is an incomplete message at the end of the buffer.
            std::memmove(buffer, reader.buffer_begin(), buffer_length); // Move the partial portion of the incomplete message to buffer[0].
    }
}