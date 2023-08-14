#include "ResultsListCtrl.h"

int ResultsListCtrl::colId = 0;

ResultsListCtrl::ResultsListCtrl(wxWindow *parent, wxWindowID id)
                :wxListCtrl(parent, id, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_VIRTUAL)
{
	NewColumn(_("Tag"), 35);
	NewColumn(_("Value"), 60);

	wxListItem item;
	item.SetId(0);
	item.SetText(_("Hello"));
	
	InsertItem( item );
}

int ResultsListCtrl::NewColumn(wxString name, int width)
{
	int ret = EXIT_SUCCESS;

	wxListItem col;
	col.SetId(colId);
	std::cout << colId;
	col.SetText(name);
	col.SetWidth(width);
	if ((this->InsertColumn(colId, col)) == -1)
		ret = EXIT_FAILURE;

	return colId++;
}