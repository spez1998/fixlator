#pragma once

#include <wx/wx.h>
#include <wx/fileconf.h>
#include <wx/propdlg.h>

namespace Fixlator::GUI {

class UserSettings: public wxPropertySheetDialog
{
    public:
        UserSettings();
        ~UserSettings();
        bool Create(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos=wxDefaultPosition,
                const wxSize &size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE,
                const wxString &name=wxDialogNameStr);
        void OnApplyClicked(wxCommandEvent &evt);

    public:
        std::shared_ptr<wxFileConfig> fileconfig_main;
    
    private:
        wxDECLARE_EVENT_TABLE();
};

} // namespace Fixlator::GUI
