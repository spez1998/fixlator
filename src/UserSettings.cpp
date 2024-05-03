#include "UserSettings.h"

UserSettings::UserSettings(const wxString &appName, const wxString &vendorName, const wxString &localFilename,
                            const wxString &globalFilename, long style)
    : wxFileConfig(appName, vendorName, localFilename, globalFilename, style)
{
    ;
}

UserSettings::~UserSettings()
{
    ;
}