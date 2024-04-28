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
	m_frame1 = new FLMain();
	m_frame1->Show();
	return true;
}
