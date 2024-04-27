#include "ClearCurrentMsgsDialog.h"

ClearCurrentMsgsDialog::ClearCurrentMsgsDialog(wxWindow *parent, const wxString &message,
                            const wxString &caption, long style)
    : wxMessageDialog(parent, message, caption, style)
{
    
}