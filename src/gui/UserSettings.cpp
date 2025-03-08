#include <wx/panel.h>
#include <wx/bookctrl.h>

#include "UserSettings.h"

wxBEGIN_EVENT_TABLE(UserSettings, wxPropertySheetDialog)
    EVT_BUTTON(wxID_APPLY, UserSettings::OnApplyClicked)
wxEND_EVENT_TABLE()


class GeneralPanel: public wxPanel
{
    public:
        GeneralPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style,
                        const wxString &name) : wxPanel(parent, id, pos, size, style, name)
        {
            wxCheckBox *checkbox1 = new wxCheckBox(this, wxID_ANY, "Setting 1");
            wxCheckBox *checkbox2 = new wxCheckBox(this, wxID_ANY, "Setting 2");
            wxCheckBox *checkbox3 = new wxCheckBox(this, wxID_ANY, "Setting 3");

            wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
            sizer->Add(checkbox1, 0, wxALL, 5);
            sizer->Add(checkbox2, 0, wxALL, 5);
            sizer->Add(checkbox3, 0, wxALL, 5);

            // Create text field for reading from fixlator.ini
            textfield = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(200, 25), wxTE_READONLY);

            // Read from fixlator.ini and set the text field value
            wxString value, timestamp_format;

            // Add text field to the sizer
            sizer->Add(textfield, 0, wxALL, 5);

            this->SetSizer(sizer);
        }

        ~GeneralPanel()
        {
            ;
        }
    
    public:
        wxTextCtrl *textfield = nullptr;
};



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
    wxString value, timestamp_format;
    
    if (!wxPropertySheetDialog::Create(parent, id, title, pos, size, style, name))
        return false;

    CreateButtons(wxOK | wxCANCEL | wxAPPLY);


    GeneralPanel *panel_general = new GeneralPanel(GetBookCtrl(), wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                                    wxTAB_TRAVERSAL,"General");
    fileconfig_main->SetPath("/options");
    fileconfig_main->Read("timestamp_format", &timestamp_format);
    panel_general->textfield->SetValue(timestamp_format);

    GetBookCtrl()->AddPage(panel_general, "General");

    LayoutDialog();
    return true;
}

void UserSettings::OnApplyClicked(wxCommandEvent &evt)
{
    std::cout << "Apply clicked\n";
    evt.Skip();
}