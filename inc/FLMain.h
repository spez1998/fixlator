#pragma once
#include "wx/wx.h"
#include "wx/string.h"
#include "ResultsListCtrl.h"
#include "ParserEngine.h"
#include <sstream>

class FLMain : public wxFrame
{
private:
	ParserEngine f_ParserEngine;

private:
    void SetupResultsListCtrl();

public:
	FLMain();
	~FLMain();
	void OnTranslateClicked(wxCommandEvent& evt);

public:
	wxTextCtrl *m_txt_raw = nullptr;
	wxListBox *m_list_res = nullptr;
	wxButton *m_btn_trans = nullptr;
    ResultsListCtrl *f_ResListCtrl = nullptr;

	wxDECLARE_EVENT_TABLE();
};

