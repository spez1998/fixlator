#include <chrono>
#include <date/date.h>
#include <map>

#include <hffix.hpp>
#include <wx/string.h>
#include <wx/intl.h>

#include "ResultsListCtrl.h"

int ResultsListCtrl::col_id = 0;

ResultsListCtrl::ResultsListCtrl(wxWindow* parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style,
                                    const wxString &name) : wxListCtrl(parent, id, pos, size, wxLC_REPORT | wxLC_VIRTUAL)
{
    /* This must be done in the same order as the ColumnNames enum */
    // TODO: Define in a header along with the enum?
    AddColumn("Timestamp", SIZE_COL_TIMESTAMP);
    AddColumn("Sender", SIZE_COL_SENDER);
    AddColumn("Target", SIZE_COL_TARGET);
    AddColumn("Message type", SIZE_COL_MESSAGE_TYPE);

    this->SetFont(wxFont(10, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    this->Bind(wxEVT_LIST_COL_CLICK, [this](wxListEvent &evt)
    {
        this->SortByColumn(evt.GetColumn());
        this->Refresh();
        this->sort_ascending = !this->sort_ascending;
    });
}

void ResultsListCtrl::AddColumn(const char *name, int width)
{
    col_id = this->AppendColumn(name);
    this->SetColumnWidth(col_id, width);
}

void ResultsListCtrl::RefreshAfterUpdate()
{
    this->SetItemCount(rawdatahandler_main->msg_locs.size());
    this->Refresh();
}

wxString ResultsListCtrl::OnGetItemText(long index, long col_id) const
{
    const char *curr_msg_loc = rawdatahandler_main->msg_locs[index];
    hffix::message_reader reader(curr_msg_loc, strlen(curr_msg_loc));
    std::map<std::string, std::string> msgtypedict;
    hffix::dictionary_init_message(msgtypedict);

    if (reader.is_valid()) {
        auto i = reader.begin();
        switch (col_id) {
        case TIMESTAMP:
            if (reader.find_with_hint(hffix::tag::SendingTime, i)) {
                std::chrono::time_point<std::chrono::system_clock> timestamp;
                wxString timestamp_format, original_path = fileconfig_main->GetPath();
                fileconfig_main->SetPath("/options");
                if (!(fileconfig_main->Read("timestamp_format", &timestamp_format)))
                    timestamp_format = "%Y%m%d-%H:%M:%S";

                fileconfig_main->SetPath(original_path);
                i->value().as_timestamp(timestamp);
                return wxString(date::format(timestamp_format.ToStdString(), timestamp));
            } else {
                return _("N/A");
            }

        case SENDER:
            if (reader.find_with_hint(hffix::tag::SenderCompID, i))
                return wxString(i->value().as_string());
            else
                return _("N/A");

        case TARGET:
            if (reader.find_with_hint(hffix::tag::TargetCompID, i))
                return wxString(i->value().as_string());
            else
                return _("N/A");

        case MESSAGE_TYPE:
            if (reader.find_with_hint(hffix::tag::MsgType, i)) {
                auto msgtype = msgtypedict.find(i->value().as_string());
                if (msgtype != msgtypedict.end())
                    return wxString(msgtype->second);
                else
                    return wxString(msgtype->first);
                } else {
                    return _("N/A");
                }

            default:
                return "";
        }
    } else {
        switch (col_id) {
        case 0:
            return wxString::FromAscii(invalidDataText);

        default:
            return "";
        }
    }
}

void ResultsListCtrl::SortByColumn(int col_id)
{
    static auto GenericCompare = [](auto a, auto b, bool ascending)
    {
        return ascending ? (a < b) : (a > b);
    };

    bool ascending = this->sort_ascending;

    std::sort(rawdatahandler_main->msg_locs.begin(), rawdatahandler_main->msg_locs.end(),
        [col_id, ascending](const char *msg_p1, const char *msg_p2)
        {
            bool ret = false;

            hffix::message_reader reader1(msg_p1, strlen(msg_p1));
            std::map<std::string, std::string> msgtypedict_1;
            hffix::dictionary_init_message(msgtypedict_1);

            hffix::message_reader reader2(msg_p2, strlen(msg_p2));
            std::map<std::string, std::string> msgtypedict_2;
            hffix::dictionary_init_message(msgtypedict_2);

            if (reader1.is_valid() && reader2.is_valid()) {
                auto i1 = reader1.begin();
                auto i2 = reader2.begin();
                switch(col_id) {
                case TIMESTAMP:
                    ret =  reader1.find_with_hint(hffix::tag::SendingTime, i1);
                    ret |= reader2.find_with_hint(hffix::tag::SendingTime, i2);
                    if (ret)
                        return GenericCompare(i1->value().as_string(), i2->value().as_string(), ascending);
                    else
                        return ascending;
                
                case SENDER:
                    ret =  reader1.find_with_hint(hffix::tag::SenderCompID, i1);
                    ret |= reader2.find_with_hint(hffix::tag::SenderCompID, i2);
                    if (ret)
                        return GenericCompare(i1->value().as_string(), i2->value().as_string(), ascending);
                    else
                        return ascending;

                case TARGET:
                    ret =  reader1.find_with_hint(hffix::tag::TargetCompID, i1);
                    ret |= reader2.find_with_hint(hffix::tag::TargetCompID, i2);
                    if (ret)
                        return GenericCompare(i1->value().as_string(), i2->value().as_string(), ascending);
                    else
                        return ascending;

                case MESSAGE_TYPE:
                    {
                        ret =  reader1.find_with_hint(hffix::tag::MsgType, i1);
                        ret |= reader2.find_with_hint(hffix::tag::MsgType, i2);
                        auto msgtype_1 = msgtypedict_1.find(i1->value().as_string());
                        auto msgtype_2 = msgtypedict_2.find(i2->value().as_string());
                        if (ret)
                            return GenericCompare(msgtype_1->second, msgtype_2->second, ascending);
                        else
                            return ascending;
                    }
                }
            }
        }
    );
}