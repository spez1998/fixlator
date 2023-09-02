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
		void AddColumn(const char* name, int width);
		inline int getColId() { return colId; };
	
	public:
		ParserEngine* f_ParserEngine;

	private:
		static int colId;
};