#include "ParserEngine.h"

ParserEngine::ParserEngine()
{
    ;
}

/*
int ParserEngine::RawToMaps(std::istream& in_stream)
// For each FIX message, construct an <int, std::string> map from tags and values in the message
// Do this immediately since hffix message_readers need to last for less time than in_stream
{
    std::map<int, std::string> field_dictionary;
    hffix::dictionary_init_field(field_dictionary);
    std::map<std::string, std::string> message_dictionary;
    hffix::dictionary_init_message(message_dictionary);

    size_t buffer_length = 0; // The number of bytes read in buffer[].

    // Read chunks from stdin until 0 is read or the buffer fills up without finding a complete message.
    do
    {
        in_stream.read(buffer + buffer_length, std::min(sizeof(buffer) - buffer_length, size_t(chunksize)));
        buffer_length += in_stream.gcount();
        std::cout << "in_stream.gcount() = " << in_stream.gcount() << '\n';
        hffix::message_reader reader(buffer, buffer + buffer_length);
        for (; reader.is_complete(); reader = reader.next_message_reader())
        {
            std::map<std::tuple<int, std::string>, std::string> msg;
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
                        std::tuple<int, std::string> tag = std::make_tuple(i->tag(), "");
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
                    std::tuple<int, std::string> errTag = std::make_tuple(9999, "");
                    msg[errTag] = std::string(ex.what());
                }
            }
            else
            {
                std::tuple<int, std::string> errTag = std::make_tuple(999999, "");
                std::string errString;
                msg[errTag] = errString.assign("Corrupted FIX msg");
            }

            messages.push_back(msg);
        }

        buffer_length = reader.buffer_end() - reader.buffer_begin();
        if (buffer_length > 0) // Then there is an incomplete message at the end of the buffer.
            std::memmove(buffer, reader.buffer_begin(), buffer_length); // Move the partial portion of the incomplete message to buffer[0].

    } while (in_stream);

    return 0;
}
*/
int ParserEngine::TextToHffixMsgs(std::istream& in_stream)
// For each FIX message, construct an <int, std::string> map from tags and values in the message
// Do this immediately since hffix message_readers need to last for less time than in_stream
{
    std::map<int, std::string> field_dictionary;
    hffix::dictionary_init_field(field_dictionary);
    std::map<std::string, std::string> message_dictionary;
    hffix::dictionary_init_message(message_dictionary);

    size_t buffer_length = 0; // The number of bytes read in buffer[].

    // Read chunks from stdin until 0 is read or the buffer fills up without finding a complete message.
    do
    {
        in_stream.read(buffer + buffer_length, std::min(sizeof(buffer) - buffer_length, size_t(chunksize)));
        auto gcount = in_stream.gcount();
        buffer_length += gcount;
        std::cout << "in_stream.gcount() = " << in_stream.gcount() << '\n' << std::endl;
        
        hffix::message_reader reader(buffer, buffer + buffer_length);
        
        for (; reader.is_complete(); reader = reader.next_message_reader())
        {
            if (reader.is_valid())
            {
                std::cout << "reader.buffer_size() = " << reader.buffer_size() << std::endl;
                std::cout << "gcount * sizeof(char) = " << gcount * sizeof(char) << std::endl;
                std::cout << "reader.message_size() = " << reader.message_size() << std::endl;
                HffixMsg msg(reader.message_size());
                //std::memmove(msg.buf, reader.message_begin(), reader.message_size());
                memcpy(msg.buf, reader.message_begin(), reader.message_size());
                messages_hffix.push_back(msg);
            }
        }

        buffer_length = reader.buffer_end() - reader.buffer_begin();
        if (buffer_length > 0) // Then there is an incomplete message at the end of the buffer.
            std::memmove(buffer, reader.buffer_begin(), buffer_length); // Move the partial portion of the incomplete message to buffer[0].

    } while (in_stream);

    return 0;
}

HffixMsg::HffixMsg(size_t size)
{
    buf = (char*) malloc(size);
    size = size;
}