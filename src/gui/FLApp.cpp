#include "FLApp.h"

wxIMPLEMENT_APP(Fixlator::GUI::FLApp);

namespace Fixlator::GUI {

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

} // namespace Fixlator::GUI
