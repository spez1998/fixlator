#include "FLMain.h"

wxBEGIN_EVENT_TABLE(FLMain, wxFrame)
	EVT_BUTTON(10002, FLMain::OnTranslateClicked)
wxEND_EVENT_TABLE()

FLMain::FLMain() : wxFrame(nullptr, wxID_ANY, "fixlator", wxPoint(50, 50), wxSize(800, 600))
{
	SetBackgroundColour(wxColour("#ECECEC"));
	wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
	m_txt_raw = new wxTextCtrl(this, 10001, "Input", wxPoint(10, 70), wxSize(300, 30));
	m_btn_trans = new wxButton(this, 10002, "Translate", wxPoint(75,150));

    f_ResListCtrl = new ResultsListCtrl(this, 10003, wxDefaultPosition, wxDefaultSize,
										wxLC_REPORT|wxLC_VIRTUAL, _("Results"));

	sizer->Add(m_txt_raw, 1, wxEXPAND | wxALL);
	sizer->Add(m_btn_trans, 0);
	sizer->Add(f_ResListCtrl, 1, wxEXPAND | wxALL);

	this->SetSizer(sizer);
	sizer->Layout();
}

FLMain::~FLMain()
{

}

void FLMain::OnTranslateClicked(wxCommandEvent& evt)
{
	// TODO: Fix segfault on invalid input

	std::string raw_std_msg = m_txt_raw->GetValue().ToStdString();
	std::istringstream isstr(raw_std_msg);
	f_ParserEngine = new ParserEngine;
	f_ResListCtrl->f_ParserEngine = f_ParserEngine;
	//int ret = this->f_ParserEngine->RawToMaps(isstr);
	int ret = this->f_ParserEngine->TextToHffixMsgs(isstr);

    // 'example' is the first tag of the first message
	//std::tuple example = f_ParserEngine->messages[0].begin()->first;
	//int tag = std::get<0>(example);
	
	f_ResListCtrl->RefreshAfterUpdate();
	std::cout << '\n' << std::endl;
    evt.Skip();
}
