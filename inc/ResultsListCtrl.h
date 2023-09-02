#pragma once

#include "wx/wx.h"
#include "wx/string.h"
#include "wx/listctrl.h"
#include "ParserEngine.h"

class ResultsListCtrl : public wxListCtrl
{
	public:
		ResultsListCtrl(wxWindow* parent, wxWindowID id, const wxPoint &pos,
						const wxSize &size, long style, const wxString &name);
		virtual wxString OnGetItemText(long index, long colId) const wxOVERRIDE;
		void RefreshAfterUpdate();
	
	public:
		wxListItem *col0 = nullptr;
		wxListItem *col1 = nullptr;
		ParserEngine* f_ParserEngine;

	private:
		static int colId;
		
};