#include "ResultsListCtrl.h"

ResultsListCtrl::ResultsListCtrl(wxWindow *parent, wxWindowID id)
                :wxListCtrl(parent, id, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_VIRTUAL)
{
    // Add first column        
	col0 = new wxListItem();
	col0->SetId(0); 
	col0->SetText( _("Tag") ); 
	col0->SetWidth(35);
	InsertColumn(0, *col0); 

	// Add second column 
	col1 = new wxListItem();
	col1->SetId(1); 
	col1->SetText( _("Value") );
	col1->SetWidth(60);
	InsertColumn(1, *col1);
}