#pragma once

#include <wx/wx.h>
#include <wx/listctrl.h>

#include "RawDataHandler.h"

/**
 * \brief The results list control class.
 *
 * This class is a custom virtual list control that displays the results of the
 * FIX message translation. It does not store any of its own data, but merely
 * acts as a facade for the underlying raw data handler.
 */
class ResultsListCtrl: public wxListCtrl
{
	public:

		/**
		 * \brief Constructor.
		 *
		 * Upon construction of the results list control:
		 * - The columns are set up
		 */
		ResultsListCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos,
						const wxSize &size, long style, const wxString &name);

		/**
		 * \brief Virtaul item text getter.
		 * 
		 * This must be overridden from the base class to display the data in
		 * the list control.
		 * \param index The index of the item.
		 * \param col_id The column id.
		*/
		virtual wxString OnGetItemText(long index, long col_id) const wxOVERRIDE;

		/**
		 * \brief Refreshes the list control after an update.
		 */
		void RefreshAfterUpdate();

		/**
		 * \brief Adds a column to the list control.
		 * 
		 * \param name The name of the column.
		 * \param width The width of the column.
		 */
		void AddColumn(const char *name, int width);

		/**
		 * \brief Gets the column id.
		 * 
		 * \return The column id.
		 */
		inline int GetColId() { return col_id; };

		void SortByColumn(int col_id);
		// int SortColumnSpec()
	
	public:
		/**
		 * \brief The main raw data handler.
		 * 
		 * This is a shared pointer to the raw data handler instantiated in
		 * FLMain.cpp.
		 */
		std::shared_ptr<RawDataHandler> rawdatahandler_main;

		enum ColumnNames
		{
			TIMESTAMP,
			SPEC_VERSION,
			MESSAGE_TYPE,
			CURRENCY
		};

	private:
		/**
		 * \brief The highest column ID currently in use.
		 */
		static int col_id;

		/**
		 * \brief The text to display when the FIX field data is invalid.
		 */
		static constexpr const char *invalidDataText = "Error: Invalid data";


		bool sort_ascending;
};