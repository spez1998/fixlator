#include "ParserEngine.h"

ParserEngine::ParserEngine()
{
    ;
}

ParserEngine::~ParserEngine()
{
    ;
}

int ParserEngine::RawToMaps(std::istream& in_stream)
// For each FIX message, construct an <int, std::string> map from tags and values in the message
// Do this immediately since hffix message_readers need to last for less time than the input buffer (in this case our in_stream)
{
    std::map<int, std::string> field_dictionary;
    hffix::dictionary_init_field(field_dictionary);
    std::map<std::string, std::string> message_dictionary;
    hffix::dictionary_init_message(message_dictionary);

    size_t buffer_length = 0; // The number of bytes read in buffer[].

    // Read chunks from stdin until 0 is read or the buffer fills up without finding a complete message.
    while (in_stream.read(buffer + buffer_length, std::min(sizeof(buffer) - buffer_length, size_t(chunksize))))
    {
        std::map<std::tuple<int, std::string>, std::string> msg; // The message map.
        buffer_length += in_stream.gcount();
        hffix::message_reader reader(buffer, buffer + buffer_length);
        for (; reader.is_complete(); reader = reader.next_message_reader())
        {
            if (reader.is_valid())
            {
                // A complete message. Read fields out of reader and into map.
                std::tuple<int, std::string> beginStringTag = std::make_tuple(8, "BeginString");
                std::string beginStringValue;
                msg[beginStringTag] = beginStringValue.assign(reader.prefix_begin(), reader.prefix_size());
                try
                {
                    for (hffix::message_reader::const_iterator i = reader.begin(); i != reader.end(); i++)
                    {
                        std::tuple<int, std::string> tag = std::make_tuple(i->tag(), nullptr);
                        std::map<int, std::string>::iterator fname = field_dictionary.find(i->tag());
                        if (fname != field_dictionary.end())
                            std::get<1>(tag) = fname->second;

                        if (i->tag() == hffix::tag::MsgType)
                        {
                            std::map<std::string, std::string>::iterator mname = message_dictionary.find(std::string(i->value().begin(), i->value().end()));
                            if (mname != message_dictionary.end())
                                std::get<1>(tag) = mname->second;
                        }

                        std::string value;
                        msg[tag] = value.assign(i->value().begin(), i->value().size());
                    }
                }
                catch (std::exception& ex)
                {
                    std::tuple<int, std::string> errTag = std::make_tuple(9999, nullptr);
                    msg[errTag] = std::string(ex.what());
                }
            }
            else
            {
                std::tuple<int, std::string> errTag = std::make_tuple(999999, nullptr);
                std::string errString;
                msg[errTag] = errString.assign("Corrupted FIX msg");
            }
        }

        buffer_length = reader.buffer_end() - reader.buffer_begin();
        if (buffer_length > 0) // Then there is an incomplete message at the end of the buffer.
            std::memmove(buffer, reader.buffer_begin(), buffer_length); // Move the partial portion of the incomplete message to buffer[0].

        messages.push_back(msg);
    }

    return 0;
}