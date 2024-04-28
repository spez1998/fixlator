#include <map>

#include <wx/string.h>
#include <hffix.hpp>

#include "ResultsListCtrl.h"

int ResultsListCtrl::col_id = 0;

ResultsListCtrl::ResultsListCtrl(wxWindow* parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style,
                                    const wxString &name)
    :wxListCtrl(parent, id, pos, size, wxLC_REPORT | wxLC_VIRTUAL)
{
    AddColumn("Timestamp", 80);
    AddColumn("Spec version", 120);
    AddColumn("Message type", 120);
    AddColumn("Currency", 120);
}

void ResultsListCtrl::AddColumn(const char *name, int width)
{
    col_id = this->AppendColumn(name);
    this->SetColumnWidth(col_id, width);
}

void ResultsListCtrl::RefreshAfterUpdate()
{
    this->SetItemCount(rawdatahandler_main->GetNumMsgs());
    this->Refresh();
}

// Bind(wxEVT_LIST_COL_CLICK, &MyListCtrl::OnColClick, this); --> somewhere here?

wxString ResultsListCtrl::OnGetItemText(long index, long col_id) const
{
    const char *curr_msg_loc = rawdatahandler_main->GetMsgLoc(index);
    hffix::message_reader reader(curr_msg_loc, strlen(curr_msg_loc));
    std::map<std::string, std::string> msg_dict;
    hffix::dictionary_init_message(msg_dict);

    if (reader.is_valid())
    {
        auto i = reader.begin();
        switch (col_id)
        {
            case TIMESTAMP:
            {
                reader.find_with_hint(hffix::tag::SendingTime, i);
                return _(i->value().as_string());
            }
            case SPEC_VERSION:
                return wxString::FromUTF8(reader.prefix_begin(), reader.prefix_size());

            case MESSAGE_TYPE:
            {
                reader.find_with_hint(hffix::tag::MsgType, i);
                
                std::string result;
                std::map<std::string, std::string>::iterator mname = msg_dict.find(std::string(i->value().begin(),
                                                                                    i->value().end()));
                result = mname->first;
                if (mname != msg_dict.end())
                    result += mname->second;

                return _(result);
                
            }
            case CURRENCY:
            {
                reader.find_with_hint(hffix::tag::Currency, i);
                return _(i->value().as_string());
            }
            default:
                return "";
        }
    }
    else
    {
        switch (col_id)
        {
            case 0:
                return wxString::FromAscii(invalidDataText);

            default:
                return "";
        }
    }
}

/*
void ResultsListCtrl::SortByColumn(int col_id)
{
    static auto GenericCompare = [](auto a, auto b, bool ascending) {
        return ascending ? a < b : a > b;
    };



    bool ascending = this->sort_ascending;

    // I have a char buffer in memory
    // I have a list of pointers to the start of each FIX message's bytes in memory
    // Given these two things, how do I sort the list of pointers by the value of a tag in the FIX message?

    // 

    std::sort(rawdatahandler_main->msg_locs.begin(),
                rawdatahandler_main->msg_locs.end(),
                [col_id, ascending](hffix::message_reader r1, hffix::message_reader r2)
                {
                    
                    switch(col_id)
                    {
                        case SPEC_VERSION:
                            break;
                    }
                }

    

}
*/