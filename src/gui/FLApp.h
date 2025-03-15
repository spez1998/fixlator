#pragma once

#include "wx/wx.h"

#include "FLMain.h"

namespace Fixlator::GUI {

class FLApp : public wxApp
{
	public:
		FLApp();
		~FLApp();
		virtual bool OnInit();

	private:
		FLMain *flmain = nullptr;
};

} // namespace Fixlator::GUI
