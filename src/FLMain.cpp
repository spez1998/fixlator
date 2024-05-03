#include <wx/string.h>

#include "FLMain.h"

wxBEGIN_EVENT_TABLE(FLMain, wxFrame)
	EVT_BUTTON(10002, FLMain::OnTranslateClicked)
	//EVT_MENU(LIST_SORT, FLMain::OnSpecSort)
wxEND_EVENT_TABLE()

FLMain::FLMain()
	: wxFrame(nullptr, wxID_ANY, "fixlator", wxDefaultPosition, wxDefaultSize)
{
	SetBackgroundColour(wxColour("#ECECEC"));
	
	textctrl_inputbox = new wxTextCtrl(this, 10001, "Input", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	button_translate = new wxButton(this, 10002, "Translate");
    listctrl_results = new ResultsListCtrl(this, 10003, wxDefaultPosition, wxDefaultSize,
										wxLC_REPORT|wxLC_VIRTUAL, _("Results"));
	messagedialog_clearcurrmsgs = new wxMessageDialog(this, clrCurrentDataNotif, "Clear current messages",
														wxYES_NO | wxICON_QUESTION);
	gridbagsizer_main = new wxGridBagSizer(0, 0);
	gridbagsizer_main->SetFlexibleDirection(wxBOTH);
	gridbagsizer_main->AddGrowableRow(0);
	gridbagsizer_main->AddGrowableRow(2); 
	gridbagsizer_main->AddGrowableCol(0);
	gridbagsizer_main->Add(textctrl_inputbox, wxGBPosition(0, 0), wxGBSpan(1, 2), wxEXPAND | wxALL);
	gridbagsizer_main->Add(button_translate, wxGBPosition(1, 0), wxDefaultSpan);
	gridbagsizer_main->Add(listctrl_results, wxGBPosition(2, 0), wxDefaultSpan, wxEXPAND | wxALL);

	rawdatahandler_main = std::make_shared<RawDataHandler>();
	listctrl_results->rawdatahandler_main = rawdatahandler_main;

	this->SetSizer(gridbagsizer_main);
	gridbagsizer_main->Layout();
}

FLMain::~FLMain()
{
}

void FLMain::OnTranslateClicked(wxCommandEvent &evt)
{
	// TODO: Fix segfault on invalid input (?)
	std::string raw_input_str = textctrl_inputbox->GetValue().ToStdString();
	const char *raw_input_chars = raw_input_str.c_str();
	if (rawdatahandler_main->GetUserDataFillStatus() == 1)
	{
		int confirm = messagedialog_clearcurrmsgs->ShowModal();
		if (confirm == wxID_NO)
			return;
	}

	rawdatahandler_main->StoreUserInput(raw_input_chars);
	listctrl_results->RefreshAfterUpdate();

    evt.Skip();
}