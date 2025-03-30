#include <chrono>
#include <date/date.h>
#include <map>

#include <hffix.hpp>
#include <wx/string.h>
#include <wx/intl.h>

#include "ResultsListCtrl.h"
#include "hffix_fields.hpp"

namespace Fixlator::GUI {

int ResultsListCtrl::col_id = 0;

ResultsListCtrl::ResultsListCtrl(wxWindow* parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style,
                                    const wxString &name, std::shared_ptr<Controller> controller)
: wxListCtrl(parent, id, pos, size, wxLC_REPORT | wxLC_VIRTUAL),
  controller(controller)
{
    /* This must be done in the same order as the ColumnNames enum */
    // TODO: Define in a header along with the enum?
    AddColumn("Timestamp", SIZE_COL_TIMESTAMP);
    AddColumn("Sender", SIZE_COL_SENDER);
    AddColumn("Target", SIZE_COL_TARGET);
    AddColumn("Message type", SIZE_COL_MESSAGE_TYPE);

    this->SetFont(wxFont(10, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    this->Bind(wxEVT_LIST_COL_CLICK, [this](wxListEvent &evt) {
        this->SortByColumn2(static_cast<ColumnNames>(evt.GetColumn()));
        this->Refresh();
        this->sort_ascending = !this->sort_ascending;
    });

	col_id_to_tag[ColumnNames::TIMESTAMP] = hffix::tag::SendingTime;
	col_id_to_tag[ColumnNames::SENDER] = hffix::tag::SenderCompID;
	col_id_to_tag[ColumnNames::TARGET] = hffix::tag::TargetCompID;
	col_id_to_tag[ColumnNames::MESSAGE_TYPE] = hffix::tag::MsgType;
}

void ResultsListCtrl::AddColumn(const char *name, int width)
{
    col_id = this->AppendColumn(name);
    this->SetColumnWidth(col_id, width);
}

void ResultsListCtrl::RefreshAfterUpdate()
{
    this->SetItemCount(controller->GetNumSavedMsgs());
    this->Refresh();
}

wxString ResultsListCtrl::OnGetItemText(long index, long col_id) const
{
    const char *curr_msg_loc = controller->GetMsg(index);
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

void ResultsListCtrl::SortByColumn2(ColumnNames col_name)
{
    controller->SortUserData(col_id_to_tag[col_name]);
}

} // namespace Fixlator::GUI
