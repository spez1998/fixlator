#include <iostream>
#include <cstring>
#include <map>
#include <vector>

#include <hffix.hpp>
#include <hffix_fields.hpp>

#include "UserData.h"

/*
TODO:
1. Investigate using std::array for underlying storage container
2. Add copy assignment, copy constructor, move constructor, move assignment
*/

namespace Fixlator {

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

bool UserData::Sort(int tag)
{
    bool result {true};
 
    static auto GenericCompare = [](auto a, auto b, bool ascending)
    {
        return ascending ? (a < b) : (a > b);
    };

    bool ascending = this->sort_ascending;

    std::sort(this->msg_locs.begin(), this->msg_locs.end(),
    [tag, ascending, &result](const char *msg_p1, const char *msg_p2) -> bool
    {
        bool result {false};

        hffix::message_reader reader1(msg_p1, strlen(msg_p1));
        std::map<std::string, std::string> msgtypedict_1;
        hffix::dictionary_init_message(msgtypedict_1);

        hffix::message_reader reader2(msg_p2, strlen(msg_p2));
        std::map<std::string, std::string> msgtypedict_2;
        hffix::dictionary_init_message(msgtypedict_2);

        if (reader1.is_valid() && reader2.is_valid()) {
            bool ret {false};
            auto i1 = reader1.begin();
            auto i2 = reader2.begin();
            switch(tag) {
                case hffix::tag::SendingTime :
                    ret =  reader1.find_with_hint(hffix::tag::SendingTime, i1);
                    ret |= reader2.find_with_hint(hffix::tag::SendingTime, i2);
                    if (ret) {
                        return GenericCompare(i1->value().as_string(), i2->value().as_string(), ascending);
                    } else {
                        return ascending;
                    }

                case hffix::tag::SenderCompID :
                    ret =  reader1.find_with_hint(hffix::tag::SenderCompID, i1);
                    ret |= reader2.find_with_hint(hffix::tag::SenderCompID, i2);
                    if (ret) {
                        return GenericCompare(i1->value().as_string(), i2->value().as_string(), ascending);
                    } else {
                        return ascending;
                    }

                case hffix::tag::TargetCompID :
                    ret =  reader1.find_with_hint(hffix::tag::TargetCompID, i1);
                    ret |= reader2.find_with_hint(hffix::tag::TargetCompID, i2);
                    if (ret) {
                        return GenericCompare(i1->value().as_string(), i2->value().as_string(), ascending);
                    } else {
                        return ascending;
                    }

                case hffix::tag::MsgType :
                {
                    ret =  reader1.find_with_hint(hffix::tag::MsgType, i1);
                    ret |= reader2.find_with_hint(hffix::tag::MsgType, i2);
                    auto msgtype_1 = msgtypedict_1.find(i1->value().as_string());
                    auto msgtype_2 = msgtypedict_2.find(i2->value().as_string());
                    if (ret) {
                        return GenericCompare(msgtype_1->second, msgtype_2->second, ascending);
                    } else {
                        return ascending;
                    }
                }

                default:
                    return ascending;
            }
        } else {
            result = false;
            return false; // Explicit return from non-void lambda
        }

        return true; // Should never get here
    });

    return result; 
}

} // namespace Fixlator
