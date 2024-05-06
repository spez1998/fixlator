#pragma once

#include <wx/wx.h>
#include <wx/propdlg.h>

class UserSettings: public wxPropertySheetDialog
{
    public:
        UserSettings();
        bool Create(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos=wxDefaultPosition,
                const wxSize &size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE,
                const wxString &name=wxDialogNameStr);
        ~UserSettings();

    private:
        ;
};