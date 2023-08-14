#include "wx/listctrl.h"

class ResultsListCtrl : public wxListCtrl
{
	public:
		ResultsListCtrl(wxWindow *parent, wxWindowID id);
		int NewColumn(wxString name, int width);
	
	public:
		wxListItem *col0 = nullptr;
		wxListItem *col1 = nullptr;

	private:
		static int colId;
};