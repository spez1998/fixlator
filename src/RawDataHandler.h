#pragma once

#include <vector>

#include <hffix.hpp>

/**
 * \brief The raw data handler class.
 *
 * This class stores the user's data on the heap and maintains a list of
 * pointers to each message. It also stores a pointer to an incomplete message
 * at the end of the raw data, if one exists.
 * 
 * Users of this class are not responsible for memory managing the stored data.
 */
class RawDataHandler
{
	private:

		/**
		 * \brief The user's data.
		 * 
		 */
		char *user_data = nullptr;

		/**
		 * \brief The incomplete message at the end of the raw data.
		 * 
		 * This is not guaranteed to exist.
		 */
		const char *partial_msg = nullptr;

	public:

		/**
		 * \brief The list of pointers to each message.
		 */
		std::vector<const char *> msg_locs;

	public:

		/**
		 * \brief Default constructor
		 * 
		 */
		RawDataHandler();

		/**
		 * \brief Destructor.
		 * 
		 * Any saved memory is deallocated from the heap upon destruction.
		 */
		~RawDataHandler();

		/**
		 * \brief Stores the user's input data.
		 * 
		 * This function copies the user's input data from the input text box to the
		 *  heap and stores pointers to each FIX message.
		 * 
		 * \param user_input ASCII bytes of FIX messages.
		 * \return 0 on success, TODO: -1 on failure.
		 */
		int StoreUserInput(const char *user_input);

		/**
		 * \brief Clears the stored data.
		 * 
		 * This function deallocates the memory used to store the user's data and
		 * clears the list of message pointers.
		 */
		void ClearStoredData();

		/**
		 * \brief Returns the save status of the user data.
		 * 
		 * \return 0 if no data is stored, 1 if data is stored.
		 */
		int GetUserDataFillStatus();
};