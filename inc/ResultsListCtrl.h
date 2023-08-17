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
			/*
			std::map message = f_ParserEngine->messages[index];
		
			std::tuple<int, std::string> timestamp = std::make_tuple(hffix::tag::SendingTime,"SendingTime");
			std::tuple<int, std::string> fixspec = std::make_tuple(hffix::tag::BeginString,"BeginString");
			std::tuple<int, std::string> msgtype = std::make_tuple(hffix::tag::Currency,"Currency");

			switch (colId)
			{
				case 0:
					return message[timestamp];
				case 1:
					return message[fixspec];
				case 2:
					return message[msgtype];
				default:
					return "";
			}
			*/
			
			// /*
			HffixMsg msg = f_ParserEngine->messages_hffix[index];
			hffix::message_reader reader(msg.buf, msg.size);
			hffix::message_reader::const_iterator i = reader.begin();

			std::cout << std::endl;
			if (reader.is_valid()) {
				std::cout << "reader is valid" << std::endl;
			}
			//std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp;
			switch (colId)
			{
				case 0:
					{
						return wxString::FromUTF8(reader.prefix_begin(), reader.prefix_size());
					}
				case 1:
					{
						reader.find_with_hint(hffix::tag::Currency, i);
						return _(i->value().as_char());
					}
				case 2:
					{
						reader.find_with_hint(hffix::tag::BeginString, i);
						int test = i->value().as_int<int>();
						std::cout << test << '\n';
						return wxString::Format(wxT("%i"),test);
					}
				default:
					return "";
			}
		
		//*/
		}

		void RefreshAfterUpdate()
		{
			this->SetItemCount(f_ParserEngine->messages_hffix.size());
			this->Refresh();
		}
	
	public:
		wxListItem *col0 = nullptr;
		wxListItem *col1 = nullptr;
		ParserEngine* f_ParserEngine;

	private:
		static int colId;
		
};