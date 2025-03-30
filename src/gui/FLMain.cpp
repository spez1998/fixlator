#include <wx/string.h>
#include <wx/fileconf.h>
#include <wx/stdpaths.h>

#include "FLMain.h"

#define wxID_TEXTCTRL_INPUTBOX 10001
#define wxID_BUTTON_TRANSLATE 10002
#define wxID_LISTCTRL_RESULTS 10003
#define wxID_PREFERENCES 10004

namespace Fixlator::GUI {

wxBEGIN_EVENT_TABLE(FLMain, wxFrame)
	EVT_BUTTON(wxID_BUTTON_TRANSLATE, FLMain::OnTranslateClicked)
	EVT_MENU(wxID_EXIT, FLMain::OnExit)
	EVT_MENU(wxID_PREFERENCES, FLMain::OnPreferencesClicked)
wxEND_EVENT_TABLE()

void FLMain::SetupFrame()
{
	/* Cosmetics */
	SetBackgroundColour(wxColour("#ECECEC"));

	textctrl_inputbox->SetHint(inputbox_hint);

	/* Main window layout */
	gridbagsizer_main->SetFlexibleDirection(wxBOTH);
	gridbagsizer_main->AddGrowableRow(0);
	gridbagsizer_main->AddGrowableRow(2);
	gridbagsizer_main->AddGrowableCol(0);
	gridbagsizer_main->Add(textctrl_inputbox, wxGBPosition(0, 0), wxGBSpan(1, 2), wxEXPAND | wxALL);
	gridbagsizer_main->Add(button_translate, wxGBPosition(1, 0), wxDefaultSpan);
	gridbagsizer_main->Add(listctrl_results, wxGBPosition(2, 0), wxDefaultSpan, wxEXPAND | wxALL);

	menu_file->Append(wxID_EXIT, _("&Quit"));
	menu_edit->Append(wxID_PREFERENCES, _("&Preferences"));

	menubar_main->Append(menu_file, _("&File"));
	menubar_main->Append(menu_edit, _("&Edit"));
	menubar_main->Append(menu_help, _("&Help"));
	SetMenuBar(menubar_main);

	this->SetSizer(gridbagsizer_main);
	gridbagsizer_main->Layout();
}

FLMain::FLMain() : wxFrame(nullptr, wxID_ANY, "fixlator", wxDefaultPosition, wxDefaultSize)
{
	/* Spawn necessary objects */
	gridbagsizer_main = new wxGridBagSizer(0, 0);

	textctrl_inputbox = new wxTextCtrl(this, wxID_TEXTCTRL_INPUTBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize,
										wxTE_MULTILINE);

	button_translate = new wxButton(this, wxID_BUTTON_TRANSLATE, "Translate");

    controller = std::make_shared<Controller>();

    listctrl_results = new ResultsListCtrl(this, wxID_LISTCTRL_RESULTS, wxDefaultPosition, wxDefaultSize,
										wxLC_REPORT|wxLC_VIRTUAL, _("Results"), controller);

	messagedialog_clearcurrmsgs = new wxMessageDialog(this, clr_current_data_msg, "Clear current messages",
														wxYES_NO | wxICON_QUESTION);

	menubar_main = new wxMenuBar;
	menu_file = new wxMenu;
	menu_edit = new wxMenu;
	menu_help = new wxMenu;

	/* Set user settings path */
	wxFileName exec_name(wxStandardPaths::Get().GetExecutablePath());
	wxString settings_path = exec_name.GetPath() + _T("/../../src/fixlator.ini");
	fileconfig_main = std::make_shared<wxFileConfig>(wxEmptyString, wxEmptyString, settings_path, wxEmptyString,
														wxCONFIG_USE_LOCAL_FILE);
	usersettings_main = std::make_shared<UserSettings>();

    // TODO: Move to controller
	listctrl_results->fileconfig_main = fileconfig_main;

    // TODO: Move to controller
	usersettings_main->fileconfig_main = fileconfig_main;
	usersettings_main->Create(this, wxID_ANY, "Settings");
}

FLMain::~FLMain()
{
	;
}

void FLMain::OnTranslateClicked(wxCommandEvent &evt)
{
	std::string raw_input_str = textctrl_inputbox->GetValue().ToStdString();
	const char *raw_input_chars = raw_input_str.c_str();

	if (controller->SavedUserDataExists()) {
		if (listctrl_results->GetItemCount() != 0) {
			int confirm = messagedialog_clearcurrmsgs->ShowModal();
			if (confirm == wxID_NO) {
				return;
            } else if (confirm == wxID_YES) {
				controller->ClearUserSavedData();
            }
		}
	}

    controller->SaveUserData(raw_input_chars);
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
	Close(false);
	evt.Skip();
}

} // namespace Fixlator::GUI
