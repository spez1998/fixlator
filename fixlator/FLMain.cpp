#include "FLMain.h"

wxBEGIN_EVENT_TABLE(FLMain, wxFrame)
	EVT_BUTTON(10002, OnTranslateClicked)
wxEND_EVENT_TABLE()

FLMain::FLMain() : wxFrame(nullptr, wxID_ANY, "fixlator", wxPoint(50, 50), wxSize(800, 600))
{
	SetBackgroundColour(wxColour("#ECECEC"));
	wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
	m_txt_raw = new wxTextCtrl(this, 10001, "", wxPoint(10, 70), wxSize(300, 30));
	m_btn_trans = new wxButton(this, 10002, "Translate", wxPoint(75,150));
	m_list_res = new wxListBox(this, 10003, wxPoint(10, 110), wxSize(50, 50));
	sizer->Add(m_txt_raw, 1, wxEXPAND | wxALL);
	sizer->Add(m_btn_trans, 0);
	sizer->Add(m_list_res, 1, wxEXPAND | wxALL);

	this->SetSizer(sizer);
	sizer->Layout();

}

FLMain::~FLMain()
{
	
}

void FLMain::OnTranslateClicked(wxCommandEvent& evt)
{
	std::string raw_std_msg = m_txt_raw->GetValue().ToStdString();
	std::istringstream isstr(raw_std_msg);
	int ret = ParserEngine.RawToMaps(isstr);
	m_txt_raw->AppendText(wxString::Format(wxT("%i"), (int)ParserEngine.messages.size())); // Size currently = 0
	wxStreamToTextRedirector redirect(m_txt_raw);
	std::cout << "Hello\n";

	evt.Skip();
}