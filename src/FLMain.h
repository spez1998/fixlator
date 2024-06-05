/**
 * \file
 * \brief Main window functionality.
 *
 */

#pragma once

#include <memory>

#include <wx/wx.h>
#include <wx/menu.h>
#include <wx/gbsizer.h>

#include "ResultsListCtrl.h"
#include "RawDataHandler.h"
#include "UserSettings.h"

/**
 * \brief Represents the main frame within the application.
 *
 * This class has all the main functionality of fixlator.
 */
class FLMain: public wxFrame
{
	public:
		
		/**
		 * \brief Constructor.
		 *
		 * Upon construction of the main frame:
		 * - All member objects get instantiated
		 * - The grid sizer is set up
		 */
		FLMain();

		~FLMain();

		/**
		 * \brief Translate button click event handler.
		 *
		 * Stores (to the heap) user data inside the textbox and refreshes the
		 * virtual list control to display the translated data.
		 * 
		 * \param evt The event object for the button click.
		 */
		void OnTranslateClicked(wxCommandEvent &evt);

		/**
		 * \brief Clear current messages button click event handler.
		 *
		 * Prompts the user to confirm clearing the current messages.
		 * 
		 * \param evt The event object for the button click.
		 */
		void OnPreferencesClicked(wxCommandEvent &evt);

		/**
		 * \brief Quit menu item click event handler.
		 *
		 * Quit the application.
		 * 
		 * \param evt The event object for the menu item click.
		 */
		void OnExit(wxCommandEvent &evt);

	public:
		/**
		 * @{ \name wxwidgets objects. 
		 */
		/**
		 * \brief Some objects used to display useful things.
		 *
		 * These objects are memory-managed by wxwidgets so can be raw pointers.
		 */
		wxTextCtrl *textctrl_inputbox = nullptr;
		wxButton *button_translate = nullptr;
		wxGridBagSizer *gridbagsizer_main = nullptr;
		wxMessageDialog *messagedialog_clearcurrmsgs = nullptr;
		wxMenuBar *menubar_main = nullptr;
		wxMenu *menu_file = nullptr;
		wxMenu *menu_edit = nullptr;
		wxMenu *menu_help = nullptr;
		ResultsListCtrl *listctrl_results = nullptr;
		/**
		 * @}
		 */

		/** 
		 * \brief The class which stores and manages the user's raw input data.
		 * 
		 * This is responsible for saving the user data and memory locations of the 
		 * start of each FIX message. Use a shared_ptr here since this object gets 
		 * used by member objects of this class.
		*/
		std::shared_ptr<RawDataHandler> rawdatahandler_main;

		/** 
		 * \brief The main file config object.
		 * 
		 * Shared ptr to wxFileConfig object instantiated in FLMain.cpp.
		*/
		std::shared_ptr<wxFileConfig> fileconfig_main;

		/** 
		 * \brief The main user settings window.
		 * 
		 * Shared ptr to UserSettings object instantiated in FLMain.cpp.
		*/
		std::shared_ptr<UserSettings> usersettings_main;

		/** 
		 * \brief The event table for this class.
		 * 
		 * This is used to bind events to event handlers.
		*/
		wxDECLARE_EVENT_TABLE();

	private:
		/** 
		 * \brief The confirmaton message when trying to clear current FIX messages.
		 * 
		 * This is used to warn the user before they clear the current messages.
		*/
		static constexpr const char *clr_current_data_msg = "Clear current FIX messages?";
};