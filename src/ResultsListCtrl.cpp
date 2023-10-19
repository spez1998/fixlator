#include "ResultsListCtrl.h"
#include "wx/string.h"

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

wxString ResultsListCtrl::OnGetItemText(long index, long colId) const
{
    hffix::message_reader reader(pe->msgLocs[index], strlen(pe->msgLocs[index])); 
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
                return _(i->value().as_char());
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
        const char *error = "ERROR!";
        return wxString::FromAscii(error);
    }
}