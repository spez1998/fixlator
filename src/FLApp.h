/**
 * \file
 * \brief Top level wxwidgets window class.
 *
 */

#pragma once

#include "wx/wx.h"

#include "FLMain.h"

class FLApp : public wxApp
{
	public:
		FLApp();
		~FLApp();
		virtual bool OnInit();

	private:
		FLMain *m_frame1 = nullptr;
};