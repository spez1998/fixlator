#include "ResultsListCtrl.h"
#include "wx/string.h"
#include <map>

int ResultsListCtrl::colId = 0;

ResultsListCtrl::ResultsListCtrl(wxWindow* parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style,
                                    const wxString &name)
	: wxListCtrl(parent, id, pos, size, wxLC_REPORT | wxLC_VIRTUAL)
{
    AddColumn("Timestamp", 80);
    AddColumn("Spec version", 120);
    AddColumn("Message type", 120);
    AddColumn("Currency", 120);
}

void ResultsListCtrl::AddColumn(const char *name, int width)
{
    colId = this->AppendColumn(name);
    this->SetColumnWidth(colId, width);
}

void ResultsListCtrl::RefreshAfterUpdate()
{
    this->SetItemCount(pe->msgLocs.size());
    this->Refresh();
}

// Bind(wxEVT_LIST_COL_CLICK, &MyListCtrl::OnColClick, this); --> somewhere here?

wxString ResultsListCtrl::OnGetItemText(long index, long colId) const
{
    hffix::message_reader reader(pe->msgLocs[index], strlen(pe->msgLocs[index]));
    std::map<std::string, std::string> message_dictionary;
    hffix::dictionary_init_message(message_dictionary);

    if (reader.is_valid())
    {
        auto i = reader.begin();
        switch (colId)
        {
            case 0:
            {
                reader.find_with_hint(hffix::tag::SendingTime, i);
                return _(i->value().as_string());
            }
            case 1:
                return wxString::FromUTF8(reader.prefix_begin(), reader.prefix_size());

            case 2:
            {
                reader.find_with_hint(hffix::tag::MsgType, i);
                
                std::string result;
                std::map<std::string, std::string>::iterator mname = message_dictionary.find(std::string(i->value().begin(), i->value().end()));
                result = mname->first;
                if (mname != message_dictionary.end())
                    result += mname->second;

                return _(result);
                
            }
            case 3:
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
        switch (colId)
        {
            case 0:
            {
                const char *error = "ERROR!";
                return wxString::FromAscii(error);
            }
            default:
                return "";
        }
    }
}