#pragma once

#include <wx/wx.h>
#include <wx/fileconf.h>
#include <wx/listctrl.h>

#include <base/Controller.h>
#include "hffix_fields.hpp"

namespace Fixlator::GUI {

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
						const wxSize &size, long style, const wxString &name,
                        std::shared_ptr<Controller> controller);

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
		 * \brief Gets the column ID.
		 * 
		 * \return The column ID.
		 */
		inline int GetColId() { return col_id; };

		/**
		 * \brief Define sorting algorithms for each column
		 * 
		 * \param col_id The column ID to sort by.
		 */
		void SortByColumn(int col_id);

		/**
		 * \brief The main file config object.
		 * 
		 * Shared ptr to wxFileConfig object instantiated in FLMain.cpp.
		 */
		std::shared_ptr<wxFileConfig> fileconfig_main;

		/**
		 * \brief The highest column ID currently in use.
		 */
		static int col_id;

	public:
		/**
		 * \brief The controller object.
		 * 
		 * This instantiates a storage class for user data and acts as the mediator between the GUI and the
		 * UserData storage class.
		 */
		std::shared_ptr<Controller> controller;

	private:
		/**
		 * \brief Column names enumeration.
		 * 
		 */
		enum ColumnNames
		{
			TIMESTAMP,
			SENDER,
			TARGET,
			MESSAGE_TYPE
		};

		/**
		 * \brief A map to associate column IDs with their corresponding hffix::tags.
		 * 
		 */
		std::unordered_map<ColumnNames, int> col_id_to_tag;

		/**
		 * \brief The text to display when the FIX field data is invalid.
		 */
		static constexpr const char *invalidDataText = "Error: Invalid data";

		/**
		 * @{ \name Column sizes. 
		 */
		/**
		 * \brief Size of columns in the list control.
		 */
		static constexpr const int SIZE_COL_TIMESTAMP = 300;
		static constexpr const int SIZE_COL_SENDER = 120;
		static constexpr const int SIZE_COL_TARGET = 120;
		static constexpr const int SIZE_COL_MESSAGE_TYPE = 120;
		/**
		 * @}
		 */

	private:
		/**
		 * \brief Sort the list control by a given column.
		 * 
		 * \param col_id The column ID to sort the data by.
		 */
		void SortByColumn(int col_id);
};

} // namespace Fixlator::GUI
