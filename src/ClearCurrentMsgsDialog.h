#pragma once

#include <wx/msgdlg.h>

class ClearCurrentMsgsDialog: public wxMessageDialog
{
    public:
        ClearCurrentMsgsDialog(wxWindow *parent, const wxString &message,
                            const wxString &caption, long style);
};