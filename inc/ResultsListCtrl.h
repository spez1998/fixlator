#pragma once

#include "wx/wx.h"
#include "wx/string.h"
#include "wx/listctrl.h"
#include "ParserEngine.h"

class ResultsListCtrl : public wxListCtrl
{
	public:
		ResultsListCtrl(wxWindow* parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style,
						const wxString &name)
			: wxListCtrl(parent, id, pos, size, wxLC_REPORT | wxLC_VIRTUAL)
		{
			this->AppendColumn("Timestamp");
			this->AppendColumn("Spec version");
			this->AppendColumn("Message type");
			this->SetColumnWidth(0, 80);
			this->SetColumnWidth(1, 120);
			this->SetColumnWidth(2, 600);
		}

		virtual wxString OnGetItemText(long index, long colId) const wxOVERRIDE
		{
			std::map message = f_ParserEngine->messages[index];
			std::string fixspec;
			std::string timestamp;
			std::string msgtype;

			/* TODO: A message_reader provides an iterator for a buffer of FIX msgs,
				     so long as the buffer outlives the message reader. How do I save
					 the initial buffer (or chunks of the initial buffer) in the message_reader format? */
			hffix::message_reader msg = f_ParserEngine->messages_hffix[index];
			
			hffix::message_reader::const_iterator i = msg.begin();
 
			if (msg.find_with_hint(hffix::tag::MsgType, i))
				timestamp = i++->value().as_string();
			
			if (msg.find_with_hint(hffix::tag::BeginString, i))
				fixspec = i++->value().as_string();

			if (msg.find_with_hint(hffix::tag::BeginString, i))
				msgtype = i++->value().as_string();
			
			switch (colId)
			{
				case 0:
					return timestamp;
				case 1:
					return fixspec;
				case 2:
					return msgtype;
				default:
					return "";
			}
		}

		void RefreshAfterUpdate()
		{
			this->SetItemCount(f_ParserEngine->messages.size());
			this->Refresh();
		}
	
	public:
		wxListItem *col0 = nullptr;
		wxListItem *col1 = nullptr;
		ParserEngine* f_ParserEngine = nullptr;

	private:
		static int colId;
		
};