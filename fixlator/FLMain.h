#pragma once
#include "wx/wx.h"
#include "wx/string.h"
#include "ParserEngine.h"
#include <sstream>

class FLMain : public wxFrame
{
private:
	ParserEngine ParserEngine;

public:
	FLMain();
	~FLMain();

public:
	wxTextCtrl *m_txt_raw = nullptr;
	wxListBox* m_list_res = nullptr;
	wxButton* m_btn_trans = nullptr;

	void OnTranslateClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

