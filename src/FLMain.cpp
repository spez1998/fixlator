#include "FLMain.h"
#include <wx/gbsizer.h>
#include <wx/string.h>

wxBEGIN_EVENT_TABLE(FLMain, wxFrame)
	EVT_BUTTON(10002, FLMain::OnTranslateClicked)
	//EVT_MENU(LIST_SORT, FLMain::OnSpecSort)
wxEND_EVENT_TABLE()

FLMain::FLMain() : wxFrame(nullptr, wxID_ANY, "fixlator", wxDefaultPosition, wxDefaultSize)
{
	SetBackgroundColour(wxColour("#ECECEC"));
	
	m_txt_raw = new wxTextCtrl(this, 10001, "Input", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	m_btn_trans = new wxButton(this, 10002, "Translate");
    f_ResListCtrl = new ResultsListCtrl(this, 10003, wxDefaultPosition, wxDefaultSize,
										wxLC_REPORT|wxLC_VIRTUAL, _("Results"));

	wxGridBagSizer *gridSizer = new wxGridBagSizer(0, 0);
	gridSizer->SetFlexibleDirection(wxBOTH);
	gridSizer->AddGrowableRow(0);
	gridSizer->AddGrowableRow(2);
	gridSizer->AddGrowableCol(0);
	gridSizer->Add(m_txt_raw, wxGBPosition(0, 0), wxGBSpan(1, 2), wxEXPAND | wxALL);
	gridSizer->Add(m_btn_trans, wxGBPosition(1, 0), wxDefaultSpan);
	gridSizer->Add(f_ResListCtrl, wxGBPosition(2, 0), wxDefaultSpan, wxEXPAND | wxALL);

	this->SetSizer(gridSizer);
	gridSizer->Layout();
}

FLMain::~FLMain()
{

}

void FLMain::OnTranslateClicked(wxCommandEvent &evt)
{
	// TODO: Fix segfault on invalid input
	std::string rawIn = m_txt_raw->GetValue().ToStdString();
	const char *newrawInput = rawIn.c_str();
	f_ParserEngine = new ParserEngine;
	f_ResListCtrl->pe = f_ParserEngine;
	int ret = this->f_ParserEngine->TextToHffixMsgs(newrawInput);
	f_ResListCtrl->RefreshAfterUpdate();
    evt.Skip();
}

/*
void FLMain::OnSpecSort(wxCommandEvent &evt)
{
	f_ResListCtrl->SortItems(SpecCompFn, 0);
}

int wxCALLBACK SpecCompFn(wxIntPtr item1, wxIntPtr item2, wxIntPtr sortData)
{

}
*/