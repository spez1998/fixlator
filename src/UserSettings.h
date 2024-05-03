#pragma once

#include <wx/wx.h>
#include <wx/fileconf.h>

class UserSettings: public wxFileConfig
{
    public:
        UserSettings(const wxString &appName, const wxString &vendorName, const wxString &localFilename,
                        const wxString &globalFilename, long style);
        ~UserSettings();

    private:
        ;
};