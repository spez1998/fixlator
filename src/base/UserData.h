#pragma once

#include <array>
#include <vector>
#include <memory>

#include <hffix.hpp>
#include <hffix_fields.hpp>

namespace Fixlator {

/**
 * \brief A class to handle the user's ASCII input of FIX data.
 *
 * This class stores the user's data on the heap and maintains a vector of
 * pointers to each message. It also stores a pointer to an incomplete message
 * at the end of the raw data, if one exists.
 * 
 * Users of this class are not responsible for memory managing the stored data.
 */
class UserData
{
	private:
	
		/**
		 * \brief Finds the start of each FIX message in the raw data.
		 * 
		 * This function uses the hffix library to find the start of each FIX message
		 * in the raw data. It stores the pointers to each message in the msg_locs vector.
		 * 
		 * \param userinput_buf The raw data.
		 * \param msg_locs The vector of pointers to each message.
		 * \param partialmsg_buf The buffer to store any incomplete message at the end of the raw data.
		 */
		void FindMsgs(std::unique_ptr<char[]>& userinput_buf, std::vector<const char *>& msg_locs,
						std::unique_ptr<char[]>& partialmsg_buf);

	private:

		/**
		 * \brief A buffer to store the user's raw input. The buffer is guaranteed to be
		 * larger than the largest possible FIX message size.
		 * 
		 * Necessary to use C-style char buf as this is what hffix works with
		 */
		std::unique_ptr<char[]> userinput_buf = nullptr;

		/**
		 * \brief A buffer to store any incomplete message at the end of the raw data.
		 * 
		 * This is not guaranteed to be filled.
         *
         * Necessary to use C-style char buf as this is what hffix works with
		 */
		std::unique_ptr<char[]> partialmsg_buf = nullptr;

		size_t userdata_len {0};
		size_t partialmsg_len {0};

		/**
		 * \brief The size of the userinput_buf. Guaranteed to be larger than largest possible FIX message.
		 */
		static constexpr size_t userinput_buf_size = 1 << 20;

        /**
         * \brief Used to store the direction of sorted data
         */
        bool sort_ascending {true};

		/**
		 * \brief The list of pointers to each FIX message.
		 */
		std::vector<const char *> msg_locs;

	public:

		/**
		 * \brief Constructor
		 * 
		 */
		UserData();

		/**
		 * \brief Default destructor.
		 * 
		 */
		~UserData() = default;

		/** 
		 * \brief Save data pointed to by char ptr.
		 */
		void SaveData(const char *data);

		/**
		 * \brief Constructor using istream.
		 * 
		 * This constructor saves the user's input from an istream.
		 * Useful for reading from std::cin.
		 * 
		 * \param stream std::istream of FIX messages.
		 */
		void SaveData(std::istream& stream);

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
		inline bool HasSavedData() { return (userinput_buf == nullptr) ? false : true; };

        /**
         * \brief Returns number of saved messages
         * 
         * \return number of ptrs in the vector, i.e. number of saved msgs
         */
        int GetNumSavedMessages() { return msg_locs.size(); };

        /**
         * \brief Get a pointer to a message
         *
         * \return const char pointer pointing to a part of the userdata saved buffer
         */
        const char* GetMsg(int index) { return msg_locs[index]; };

        /**
         * \brief Sorts messagaes in the buffer by the order of the values in the requested tag
         *
         * \return true on success (I think)
         */
        bool Sort(int tag);
};

} // namespace Fixlator
