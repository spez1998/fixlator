#include "wx/listctrl.h"

class ResultsListCtrl : public wxListCtrl
{
	public:
		ResultsListCtrl(wxWindow *parent, wxWindowID id);
	
	public:
		wxListItem *col0 = nullptr;
		wxListItem *col1 = nullptr;	
};