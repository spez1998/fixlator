#include <wx/string.h>
#include <wx/config.h>
#include <wx/confbase.h>
#include <wx/stdpaths.h>

#include "FLMain.h"

#define wxID_TEXTCTRL_INPUTBOX 10001
#define wxID_BUTTON_TRANSLATE 10002
#define wxID_LISTCTRL_RESULTS 10003
#define wxID_PREFERENCES 10004

wxBEGIN_EVENT_TABLE(FLMain, wxFrame)
	EVT_BUTTON(wxID_BUTTON_TRANSLATE, FLMain::OnTranslateClicked)
	EVT_MENU(wxID_EXIT, FLMain::OnExit)
	EVT_MENU(wxID_PREFERENCES, FLMain::OnPreferencesClicked)
wxEND_EVENT_TABLE()

FLMain::FLMain()
	: wxFrame(nullptr, wxID_ANY, "fixlator", wxDefaultPosition, wxDefaultSize)
{
	/* Cosmetics */
	SetBackgroundColour(wxColour("#ECECEC"));

	/* Spawn necessary objects */
	textctrl_inputbox = new wxTextCtrl(this, wxID_TEXTCTRL_INPUTBOX, "Input", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	button_translate = new wxButton(this, wxID_BUTTON_TRANSLATE, "Translate");
    listctrl_results = new ResultsListCtrl(this, wxID_LISTCTRL_RESULTS, wxDefaultPosition, wxDefaultSize,
										wxLC_REPORT|wxLC_VIRTUAL, _("Results"));
	messagedialog_clearcurrmsgs = new wxMessageDialog(this, clrCurrentDataNotif, "Clear current messages",
														wxYES_NO | wxICON_QUESTION);
	gridbagsizer_main = new wxGridBagSizer(0, 0);

	rawdatahandler_main = std::make_shared<RawDataHandler>();
	listctrl_results->rawdatahandler_main = rawdatahandler_main;

	menubar_main = new wxMenuBar;
	menu_file = new wxMenu;
	menu_edit = new wxMenu;
	menu_help = new wxMenu;

	menu_file->Append(wxID_EXIT, _("&Quit"));
	menu_edit->Append(wxID_PREFERENCES, _("&Preferences"));

	menubar_main->Append(menu_file, _("&File"));
	menubar_main->Append(menu_edit, _("&Edit"));
	menubar_main->Append(menu_help, _("&Help"));
	SetMenuBar(menubar_main);

	/* Set up the grid sizer */
	gridbagsizer_main->SetFlexibleDirection(wxBOTH);
	gridbagsizer_main->AddGrowableRow(0);
	gridbagsizer_main->AddGrowableRow(2); 
	gridbagsizer_main->AddGrowableCol(0);
	gridbagsizer_main->Add(textctrl_inputbox, wxGBPosition(0, 0), wxGBSpan(1, 2), wxEXPAND | wxALL);
	gridbagsizer_main->Add(button_translate, wxGBPosition(1, 0), wxDefaultSpan);
	gridbagsizer_main->Add(listctrl_results, wxGBPosition(2, 0), wxDefaultSpan, wxEXPAND | wxALL);

	/* Set up user settings */
	wxFileName exec_name(wxStandardPaths::Get().GetExecutablePath());
	wxString settings_path = exec_name.GetPath() + _T("/../../src/fixlator.ini");
	fileconfig_main = std::make_shared<wxFileConfig>(wxEmptyString, wxEmptyString, settings_path, wxEmptyString,
														wxCONFIG_USE_LOCAL_FILE);
	listctrl_results->fileconfig_main = fileconfig_main;

	/* Set up user settings window */
	usersettings_main = std::make_shared<UserSettings>();
	usersettings_main->Create(this, wxID_ANY, "Settings");

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
		if (listctrl_results->GetItemCount() != 0)
		{
			int confirm = messagedialog_clearcurrmsgs->ShowModal();
			if (confirm == wxID_NO)
				return;
		}
	}

	rawdatahandler_main->StoreUserInput(raw_input_chars);
	listctrl_results->RefreshAfterUpdate();

    evt.Skip();
}

void FLMain::OnPreferencesClicked(wxCommandEvent &evt)
{
	usersettings_main->ShowModal();
	evt.Skip();
}

void FLMain::OnExit(wxCommandEvent &evt)
{
	Close(true);
	evt.Skip();
}