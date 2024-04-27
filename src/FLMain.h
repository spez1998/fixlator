#pragma once
#include "ResultsListCtrl.h"
#include "ParserEngine.h"
#include "ClearCurrentMsgsDialog.h"
#include <wx/wx.h>


class FLMain: public wxFrame
{
private:
    void SetupResultsListCtrl();

public:
	FLMain();
	~FLMain();
	void OnTranslateClicked(wxCommandEvent &evt);

public:
	wxTextCtrl *m_txt_raw = nullptr;
	wxListBox *m_list_res = nullptr;
	wxButton *m_btn_trans = nullptr;
	ParserEngine *f_ParserEngine = nullptr;
    ResultsListCtrl *f_ResListCtrl = nullptr;
	ClearCurrentMsgsDialog *f_ClearCurrentMsgsDialog = nullptr;

	wxDECLARE_EVENT_TABLE();
};