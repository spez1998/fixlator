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

    CreateButtons(wxOK|wxCANCEL|wxHELP);


    wxBookCtrlBase *book = GetBookCtrl();
    book->AddPage(new wxPanel(book, wxID_ANY), "General");
    LayoutDialog();
    return true;
}