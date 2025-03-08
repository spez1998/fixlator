#include "FLApp.h"

wxIMPLEMENT_APP(FLApp);

FLApp::FLApp()
{
}

FLApp::~FLApp()
{
}

bool FLApp::OnInit()
{
	flmain = new FLMain();
	flmain->Show();
	return true;
}
