#include <wx/panel.h>
#include <wx/bookctrl.h>

#include "UserSettings.h"

// TODO: Change this into a window displaying the settings rather than the fileControl settings
UserSettings::UserSettings()
{
    ;
}

UserSettings::~UserSettings()
{
    ;
}

bool UserSettings::Create(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos,
                const wxSize &size, long style, const wxString &name)
{
    if (!wxPropertySheetDialog::Create(parent, id, title, pos, size, style, name))
        return false;

    CreateButtons(wxOK | wxCANCEL | wxHELP);

    wxBookCtrlBase *book = GetBookCtrl();
    wxPanel *panel = new wxPanel(book, wxID_ANY);

    // Create checkboxes for settings
    wxCheckBox* checkbox1 = new wxCheckBox(panel, wxID_ANY, "Setting 1");
    wxCheckBox* checkbox2 = new wxCheckBox(panel, wxID_ANY, "Setting 2");
    wxCheckBox* checkbox3 = new wxCheckBox(panel, wxID_ANY, "Setting 3");

    // Add checkboxes to a sizer
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(checkbox1, 0, wxALL, 5);
    sizer->Add(checkbox2, 0, wxALL, 5);
    sizer->Add(checkbox3, 0, wxALL, 5);

    // Create text field for reading from fixlator.ini
    wxTextCtrl* textField = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    // Read from fixlator.ini and set the text field value
    wxString value, timestamp_format;
    fileconfig_main->SetPath("/options");
    fileconfig_main->Read("timestamp_format", &timestamp_format);
    textField->SetValue(timestamp_format);
    // Add text field to the sizer
    sizer->Add(textField, 0, wxALL, 5);

    // Set the sizer for the panel
    panel->SetSizer(sizer);

    book->AddPage(panel, "General");

    LayoutDialog();
    return true;
}