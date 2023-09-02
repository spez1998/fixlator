#include "ResultsListCtrl.h"

ResultsListCtrl::ResultsListCtrl(wxWindow* parent, wxWindowID id, const wxPoint &pos, 
                                const wxSize &size, long style, const wxString &name)
	: wxListCtrl(parent, id, pos, size, wxLC_REPORT | wxLC_VIRTUAL)
{
    this->AppendColumn("Timestamp");
    this->AppendColumn("Spec version");
    this->AppendColumn("Message type");
    this->AppendColumn("Currency");
    this->SetColumnWidth(0, 80);
    this->SetColumnWidth(1, 120);
    this->SetColumnWidth(2, 120);
    this->SetColumnWidth(3, 120);
}

void ResultsListCtrl::RefreshAfterUpdate()
{
    this->SetItemCount(f_ParserEngine->messages_hffix.size());
    this->Refresh();
}

wxString ResultsListCtrl::OnGetItemText(long index, long colId) const
{
    HffixMsg msg = f_ParserEngine->messages_hffix[index];
    hffix::message_reader reader(msg.buf, msg.size);
    hffix::message_reader::const_iterator i = reader.begin();

    std::cout << std::endl;
    if (reader.is_valid()) {
        // TODO: Fix wxCommand invocation when clicking anywhere in the boxes
        std::cout << "reader is valid" << std::endl;
    }

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